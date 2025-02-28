#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t mutex;
void *tfn(void *atg)
{
    srand(time(NULL));

    while (1)
    {
        pthread_mutex_lock(&mutex);

        printf("hello");
        // sleep(rand() % 3);
        printf("world\n");

        pthread_mutex_unlock(&mutex);

        // sleep(rand() % 3);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    srand(time(NULL));

    // 初始化 互斥锁
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid, NULL, tfn, NULL);
    while (1)
    {
        pthread_mutex_lock(&mutex); // 加锁

        printf("HELLO");
        // sleep(rand() % 3);
        printf("WORLD\n");

        pthread_mutex_unlock(&mutex); // 解锁，唤醒阻塞状态

        // sleep(rand() % 3);
    }
}