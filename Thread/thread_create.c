#include <stdio.h>
//#include <windows.h>
#include <unistd.h>
#include <stdint.h>

#include <stdlib.h>
#include <pthread.h>


// 用于模拟线程的状态
typedef enum {
    THREAD_UNSTARTED,
    THREAD_RUNNING,
    THREAD_SUSPENDED
    } ThreadState;

// 全局变量保存线程状态
ThreadState thr_state = THREAD_UNSTARTED;



// 线程函数：每个新线程将要执行的代码
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is running.\n", thread_id);

    // 模拟一些任务处理时间
    sleep(2); // 让线程休眠2秒以模拟工作

    printf("Thread %d has finished its work.\n", thread_id);
    return NULL; // 返回给主线程的数据 (这里为NULL)
}

// int main() {
//     pthread_t thread;
//     int thread_id = 1;
//     int ret;

//     // 创建线程
//     ret = pthread_create(&thread, NULL, thread_function, &thread_id);
//     if (ret != 0) {
//         perror("Thread creation failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Main thread waiting for the child thread to complete...\n");

//     // 等待线程结束并回收资源
//     void* thread_result;
//     ret = pthread_join(thread, &thread_result);
//     if (ret != 0) {
//         perror("Thread join failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Child thread completed. Main thread exiting.\n");

//     return EXIT_SUCCESS;
// }


// // 模拟线程执行的函数
// uint32_t WINAPI my_thread(LPVOID arg) {
//     for (int x = 0; x < 2; x++) {
//         printf("My Thread\n");
//         Sleep(1000);  // 模拟线程执行中的延迟
//     }
//     return 0;
// }

// 函数用于输出当前线程状态
void print_thread_state(ThreadState state) {
    switch (state) {
        case THREAD_UNSTARTED:
            printf("ThreadState: Unstarted\n");
            break;
        case THREAD_RUNNING:
            printf("ThreadState: Running\n");
            break;
        case THREAD_SUSPENDED:
            printf("ThreadState: Suspended\n");
            break;
    }
}

int main() {
    //HANDLE thr1;
    //DWORD threadId;
    pthread_t thr1;
    uint32_t threadId;

    // 初始状态：线程未启动
    print_thread_state(thr_state);

    // 创建并启动线程
    thr_state = THREAD_RUNNING;
    thr1 = CreateThread(
        NULL,               // 默认安全属性
        0,                  // 默认堆栈大小
        thread_function,          // 线程函数
        NULL,               // 线程函数的参数
        0,                  // 默认创建标志
        &threadId);         // 线程 ID

    if (thr1 == NULL) {
        printf("Error creating thread\n");
        return 1;
    }

    print_thread_state(thr_state);

    // 模拟线程挂起（在 Windows 中没有直接的 suspend 方法，使用 Sleep 来模拟）
    //Sleep(2000);
    sleep(2000);
    thr_state = THREAD_SUSPENDED;
    print_thread_state(thr_state);

    // 模拟线程恢复执行
    //Sleep(2000); // 等待线程恢复执行
    sleep(2000);
    thr_state = THREAD_RUNNING;
    print_thread_state(thr_state);

    // 等待线程结束
    //WaitForSingleObject(thr1, INFINITE);
    pthread_join(thr1, NULL);

    // 关闭线程句柄
    CloseHandle(thr1);

    return 0;
}