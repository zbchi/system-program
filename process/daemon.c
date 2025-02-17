#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    pid_t pid;

    pid = fork();
    if (pid > 0)
        exit(0); // 终止父进程

    pid = setsid();
    if (pid == -1)
        perror("fork");

    int ret = chdir("/home/zb");
    if (ret == -1)
        perror("chdir");

    umask(0); // 改变文件访问权限掩码

    close(STDIN_FILENO);                // 关闭标准输入文件描述符
    int fd = open("/dev/null", O_RDWR); // fd=0
    if (fd == -1)
        perror("open");

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    while (1)
    {

        sleep(1);
    }
    return 0;
}