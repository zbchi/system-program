#include<unistd.h>
#include<stdio.h>
int main()
{
    pid_t pid,wpid;
    pid=fork();
    if(pid==-1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid==0)
    {
        printf("i am process child,pid=%d\n",getpid());
        sleep(5);
    }
    else
    {
        lable:
        wpid=wait(NULL);
        if(wpid==-1)
        {
            perror("wait");
            goto lable;
        }
        printf("i am parent,i catched child,pid =%d\n ",wpid);
    }
    return 0;
}