#include<unistd.h>
#include<stdio.h>

int main()
{
    int fd[2];
    int ret=pipe(fd);
    if(ret==-1)
    {
        perror("pipe");
        exit(1);
    }
    pid_t pid=fork();
    if(pid==0)
    {
        close(fd[1]);  //子进程读管道，关闭写端
        char buf[4096]={0};
        read(fd[0],buf,4096);
        printf("child read:%s\n",buf);
        close(fd[0]);
    }
    else if(pid>0)
    {
        close(fd[0]); //父进程写管道，关闭读端
        write(fd[1],"hello\n",6);
        wait(NULL);
        close(fd[1]);
    }
    return 0;
}