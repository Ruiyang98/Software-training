#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// #define POOL_SIZE 1024  // 默认内存池大小
// #define ALIGNMENT 8     // 对齐大小

typedef struct {
    char *pool;         // 内存池指针
    size_t size;        // 内存池大小
    char *free_ptr;     // 下一个空闲内存的位置
    size_t free_size;   // 剩余可用内存大小
} MemoryPool;


MemoryPool *create_memory_pool(size_t size);//创建内存池
void *pool_alloc(MemoryPool *mp, size_t size);//内存分配函数
void pool_free(MemoryPool *mp);//内存回收函数，通过重置内存池来释放所有内存
size_t align_size(size_t size);//对齐
