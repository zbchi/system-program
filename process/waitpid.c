#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int flg=0;
    pid_t pid=fork();
    pid_t pid2=fork();
    pid_t wpid;
    if(pid==-1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid==0)
    {
        printf("i am process child ,pid=%d \n",getpid());
        sleep(5);
        exit(4);
    }
    else
    {
        do
        {
            wpid=waitpid(pid,NULL,WNOHANG);
            printf("--wpid=%d-----%d\n",wpid,flg++);
            if(wpid==0)
            {
                printf("No child exited\n");
                sleep(1);
            }
        } while (wpid==0);
        if(wpid==pid)
        {
            printf("i am parent,i catched child process,pid =%d\n",wpid);

        }
        else
        printf("other----\n");
    }
    return 0;
}