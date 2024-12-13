#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ARRAY_SIZE 10000
#define NUM_THREADS 4

int main() {
    int array[ARRAY_SIZE];
    int result[ARRAY_SIZE];

    // 用随机数填充数组
    srand(time(0));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100; // 随机数范围在 0 到 99 之间
    }

    // 并行计算每个数字的平方
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result[i] = array[i] * array[i];
    }

    // 输出新数组的前十个结果
    printf("新数组的前十个结果:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
