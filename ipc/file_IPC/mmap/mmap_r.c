#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

struct student
{
    int id;
    char name[256];
    int age;
};
int main()
{
    struct student stu;
    int fd=open("test_map",O_RDONLY);

    struct student *p=mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);
    if(p==MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    close(fd);

    while(1)
    {
        printf("id=%d,name=%s,age=%d\n",p->id,p->name,p->age);
        sleep(2);
    }

    munmap(p,sizeof(stu));
    return 0;
} 