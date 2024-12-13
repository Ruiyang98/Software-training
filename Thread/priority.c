#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    struct sched_param param;
    int policy = SCHED_FIFO;  // 设置调度策略为 SCHED_FIFO

    // 设置实时任务的优先级
    // 在 FIFO 策略下，优先级越高的任务越早被调度
    param.sched_priority = 10;  // 设置任务的优先级为 10（较高的优先级）

    // 通过系统调用设置进程的调度策略和优先级
    if (sched_setscheduler(0, policy, &param) == -1) {
        perror("sched_setscheduler");
        exit(1);  // 如果设置失败，输出错误并退出
    }

    // 打印出当前任务的调度策略和优先级
    printf("Task running with FIFO policy and priority %d\n", param.sched_priority);

    // 模拟一个任务的执行
    // 这里可以插入实际的任务代码，下面是一个简单的循环
    // 模拟任务的执行，例如在这里进行一些计算任务，或者实时控制任务等
    int counter = 0;
    while (1) {
        // 每次循环后打印计数器的值
        printf("Counter: %d\n", counter);
        counter++;

        // 为了防止输出过快，加入短暂的休眠，模拟任务处理时间
        // 如果是硬实时任务，这部分可以替换为实际的任务代码
        usleep(100000);  // 睡眠 100 毫秒
    }

    return 0;
}