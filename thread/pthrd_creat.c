#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int main()
{
    printf("%ld", pthread_self());
}