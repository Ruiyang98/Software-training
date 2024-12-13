#define _POSIX_C_SOURCE 199309L



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_TASKS 3

typedef struct {
    int priority;
    int task_id;
    void (*task_func)();
    struct timespec start_time;
    struct timespec end_time;
} Task;

pthread_mutex_t lock;
FILE *log_file;

//记录到日志中
void log_task_start_end_time(Task *task) {
    fprintf(log_file, "Task %d (Priority %d) started at: %ld.%ld\n", task->task_id, task->priority, task->start_time.tv_sec, task->start_time.tv_nsec);
    fprintf(log_file, "Task %d (Priority %d) ended at: %ld.%ld\n", task->task_id, task->priority, task->end_time.tv_sec, task->end_time.tv_nsec);
    fflush(log_file); // 确保日志被及时写入文件
}

void task_function_high() {
    fprintf(log_file, "High priority task is running...\n");
    fflush(log_file);
    sleep(1); // 模拟任务运行时间
}

void task_function_medium() {
    fprintf(log_file, "Medium priority task is running...\n");
    fflush(log_file);
    sleep(2); // 模拟任务运行时间
}

void task_function_low() {
    fprintf(log_file, "Low priority task is running...\n");
    fflush(log_file);
    sleep(3); // 模拟任务运行时间
}

void *task_scheduler(void *arg) {
    Task *tasks = (Task *)arg;
    while (1) {
        for (int i = 0; i < NUM_TASKS; i++) {
            pthread_mutex_lock(&lock);
            if (clock_gettime(CLOCK_MONOTONIC, &tasks[i].start_time) != 0) {
                perror("Error getting start time");
                exit(EXIT_FAILURE);
            }
            tasks[i].task_func();
            if (clock_gettime(CLOCK_MONOTONIC, &tasks[i].end_time) != 0) {
                perror("Error getting end time");
                exit(EXIT_FAILURE);
            }
            log_task_start_end_time(&tasks[i]);
            pthread_mutex_unlock(&lock);
            sleep(3); // 修改时间片为2秒
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_TASKS];
    Task tasks[NUM_TASKS];

    // 打开日志文件
    log_file = fopen("task_scheduler.log", "w");
    if (log_file == NULL) {
        perror("Error opening log file");
        return EXIT_FAILURE;
    }

    // 初始化任务
    tasks[0].priority = 0;
    tasks[0].task_id = 0;
    tasks[0].task_func = task_function_high;

    tasks[1].priority = 1;
    tasks[1].task_id = 1;
    tasks[1].task_func = task_function_medium;

    tasks[2].priority = 2;
    tasks[2].task_id = 2;
    tasks[2].task_func = task_function_low;

    pthread_mutex_init(&lock, NULL);

    // 创建调度线程
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_create(&threads[i], NULL, task_scheduler, (void *)tasks);
    }

    // 等待所有线程完成
    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    // 关闭日志文件
    fclose(log_file);

    return 0;
}
