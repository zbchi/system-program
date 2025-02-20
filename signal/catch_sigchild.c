#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

void catch_child(int signum)
{
    pid_t wpid;
    // if ((wpid = wait(NULL)) != -1)
    int status;
    while (wpid = waitpid(-1, &status, 0) != -1)
        printf("-----------catch child %d---------,ret=%d\n", wpid, WEXITSTATUS(status));
}

int main()
{
    int i;
    pid_t pid;
    for (i = 0; i < 5; i++)
    {
        if ((pid = fork()) == 0)
        {
            break;
        }
    }

    if (i == 5)
    {
        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        act.sa_handler = catch_child;

        sigaction(SIGCHLD, &act, NULL);
        printf("i am parent,pid=%d\n", getpid());
        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("i am child,pid=%d\n", getpid());
        // sleep(i + 1);
        return i;
    }
}