#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int main()
{
    int count=0;
    alarm(1);
    for(count=0;;count++)
    {
        printf("%d\n",count);
    }
    
}