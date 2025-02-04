#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/mman.h>
int main()
{
    int fd=open("test.mmap",O_RDWR|O_CREAT|O_TRUNC,0644);

    ftruncate(fd,4);

    char*memp;
    memp=mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(memp==MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    strcpy(memp,"xxx");
    printf("%s\n",memp);
    
    if(munmap(memp,4)==-1)
    {
        perror("munmap");
        exit(1);
    }
    close(fd);

    return 0;
}