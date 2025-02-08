#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

void print_pedset(sigset_t *set)
{
    for (int i = 1; i < 32; i++)
    {
        if (sigismember(set, i))
            putchar('1');
        else
            putchar('0');
    }
    printf("\n");
}

int main()
{
    // 自定义信号集
    sigset_t set, oldset, pedset;

    // 清空自定义信号集
    sigemptyset(&set);

    // 将2号信号添加到自定义信号集
    sigaddset(&set, SIGINT);

    // 借助自定义信号集，设置pcb中的信号屏蔽字中的2号信号为屏蔽
    int ret = sigprocmask(SIG_BLOCK, &set, &oldset);
    if (ret == -1)
    {
        perror("sigprocmask");
        exit(1);
    }

    while (1)
    {
        // 获取当前未决信号集
        ret = sigpending(&pedset);
        if (ret == -1)
        {
            perror("sigpending");
            exit(1);
        }

        print_pedset(&pedset);
        sleep(1);
    }
    return 0;
}