#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct thrd
{
    int var;
    char strp[256];
};

void *tfn(void *arg)
{
    // return (void *)74;
    struct thrd *val = (struct thrd *)arg;
    val->var = 100;
    strcpy(val->strp, "hello thread");
    pthread_exit((void *)val);
}

int main()
{
    pthread_t tid;

    struct thrd arg, *retval;

    // char *retval; // 存储线程退出值

    int ret = pthread_create(&tid, NULL, tfn, (void *)&arg);
    if (ret != 0)
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
    sleep(1);

    // 回收子线程退出值
    ret = pthread_join(tid, (void **)&retval);
    if (ret != 0)
        fprintf(stderr, "pthread_join:%s\n", strerror(ret));

    printf("child thread exit with:var=%d,str= %s\n", retval->var, ((struct thrd *)retval)->strp);

    return 0; // 释放进程地址空间
}