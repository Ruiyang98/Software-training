#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        printf("This is the child process, PID: %d\n", getpid());
    } else if (pid > 0) {
        // 父进程
        printf("This is the parent process, PID: %d\n", getpid());
    } else {
        // 错误处理
        perror("fork failed");
    }

    return 0;
}