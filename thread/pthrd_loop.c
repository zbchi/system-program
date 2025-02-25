#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    int i = (int)arg;
    sleep(i);

    printf("i am %dth thread:pid=%d ,tid=%lu\n", i + 1, getpid(), pthread_self());
}

int main()
{
    int i;
    pthread_t tid;
    for (i = 0; i < 5; i++)
    {
        int ret = pthread_create(&tid, NULL, tfn, (void *)i);
        if (ret != 0)
            fprintf(stderr, "pthread_creat:%s\n", strerror(ret));
    }

    sleep(6);
    printf("i am main thread\n");
    return 0;
}