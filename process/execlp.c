#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
 void sys_err(const char *str)
 {
    perror(str);
    exit(1);
 }

 int main(int argc,char*argv[])
 {
    pid_t pid =fork();
    if(pid==0)
    {
        execlp("ls","ls","-l","-F","-a",NULL);
        perror("/bin/ls  exec error");
        exit(1);

    }
    else if(pid>0)
    {
        sleep(1);
        printf("parent\n");
    }
    return 0;

 }