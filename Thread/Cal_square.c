#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define ARRAY_SIZE 10000  // 数组大小
#define NUM_THREADS 4   //定义线程数量

// 定义结构体，保存线程的输入参数
typedef struct {
    int *arr;
    //int *output;
    int thread_id;
    int start; //开始处理的数组下标
    int end;
} arr_data;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //全局变量，互斥锁
sem_t sem; //信号量
int counter = 0;//全局计数

void* cal_squares(void* arg) {
    //获取输入参数
    arr_data *data = (arr_data *)arg;
    //int thread_id = data->thread_id;
    //int* arr = data->arr;
    //int* output = data->output;

    for(int i = data->start; i < data->end; i++) {
        data->arr[i] = data->arr[i] * data->arr[i];
    }

    pthread_mutex_lock(&mutex); //如果加在for循环前面，锁住数组，多线程操作就没有意义了
    counter += (data->end - data->start);
    printf("Child process %d has finished, updated counter to %d\n", data->thread_id, counter);
    pthread_mutex_unlock(&mutex);


    sem_post(&sem); // 释放信号量

    pthread_exit(NULL);
    return NULL;
    
}



int main() {
    // 动态分配数组内存
    int *arr = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory for array");
        exit(1);
    }

    // 填充数组，数组内容为从 1 到 10000 的整数
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;  // 数组元素从 1 开始
    }

    // 打印数组的前 10 个元素，避免输出过多
    printf("First 10 elements of the array:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //用多线程求数组的每一个数的平方 

    //初始化信号量和互斥锁（动态）
    sem_init(&sem, 0, 0);

    //创建线程数据结构
    pthread_t threads[NUM_THREADS]; //线程数组
    //int thread_ids[NUM_THREADS]; //记录已有线程ID
    arr_data params[NUM_THREADS];

    //创建并启动线程
    for(int i = 0; i < NUM_THREADS; i++){
        //thread_ids[i] = i;

        //分配每个进程计算的数组下标范围
        params[i].arr = arr;
        params[i].thread_id = i;
        params[i].start = (i * ARRAY_SIZE) / NUM_THREADS;
        params[i].end = ((i + 1) * ARRAY_SIZE) / NUM_THREADS;

        printf("Child process %d will process elements from %d to %d\n", params[i].thread_id, params[i].start, params[i].end - 1);

        if(pthread_create(&threads[i], NULL, cal_squares, (void*)&params[i])) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    // //等待所有线程完成
    // for(int i = 0; i < NUM_THREADS; i++) {
    //     if(pthread_join(threads[i], NULL)) {
    //         fprintf(stderr, "Error joining thread %d\n", i);
    //         return 2;
    //     }
    // }

    // 等待所有线程完成
    printf("Parent process waiting for all child processes to complete...\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        sem_wait(&sem);
    }

    // 打印数组的前 10 个元素，避免输出过多
    printf("First 10 elements of the array:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 打印最终计数器值
    printf("Final counter value: %d\n", counter);

    // 释放资源
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
    free(arr);
    //free(output);

    return 0;
}
