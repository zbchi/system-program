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
        char buf[4096]={0};
        read(fd[0],buf,4096);
        printf("child read:%s\n",buf);
    }
    else if(pid>0)
    {
        write(fd[1],"hello\n",6);
    }
    return 0;
}