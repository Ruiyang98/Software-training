#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 定义一个全局变量，表示关键线程的状态
int critical_thread_alive = 1;  // 假设关键线程最初是活跃的

// 关键线程函数
void* critical_thread_func(void* arg) {
    while (1) {
        printf("关键线程正在运行...\n");
        sleep(2);  // 模拟工作，每2秒输出一次
    }
    return NULL;
}

// 守护线程函数
void* daemon_thread_func(void* arg) {
    while (1) {
        sleep(1);  // 每秒检查一次
        if (!critical_thread_alive) {
            printf("错误：关键线程已经停止！\n");
            break;  // 停止守护线程（也可以重启关键线程等操作）
        }
    }
    return NULL;
}

int main() {
    pthread_t critical_thread, daemon_thread;

    // 创建关键线程
    if (pthread_create(&critical_thread, NULL, critical_thread_func, NULL) != 0) {
        perror("创建关键线程失败");
        exit(1);
    }

    // 创建守护线程
    if (pthread_create(&daemon_thread, NULL, daemon_thread_func, NULL) != 0) {
        perror("创建守护线程失败");
        exit(1);
    }

    // 设置守护线程为守护线程（退出时自动清理）
    pthread_detach(daemon_thread);

    // 模拟关键线程的状态变化
    sleep(5);  // 模拟运行 5 秒
    critical_thread_alive = 0;  // 假设关键线程失败

    // 等待关键线程结束
    pthread_join(critical_thread, NULL);

    return 0;
}