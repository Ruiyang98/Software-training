#include "priority_queue.h"
#include <stdio.h>
#include <string.h>

// 交换两个任务的函数
void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化函数，确保最小堆性质
void heapify(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 找出三个节点中优先级最小的节点
    if (left < pq->size && pq->tasks[left].priority < pq->tasks[smallest].priority)
        smallest = left;
    if (right < pq->size && pq->tasks[right].priority < pq->tasks[smallest].priority)
        smallest = right;
    if (smallest != i) {
        swap(&pq->tasks[i], &pq->tasks[smallest]);
        heapify(pq, smallest);
    }
}

// 初始化优先级队列
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// 插入新任务到优先级队列
void insertTask(PriorityQueue* pq, Task task) {
    if (pq->size == MAX_TASKS) {
        printf("队列已满，无法插入任务\n");
        return;
    }
    int i = pq->size++;
    pq->tasks[i] = task;

    // 上移操作，保持最小堆性质
    while (i != 0 && pq->tasks[i].priority < pq->tasks[(i - 1) / 2].priority) {
        swap(&pq->tasks[i], &pq->tasks[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 提取优先级最高的任务
Task extractMinTask(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("队列为空\n");
        Task null_task = { .priority = -1, .id = -1, .cpu_time = 0, .memory = 0, .execution_time = 0, .aging_counter = 0, .name = "" };
        return null_task;
    }
    Task root = pq->tasks[0];
    pq->tasks[0] = pq->tasks[--pq->size];
    heapify(pq, 0); // 调整堆
    return root;
}

// 调整优先级以防止任务饿死
void adjustPriority(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        pq->tasks[i].aging_counter++;
        if (pq->tasks[i].aging_counter > 5) {
            pq->tasks[i].priority--;
            pq->tasks[i].aging_counter = 0;
        }
    }
    // 重新堆化
    for (int i = (pq->size / 2) - 1; i >= 0; i--) {
        heapify(pq, i);
    }
}
