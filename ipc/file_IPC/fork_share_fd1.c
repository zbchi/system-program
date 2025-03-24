#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
    int fd;pid_t pid;
    char buf[1024];
    char *str="---------test for shared fd in parent child process------\n";

    fd=open("test.txt",O_RDWR|O_CREAT|O_TRUNC,06440);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    pid=fork();

    if(pid<0)
    {
        perror("fork");
        exit(1);
    }
    else if(pid==0)
    {
        write(fd,str,strlen(str));  
        printf("child wrote over...\n");

        close(fd);
    }
    else
    {
        sleep(2);
        lseek(fd,0,SEEK_SET);
        int len=read(fd,buf,sizeof(buf));
        printf("parent read:%d\n",len);
        len=write(STDOUT_FILENO,buf,len);
        printf("parent write len=%d \n",len);
        wait(NULL);
    }
    return 0;
}