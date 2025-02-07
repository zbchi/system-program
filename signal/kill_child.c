#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main()
{
    int i=0;
    pid_t pids[5];
    for(i=0;i<5;i++)
    {
        pids[i]=fork();
        if(pids[i]==0)
        {
            while(1)
            {
                printf("child %d pid=%d is running\n",i+1,getpid());
                sleep(1);
            }        
        }
    }

    if(i==5)
    {
        printf("i am parent\n");
        sleep(2);

        int k=3;
        printf("child %d is going to die\n",k+1);
        kill(pids[k],SIGKILL);

        sleep(2);
        for(int j=0;j<5;j++)
        {
            if(j==k)continue;
            kill(pids[j],SIGKILL);
            usleep(10000);
            wait(NULL);

        }

    }

    return 0;
}