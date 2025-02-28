#include <pthread.h>
#include <stdio.h>
#include <string.h>

pthread_mutex_t mutex;

void *tfn(void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex); // 多次lock死🔓

    printf("hello world\n");
}
int main()
{
    pthread_t tid;

    pthread_mutex_init(&mutex, NULL);

    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0)
        fprintf(stderr, "pthread_creat:%s\n", strerror(ret));

    ret = pthread_join(tid, NULL);
    if (ret != 0)
        fprintf(stderr, "pthread_creat:%s\n", strerror(ret));

    return 0;
}