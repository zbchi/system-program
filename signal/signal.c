#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void sig_catch(int signum)
{
    printf("catch you!!\n");
}

int main()
{
    // 注册信号捕捉函数
    signal(SIGINT, sig_catch);

    while (1)
    {
        sleep(1);
    }
    return 0;
}