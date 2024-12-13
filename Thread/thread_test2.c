#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int shared_data = 0;

void* thread1(void* arg) {
    pthread_mutex_lock(&mutex);
    while (shared_data != 1) {  // 等待条件满足
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread 1: Shared data is 1, proceeding...\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&mutex);
    shared_data = 1;  // 改变条件
    pthread_cond_signal(&cond);  // 唤醒等待的线程
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}