#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    printf("hello world\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0)
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
    sleep(1);
    return 0; // 释放进程地址空间
}