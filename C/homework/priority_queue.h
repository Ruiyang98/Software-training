#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "task.h"

#define MAX_TASKS 100  // 定义最大任务数

// 优先级队列结构体
typedef struct {
    Task tasks[MAX_TASKS];  // 任务数组
    int size;               // 当前任务数
} PriorityQueue;

// 初始化队列
void initQueue(PriorityQueue* pq);

// 插入任务
void insertTask(PriorityQueue* pq, Task task);

// 提取优先级最高的任务
Task extractMinTask(PriorityQueue* pq);

// 调整优先级以防止任务饥饿
void adjustPriority(PriorityQueue* pq);

#endif
