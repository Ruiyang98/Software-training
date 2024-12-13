#ifndef TASK_H
#define TASK_H

// 定义任务结构体，包含任务的基本信息
typedef struct {
    int id;              // 任务 ID
    int priority;        // 任务优先级
    int cpu_time;        // CPU 时间
    int memory;          // 内存需求
    int execution_time;  // 执行时间
    int aging_counter;   // 饥饿保护计数器
    char name[50];       // 任务名称
} Task;

#endif
