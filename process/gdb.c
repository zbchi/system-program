#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>
int main()
{
    int n=5,i;
    for(i=0;i<n;i++)
    {
        if(fork()==0)
        {
            break;
        }
    }#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>
    {
        sleep(n);
        printf("i am parent,pid = %d\n",getpid());

    }
    else
    {
        sleep(i);
        printf("i am %dth child,pid=%d\n",i+1,getpid());
    }
    return 0;
}