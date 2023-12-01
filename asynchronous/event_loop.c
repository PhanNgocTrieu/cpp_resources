#include "event_loop.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief This method would move to the next task, example as below:
 *          [task1][task2][task3][task4]
 *             |
 *    Null - curr - right - right -right - null
 * => When getting task1 to execute
 *    
 *    array_loop would be like this:
 *     [task1]        [task2][task3][task4]
 *       exe    null - curr - right - right - null
 * 
 * @param el event loop main
 * @return task_t* the next task should be executed
 */
static task_t* 
event_loop_get_next_task_to_run(event_loop_t *el) {
    task_t *task;
    if (!el->task_array_head) {
        printf("%s(): task_array_head is empty\n", __FUNCTION__);
        return NULL;
    }

    task = el->task_array_head;
	el->task_array_head = task->right;
	if (el->task_array_head) {
		el->task_array_head->left = NULL;
	}
	task->left = NULL;
	task->right = NULL;
	return task;
}

/**
 * @brief this method checking whether the given task is in array of tasks
 * 
 * @param task task to check
 */
static bool
task_is_present_in_task_array(task_t *task) {
    return !(task->left != NULL && task->right != NULL);
}


/**
 * @brief
 *      Algorithm:
 *          1. Lock the EL mutex
 *          2. Fetch the task from task array
 *          3. If task not found, suspend
 *          4. If task found, fire the task
 *          5. Unlock the EL Mutex
 * 
 * @param arg 
 * @return void* 
 */
static void*
event_loop_thread(void *arg) {
    event_loop_t *el = (event_loop_t*)arg;
    task_t* _task;

    while (1)
    {
        sleep(1);

        /* lock the event loop mutex */
        pthread_mutex_lock(&el->ev_loop_mutext);
        
        /* Event loop has no task to perfom -> set state to IDLE */
        el->ev_loop_state = EV_LOOP_IDLE;

        // Doing this loop make us more efficient because we don't need to fetch regularly
        while ((_task = event_loop_get_next_task_to_run(el)) == NULL) {
            pthread_cond_wait(&el->ev_loop_cv, &el->ev_loop_mutext);
            /*
            When task is empty, we waiting here for receive signals
            On receiving signal, go back, fetch the new task from task array
            If task is not empty, we execute it
            */
        }
        /* Event loop in start of running task -> set state to busy */
        el->ev_loop_state = EV_LOOP_BUSY;

        /* Unlock mutex when done with task array */
        pthread_mutex_unlock(&el->ev_loop_mutext);

        /* Fire the task */
        el->current_task = _task;
        _task->cbk(_task->arg);
        
        /* Already done task -> current task set to Null */
        el->current_task = NULL;

        /* Free task when done - this one does not delete _task but maybe it set _task to Null */
        free(_task);
    }
}

void
event_loop_init(event_loop_t* el) {
    /* Set null to head of task array */
    el->task_array_head = NULL;
    /* Set null to the mutex of event loop */
    pthread_mutex_init(&el->ev_loop_mutext, NULL);
    /* Set default state of event loop */
    el->ev_loop_state = EV_LOOP_IDLE;
    /* Set null to cond thread */
    pthread_cond_init(&el->ev_loop_cv, NULL);
    /* Set current task is null */
    el->current_task = NULL;
}


void 
event_loop_add_task_in_task_array(
        event_loop_t *el,
        task_t *new_task
        )
{
    task_t *task, *prev_task;
	
	prev_task = NULL;
	
	task = el->task_array_head;
	while (task) {
		prev_task = task;
		task = task->right;
	}

	if (prev_task) {
		prev_task->right = new_task;
		new_task->left = prev_task;
	}
	else {
		el->task_array_head = new_task;
	}
}

static void
event_loop_schedule_task(event_loop_t* el, task_t* task) {
    pthread_mutex_lock(&el->ev_loop_mutext);

    event_loop_add_task_in_task_array(el,task);

    if (el->ev_loop_state == EV_LOOP_BUSY) {
        /* event loop in BUSY state -> we done */
        pthread_mutex_unlock(&el->ev_loop_mutext);
        return;
    }

    /* event loop in IDLE state -> send the signal */
    pthread_cond_signal(&el->ev_loop_cv);
    pthread_mutex_unlock(&el->ev_loop_mutext);
}

task_t *
task_create_new_job(event_loop_t* el, event_cbk cbk, void* arg) {
    task_t* task = (task_t*)calloc(1, sizeof(task_t));
    task->cbk = cbk;
    task->arg = arg;
    task->left = task->right = NULL;

    event_loop_schedule_task(el, task);
    return task;
}


void
event_loop_run(event_loop_t* el) {
    pthread_attr_t attr;
    
    /* Checking thread is null or not */
    assert(el->thread == NULL);

    /* Allocate memory for thread to operate */
    el->thread = (pthread_t*)calloc(1, sizeof(pthread_t));
    
    /* Initialize the attribute of thread */
    pthread_attr_init(&attr);
    
    /* Detach the attribue of thread */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    /* Create the thread with function object of event_loop_thread */
    pthread_create(el->thread, &attr, event_loop_thread,(void*) el);
}