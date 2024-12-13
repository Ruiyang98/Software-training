#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "priority_queue.h"

int availableCPU = 100;     // 系统总 CPU 时间
int availableMemory = 1024; // 系统总内存
pthread_mutex_t lock;       // 互斥锁保护资源分配

// 执行任务的函数
void* executeTask(void* arg) {
    Task task = *(Task*)arg;

    printf("执行任务: ID=%d, 名称=%s, 优先级=%d, 执行时间=%d, CPU=%d, 内存=%d\n",
           task.id, task.name, task.priority, task.execution_time, task.cpu_time, task.memory);

    // 模拟任务执行时间
    sleep(task.execution_time);

    // 任务执行完毕，释放资源
    pthread_mutex_lock(&lock);
    availableCPU += task.cpu_time;
    availableMemory += task.memory;
    pthread_mutex_unlock(&lock);

    printf("任务完成: ID=%d\n", task.id);
    pthread_exit(NULL);
}

// 分配资源的函数
int allocateResources(Task* task) {
    pthread_mutex_lock(&lock);
    if (task->cpu_time <= availableCPU && task->memory <= availableMemory) {
        availableCPU -= task->cpu_time;
        availableMemory -= task->memory;
        pthread_mutex_unlock(&lock);
        return 1;
    }
    pthread_mutex_unlock(&lock);
    return 0;
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);
    pthread_mutex_init(&lock, NULL);

    // 创建任务数组
    Task tasks[] = {
        { .id = 1, .priority = 3, .cpu_time = 10, .memory = 100, .execution_time = 5, .aging_counter = 0, .name = "Task1" },
        { .id = 2, .priority = 1, .cpu_time = 20, .memory = 200, .execution_time = 3, .aging_counter = 0, .name = "Task2" },
        { .id = 3, .priority = 4, .cpu_time = 15, .memory = 150, .execution_time = 2, .aging_counter = 0, .name = "Task3" },
        { .id = 4, .priority = 2, .cpu_time = 30, .memory = 300, .execution_time = 4, .aging_counter = 0, .name = "Task4" }
    };

    // 插入任务到优先级队列
    for (int i = 0; i < sizeof(tasks) / sizeof(tasks[0]); i++) {
        insertTask(&pq, tasks[i]);
    }

    // 执行任务调度
    while (pq.size > 0) {
        adjustPriority(&pq); // 调整优先级以防止任务饿死
        Task task = extractMinTask(&pq);
        if (allocateResources(&task)) {
            pthread_t thread;
            pthread_create(&thread, NULL, executeTask, (void*)&task);
            pthread_detach(thread);
        } else {
            // 如果资源不够，将任务重新插入队列
            insertTask(&pq, task);
        }
        sleep(1); // 避免过快的调度循环
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
