#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct msg
{
    struct msg *next;
    int num;
};

struct msg *head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
    struct msg *mp;

    for (;;)
    {
        pthread_mutex_lock(&lock);
        while (head == NULL) // 头节点为空，说明没有节点
        {
            pthread_cond_wait(&has_product, &lock);
        }

        mp = head;
        head = mp->next; // 模拟消费掉一个产品

        pthread_mutex_unlock(&lock);

        printf("-consume %lu---%d\n", pthread_self(), mp->num);
        free(mp);
        sleep(rand() % 3);
    }
}

void *produser(void *p)
{
    struct msg *mp;

    for (;;)
    {
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;
        printf("-----produce-----%d\n", mp->num);

        pthread_mutex_lock(&lock); // 生产
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&has_product);

        sleep(rand() % 3);
    }
}

int main()
{
    pthread_t pid, cid;
    srand(time(NULL));

    pthread_create(&pid, NULL, produser, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}