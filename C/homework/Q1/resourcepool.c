#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 10
#define MAX_CPU 100
#define MAX_MEMORY 1024

typedef struct {
    int id;
    int cpu;
    int memory;
    int isActive;
} Task;

Task taskPool[MAX_TASKS];
int availableCPU = MAX_CPU;
int availableMemory = MAX_MEMORY;

void initTaskPool() {
    for (int i = 0; i < MAX_TASKS; i++) {
        taskPool[i].id = -1; // 表示空闲任务槽
        taskPool[i].isActive = 0;
    }
}

int allocateResources(int cpu, int memory) {
    if (cpu > availableCPU || memory > availableMemory) {
        printf("资源不足，无法分配任务。\n");
        return -1;
    }

    for (int i = 0; i < MAX_TASKS; i++) {
        if (!taskPool[i].isActive) {
            taskPool[i].id = i;
            taskPool[i].cpu = cpu;
            taskPool[i].memory = memory;
            taskPool[i].isActive = 1;
            availableCPU -= cpu;
            availableMemory -= memory;
            printf("任务%d已分配 %d 单位的 CPU 和 %d 单位的内存。\n", i, cpu, memory);
            return i;
        }
    }
    printf("任务池已满，无法分配任务。\n");
    return -1;
}

void releaseResources(int taskId) {
    if (taskId < 0 || taskId >= MAX_TASKS || !taskPool[taskId].isActive) {
        printf("无效的任务 ID。\n");
        return;
    }

    availableCPU += taskPool[taskId].cpu;
    availableMemory += taskPool[taskId].memory;
    taskPool[taskId].id = -1;
    taskPool[taskId].cpu = 0;
    taskPool[taskId].memory = 0;
    taskPool[taskId].isActive = 0;
    printf("任务%d的资源已释放。\n", taskId);
}

void printStatus() {
    printf("当前资源状态：\n");
    printf("可用 CPU：%d\n", availableCPU);
    printf("可用内存：%d\n", availableMemory);
    printf("活动任务：\n");
    for (int i = 0; i < MAX_TASKS; i++) {
        if (taskPool[i].isActive) {
            printf("任务%d: CPU = %d, 内存 = %d\n", i, taskPool[i].cpu, taskPool[i].memory);
        }
    }
}

int main() {
    initTaskPool();
    int task1 = allocateResources(20, 200);
    int task2 = allocateResources(30, 300);
    printStatus();

    releaseResources(task1);
    printStatus();

    int task3 = allocateResources(50, 400);
    printStatus();

    releaseResources(task2);
    releaseResources(task3);
    printStatus();

    return 0;
}
