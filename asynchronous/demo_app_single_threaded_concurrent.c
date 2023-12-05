#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "event_loop.h"

#define LOG_INFO(N) \
    printf("[033[1;30mINFO\033[0m][\033[1;32m%s\033[0m][%d]: %s", __FUNCTION__, __LINE__, N); \

event_loop_t el;
static int upload = 0;
static int download = 0;

static void
upload_fn(void *arg) {
    while (upload < 100) {
        upload += 2;
        printf("[\033[1;30mINFO\033[0m][\033[1;32m%s\033[0m][%d]: upload percent age = %d\n", __FUNCTION__, __LINE__, upload);
        if (upload % 10 == 0 && upload != 100) {
            task_create_new_job(&el, upload_fn, NULL);
            break;
        }
    }
}

static void
download_fn(void* arg) {
    while (download < 100) {
        download += 2;
        printf("[\033[1;30mINFO\033[0m][\033[1;32m%s\033[0m][%d]: download percent age = %d\n", __FUNCTION__, __LINE__, download);

        if (download % 10 == 0 && download != 100)  {
            task_create_new_job(&el, download_fn, NULL);
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    event_loop_init(&el);
    event_loop_run(&el);

    sleep(1);

    task_create_new_job(&el, upload_fn, NULL);
    task_create_new_job(&el, download_fn, NULL);


    printf("[\033[1;30mINFO\033[0m][\033[1;32m%s\033[0m][%d]: Endind of main \n", __FUNCTION__, __LINE__);

    scanf("\n");

    return 0;
}