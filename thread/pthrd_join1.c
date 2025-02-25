#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    // return (void *)74;
    pthread_exit((void *)"hello");
}

int main()
{
    pthread_t tid;

    char *retval; // 存储线程退出值

    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0)
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
    sleep(1);

    // 回收子线程退出值
    ret = pthread_join(tid, (void **)&retval);
    if (ret != 0)
        fprintf(stderr, "pthread_join:%s\n", strerror(ret));

    printf("child thread exit with %s\n", retval);

    return 0; // 释放进程地址空间
}