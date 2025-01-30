#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char*argv[])
{
    int fd,len;
    char buf[4096];

    if(argc<2)
    {
        printf("./a.out fifoname\n");
        return -1;
    }

    fd=open(argv[1],O_RDONLY);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    while(1)
    {
        len=read(fd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
        sleep(3);
    }
    close(fd);

    return 0;
}