#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("child process PID is %d\n", getpid());
        printf("group id of child is %d\n", getpgid(0));
        printf("session id of child is %d\n", getsid(0));

        sleep(10);
        setsid();

        printf("changed\n");

        printf("child process PID is %d\n", getpid());
        printf("group id of child is %d\n", getpgid(0));
        printf("session id of child is %d\n", getsid(0));

        sleep(10);
        exit(0);
    }
    return 0;
}