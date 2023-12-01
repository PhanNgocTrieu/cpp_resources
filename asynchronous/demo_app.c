#include <stdio.h>
#include <stdlib.h>
#include "event_loop.h"

event_loop_t el;

void hello_wolrd() {
    printf("%s() - Hello World\n", __FUNCTION__);
}

void introduction(int value) {
    printf("%s() - integer value: %d\n", __FUNCTION__, value);
}

task_t* init_task(void* cbk, void* arg) {
    task_t* task = NULL;
    task = (task_t*)calloc(1, sizeof(task_t));
    task->cbk = cbk;
    task->arg = arg;
    task->left = task->right = NULL;
    return task;
}

// task_t* gTask;

int main(int argc, char **argv) {
    event_loop_init(&el);
    task_create_new_job(&el, hello_wolrd, NULL);
    task_create_new_job(&el, introduction, (void*)50);
    event_loop_run(&el);
    // Holding for not terminate
    scanf("\n");

    return 0;
}