#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    int fd[2];

    int ret=pipe(fd);


    if(ret==-1)
    {
        perror("pipe");
        exit(1);
    }

    int i=0;
    for(i=0;i<2;i++)
    {
        if((pid=fork())==0)
        {
            break;
        }
    }
    if(i==0)
    {
        //兄进程写入
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        close(fd[1]);
    }
    else if(i==1)
    {
        //弟进程读出
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        close(fd[0]);
    }
    else
    {
        //关闭父进程的两端，以单向流动
        close(fd[0]);
        close(fd[1]);

        //父进程回收子进程
        for(i=0;i<2;i++)
        wait(NULL);
    }
    return 0;

    
}