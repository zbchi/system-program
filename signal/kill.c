#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }

    if(pid==0)
    {
        sleep(2);
        kill(getppid(),SIGKILL);
    }
    else if(pid>0)
    {
        while(1)
        {
            printf("i am parent,pid=%d \n",getpid());
            usleep(10000);
        }
    }
    return 0;
}