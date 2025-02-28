#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t file1, file2;

void *tfn(void *arg)
{
    pthread_mutex_lock(&file2);
    printf("start double lock\n");

    sleep(1);

    pthread_mutex_lock(&file1); // 阻塞

    printf("i am thread\n");
}

int main()
{
    pthread_mutex_init(&file1, NULL);
    pthread_mutex_init(&file2, NULL);

    pthread_mutex_lock(&file1);

    pthread_t tid;
    pthread_create(&tid, NULL, tfn, NULL);

    sleep(1);

    pthread_mutex_lock(&file2); // 阻塞

    printf("i am main\n");

    sleep(2);
}