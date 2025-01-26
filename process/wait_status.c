#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    int status=0;
    pid_t wpid=0;

    pid_t pid=fork();
    if(pid==-1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid==0)
    {
        printf("i am child ,pid=%d \n",getpid());
        sleep(1);
        exit(73);
    }
    else
    {
        wpid=wait(&status);//保存child退出状态
        if(WIFEXITED(status))//宏为真说明child正常终止
        {
            printf("i am parent,pid= %d child,exit code=%d\n",wpid,WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status))//宏函数为真说明child被信号终止
        {
            printf("i am parent ,pid=")
        }
    }