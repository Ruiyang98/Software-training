#include <stdio.h>
#include <stdlib.h>
//#include "memory_pool_linear.h"

void leak_memory() {
    int *ptr = (int *)malloc(100 * sizeof(int));
    if (ptr == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    // 忘记释放内存，导致内存泄漏
    //free(ptr);//优化方案
}

void fragmented_memory() {
    for (int i = 0; i < 100; i++) {
        int *ptr = (int *)malloc(10 * sizeof(int));
        if (ptr == NULL) {
            perror("Failed to allocate memory");
            return;
        }
        // 模拟内存碎片
        if (i % 2 == 0) {
            free(ptr);
        }
    }
}


int main() {
    leak_memory();
    //MemoryPool *mp = create_memory_pool(10000);
    //fragmented_memory(mp);
    fragmented_memory();
    //pool_free(mp);
    printf("Memory leak and fragmentation simulation complete.\n");
    return 0;
}
