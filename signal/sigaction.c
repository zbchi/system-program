#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sig_catch(int signum)
{
    if (signum == SIGINT)
        printf("----catch %d signal\n", signum);
    sleep(5); // 模拟执行了很长时间
}

int main()
{
    struct sigaction act, oldact;
    act.sa_handler = sig_catch;
    sigemptyset(&act.sa_mask); // 清空sa_mask屏蔽字
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0; // 本信号自动屏蔽
    // 注册信号捕捉函数
    int ret = sigaction(SIGINT, &act, &oldact);
    if (ret == -1)
    {
        perror("sigaction:");
        exit(1);
    }

    while (1)
    {
        sleep(1); 
    }
    return 0;
}