#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    int i=0;
    pid_t pid,wpid;
    for(i=0;i<5;i++)
    {
        pid=fork();
        if(pid==0)
        {
            break;
        }
    }

    if(i==5)
    {
        //阻塞等待子进程结束，回收
        //while((wpid=wait(NULL))!=-1)
        //{
        //    printf("wait child %d\n",wpid);
        //}



         /*   while((wpid=waitpid(-1,NULL,0))!=-1)//waitpid阻塞等待子进程回收
        {
            printf("wait child %d\n",wpid);
        }*/

       while((wpid=waitpid(-1,NULL,WNOHANG))!=-1)//非阻塞回收
       {
            if(wpid>0)
            {
                printf("wait child%d\n",wpid);
            }
            else if(wpid==0)
            {
                sleep(1);
                continue;
            }
       }
       printf("catch all child finish\n");
    }
    else
    {
        sleep(i);
        printf("%dth child,pid=%d\n",i+1,getpid());
    }
    return 0;
}