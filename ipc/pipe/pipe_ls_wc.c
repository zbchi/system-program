#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid;
    int fd[2];

    //先创建管道
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe");
        exit(1);
    }
    pid=fork();   //ls | wc -l

    if(pid==0)
    {
        //子进程实现wc -l
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        close(fd[0]);
    }
    else if(pid>0)
    {
        close(fd[0]);  //父进程个写管道，关闭读端
        //将写出到屏幕的ls结果写入到管道写端
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        close(fd[1]);
    }
    return 0;
}