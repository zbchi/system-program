#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
int main(int argc,char*argv[])
{
    int fd,i;
    char buf[4096];
    if(argc<2)
    {
        printf("enter like this:./a.out filename\n");
        return -1;
    }

    fd=open(argv[1],O_WRONLY);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    i=0;
    while(1)
    {
        sprintf(buf,"hello %d\n",i++);
        write(fd,buf,strlen(buf));
        sleep(2);
    }
    close(fd);

    return 0;
}