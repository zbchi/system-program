#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

struct student
{
    int id;
    char name[256];
    int age;
}
int main()
{
    struct student stu={1,"xiaoming",16};
    int fd=open("test_map",O_RDWR|O_CREAT|O_TRUNC,0644);
    ftruncate(fd,sizeof(struct student));

    struct student *p=mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    close(fd);

    while(1)
    {
        memcpy(p,&stu,sizeof(stu));
        stu.id++;
        sleep(2);
    }
    munmap(p.sizeof(stu));
    return 0;
}