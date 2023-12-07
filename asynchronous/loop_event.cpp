#ifndef __EVENT_LOOP_
#define __EVENT_LOOP_

// #include <pthread.h>
#include <thread>

typedef struct task_ task_t;
typedef struct event_loop_ event_loop_t;

/**
 * @brief This is the callback function template
 * 
 */
typedef void (*event_cbk) (void *);

struct task_ {
    event_cbk cbk;
    void *arg;
    struct task_ *left, *right;
};

typedef enum {
    EV_LOOP_IDLE,
    EV_LOOP_BUSY
} EV_LOOP_STATE;

struct event_loop_ {
    /**
     * @brief Head to the start of the task array
     *
     */
    struct task_ *task_array_head;

    /**
     * @brief   Mutex to enforce Mutual exclusion enqueue/dequeue
     *          Operation in task array. Also used to update event loop
     *          attributes in mutual exclusive way
     *
     */
    pthread_mutex_t ev_loop_mutex;
    /**
     * @brief State of event loop
     * 
     */
    EV_LOOP_STATE ev_loop_state;

    /**
     * @brief CV to suspend event loop thread
     * 
     */
    pthread_cond_t ev_loop_cv;

    /**
     * @brief Event loop Thread
     * 
     */
    pthread_t* thread;

    /**
     * @brief Current task which event loop thread is executing
     * Null if event loop is resting in peace
     * 
     */
    struct task_ *current_task;
};

void
event_loop_init(event_loop_t* el);

void
event_loop_run(event_loop_t* el);

task_t *
task_create_new_job(event_loop_t* el, event_cbk cbk, void* arg);

task_t *
task_cancel_job(event_loop_t *el, task_t* task);


#endif /* __EVENT_LOOP_ */