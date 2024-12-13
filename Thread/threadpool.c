#include <pthread.h>   // 包含pthread库，以便使用多线程功能
#include <stdio.h>      // 包含标准输入输出库，用于打印信息
#include <stdlib.h>     // 包含标准库，提供malloc等函数
#include <unistd.h>     // 包含unistd.h，用于sleep函数（模拟工作）

#define MAX_THREADS 10  // 定义线程池中的最大线程数为10
#define MAX_TASKS 100   // 定义任务队列的最大任务数为100

// 定义任务结构体，用于存储任务函数和任务参数
typedef struct {
    void (*task_func)(void *);  // 任务函数指针，指向执行任务的函数
    void *arg;                  // 任务参数，任务函数的参数
} task_t;

// 定义线程池结构体，包含线程池中的线程和任务队列
typedef struct {
    pthread_t threads[MAX_THREADS];   // 存储线程池中的线程
    task_t task_queue[MAX_TASKS];     // 存储任务队列，最多可容纳MAX_TASKS个任务
    int task_count;                   // 当前队列中的任务数量
    int stop;                         // 标记线程池是否停止
    pthread_mutex_t mutex;           // 互斥锁，用于同步对任务队列的访问
    pthread_cond_t cond;             // 条件变量，用于通知工作线程执行任务
} thread_pool_t;

// 任务执行的函数，模拟执行任务的操作
void task_func(void *arg) {
    printf("Task executing with arg: %d\n", *(int *)arg);  // 打印任务的参数
    sleep(1);  // 模拟任务执行的时间（1秒）
}

// 工作线程函数，负责从任务队列中取出任务并执行
void *worker(void *arg) {
    thread_pool_t *pool = (thread_pool_t *)arg;  // 获取线程池的引用

    while (1) {
        pthread_mutex_lock(&pool->mutex);  // 上锁，确保访问任务队列时的线程安全
        while (pool->task_count == 0 && !pool->stop) {  // 如果任务队列为空且线程池未停止
            pthread_cond_wait(&pool->cond, &pool->mutex);  // 等待任务到来
        }
        if (pool->stop) {  // 如果线程池已停止
            pthread_mutex_unlock(&pool->mutex);  // 解锁
            break;  // 退出线程
        }

        task_t task = pool->task_queue[--pool->task_count];  // 从队列中取出一个任务
        pthread_mutex_unlock(&pool->mutex);  // 解锁

        task.task_func(task.arg);  // 执行任务函数
    }
    return NULL;  // 线程结束返回
}

// 初始化线程池
void pool_init(thread_pool_t *pool) {
    pool->task_count = 0;  // 初始化任务队列为空
    pool->stop = 0;        // 初始化线程池未停止
    pthread_mutex_init(&pool->mutex, NULL);  // 初始化互斥锁
    pthread_cond_init(&pool->cond, NULL);    // 初始化条件变量
    for (int i = 0; i < MAX_THREADS; i++) {  // 创建线程池中的工作线程
        pthread_create(&pool->threads[i], NULL, worker, pool);  // 创建线程并传入线程池
    }
}

// 向线程池添加任务
void pool_add_task(thread_pool_t *pool, void (*task_func)(void *), void *arg) {
    pthread_mutex_lock(&pool->mutex);  // 上锁，确保对任务队列的同步访问
    if (pool->task_count < MAX_TASKS) {  // 如果任务队列未满
        pool->task_queue[pool->task_count].task_func = task_func;  // 添加任务的函数
        pool->task_queue[pool->task_count].arg = arg;  // 添加任务的参数
        pool->task_count++;  // 增加任务计数
        pthread_cond_signal(&pool->cond);  // 通知一个线程开始处理任务
    }
    pthread_mutex_unlock(&pool->mutex);  // 解锁
}

// 停止线程池并等待线程结束
void pool_shutdown(thread_pool_t *pool) {
    pthread_mutex_lock(&pool->mutex);  // 上锁
    pool->stop = 1;  // 设置线程池为停止状态
    pthread_cond_broadcast(&pool->cond);  // 广播条件变量，通知所有线程停止工作
    pthread_mutex_unlock(&pool->mutex);  // 解锁

    for (int i = 0; i < MAX_THREADS; i++) {  // 等待所有线程完成
        pthread_join(pool->threads[i], NULL);  // 等待线程结束
    }
}

int main() {
    thread_pool_t pool;  // 定义线程池
    pool_init(&pool);    // 初始化线程池

    int task1 = 1;
    pool_add_task(&pool, task_func, &task1);  // 向线程池添加任务1

    int task2 = 2;
    pool_add_task(&pool, task_func, &task2);  // 向线程池添加任务2

    sleep(5);  // 主线程等待任务完成

    pool_shutdown(&pool);  // 停止线程池并等待所有线程完成
    return 0;  // 程序结束
}