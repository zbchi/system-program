#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    while (1)
    {
        printf("hello world\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0)
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));

    sleep(5);
    // 杀死子进程
    ret = pthread_cancel(tid);
    if (ret != 0)
        fprintf(stderr, "pthread_cancel:%s\n", strerror(ret));

    sleep(3);

    return 0; // 释放进程地址空间
}