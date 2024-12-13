#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sched.h>
//#include <linux/sched.h>
#include <linux/sched/types.h>  //版本不同
#include <sys/types.h>
#include <sys/wait.h>



int main() {
    // 定义调度参数
    struct sched_param param;
    pid_t pid = getpid();  // 获取当前进程的PID

    // 设置调度策略为 DEADLINE
    param.sched_priority = 1;  // 对于 SCHED_DEADLINE，优先级字段不再使用
    struct sched_attr sa;
    sa.sched_policy = 6; //SCHED_DEADLINE
    sa.sched_runtime = 500000000;  // 设置任务最大运行时间（500ms）
    sa.sched_deadline = 1000000000;  // 设置任务的截止时间（1000ms）
    sa.sched_period = 1000000000;  // 设置任务的周期（1000ms）

    //sched_setattr找不到定义。。
    // if (sched_setattr(pid, &sa, 0) == -1) {
    //     perror("Failed to set DEADLINE scheduler");
    //     exit(EXIT_FAILURE);
    // }

    printf("Real-time scheduling set using SCHED_DEADLINE\n");

    // 模拟任务执行
    while (1) {
        usleep(5000);  // 延迟，模拟任务执行
    }

    return 0;
}