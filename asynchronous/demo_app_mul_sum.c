#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "event_loop.h"

event_loop_t el;
int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

/*
    Problems:
        we have prototype: void fn(void*);
        and we have 2 arguments, how can we handle this?

        => solve problem by: define the structure
            instead of 2 parameters: arr[] and size
            we can have: arg_obj {
                arr[]
                size
            }
    
    Another problem: when passing an object so how can we know which object we should cast
        => We need a wrapper
*/

/* ============ Arg_Obj Template ===================== */
typedef struct arg_obj_ {
    int *arr;
    int size;
} arg_obj_t;

/* ============ Function Objects ===================== */
int sum (int arr[], int size) {
    int i, sum = 0;
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }

    return sum;
}


int mul(int arr[], int size) {
    int i, mul = 1;
    for (i = 0; i < size; i++) {
        mul *= arr[i];
    }
    return mul;
}

/* ============ Wrapper Functions ===================== */
void sum_wrapper(void* arg) {
    arg_obj_t *arg_obj= (arg_obj_t*)arg;
    printf("sum = %d\n", sum(arg_obj->arr, arg_obj->size));
}

void mul_wrapper(void *arg) {
    arg_obj_t *arg_obj= (arg_obj_t*)arg;
    printf("mul = %d\n", mul(arg_obj->arr, arg_obj->size));
}

int main(int argc, char* argv[]) {

    event_loop_init(&el);
    event_loop_run(&el);
    sleep(1);

    arg_obj_t *arg_obj1 = calloc(1, sizeof(arg_obj_t));
    arg_obj1->arr = arr;
    arg_obj1->size = sizeof(arr)/sizeof(arr[0]);

    /* Create a job with the wrapper function */
    task_create_new_job(&el, sum_wrapper, (void*)arg_obj1);

    arg_obj_t *arg_obj2 = calloc(1, sizeof(arg_obj_t));
    arg_obj2->arr = arr;
    arg_obj2->size = sizeof(arr)/sizeof(arr[0]);
    task_create_new_job(&el, mul_wrapper, (void*)arg_obj1);

    printf("%s: Ending...\n", __FUNCTION__);
    scanf("\n");

    return 0;
}