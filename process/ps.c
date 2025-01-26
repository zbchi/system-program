#include<unistd.h>
#include<stdio.h>
int main()
{
    pid_t pid =fork();
    if(pid==0)
    {
        execlp("sh","sh","-c","ps aux > out",NULL);
        perror("ps");
        exit(1);
    }
    else if(pid>0)
    {
        sleep(1);
        printf("parent\n");
    }
    return 0;

    
}