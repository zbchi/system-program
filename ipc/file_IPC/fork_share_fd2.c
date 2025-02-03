#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
    int fd1,fd2;pid_t pid;
    char buf[1024];
    char *str = "----------test for shared fd in parent child process-------\n";

    pid=fork();
    
    if(pid==0)
    {
        fd1=open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
        if(fd1<0)
        {
            perror("open");
            exit(1);
        }
        sleep(3);//睡眠三在子进程写入前，先让父进程读
        //无阻塞，无法读取

        write(fd1,str,strlen(str));
        printf("child wrote ober\n");
    }
    else
    {
        sleep(1);
        fd2=open("test.txt",O_RDONLY);
        if(fd2<0)//...
        exit(1);

        int len=read(fd2,buf,sizeof(buf));
        len=write(STDOUT_FILENO,buf,len);
        printf("---parent read len = %d\n",len);

        wait(NULL);
    }
    return 0;
}