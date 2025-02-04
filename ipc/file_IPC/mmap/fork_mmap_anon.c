#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int var=100;
int main()
{
    int *p;

    p=(int*)mmap(NULL,40,PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANON,-1,0);
    if(p==MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    pid_t pid=fork();
    if(pid==0)
    {
        *p=2000;      //写共享内存
        var=1000;     //写全局变量，修改复制份
        printf("child,*p=%d,var=%d\n",*p,var);
    }
    else{
        sleep(1);
        printf("parent,*p=%d,var=%d\n",*p,var);
        wait(NULL);

        int ret=munmap(p,4);
        if(ret==-1)
        {
            perror("munmap");
            exit(1);
        }
    }

    return 0;
}