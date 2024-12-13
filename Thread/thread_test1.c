#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem;

void* thread1(void* arg) {
    sem_wait(&sem);  // 等待信号量
    printf("Thread 1: Critical section\n");
    sem_post(&sem);  // 释放信号量
    return NULL;
}

void* thread2(void* arg) {
    sem_wait(&sem);
    printf("Thread 2: Critical section\n");
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_init(&sem, 0, 1);  // 初始化信号量，初始值为 1

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);
    return 0;
}