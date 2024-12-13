#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 1024  // 定义内存池大小
#define OBJECT_SIZE 16  // 每个对象的大小

char memory_pool[POOL_SIZE];  // 定义内存池
char *free_ptr = memory_pool; // 指向下一个可用的内存位置

void* pool_alloc(size_t size) {
    if (free_ptr + size > memory_pool + POOL_SIZE) {
        return NULL;  // 内存池不足
    }
    void* allocated_mem = free_ptr;
    free_ptr += size;  // 更新内存池指针
    return allocated_mem;
}

int main() {
    // 使用内存池分配内存
    char* object1 = (char*)pool_alloc(OBJECT_SIZE);
    if (object1 != NULL) {
        printf("Object 1 allocated\n");
    }

    char* object2 = (char*)pool_alloc(OBJECT_SIZE);
    if (object2 != NULL) {
        printf("Object 2 allocated\n");
    }

    return 0;
}
