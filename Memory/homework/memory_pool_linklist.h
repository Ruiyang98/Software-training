#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct FreeBlock {
    size_t size;
    struct FreeBlock *next;
} FreeBlock;

typedef struct {
    char *pool;         // 内存池指针
    size_t size;        // 内存池大小
    FreeBlock *free_list; // 空闲块链表头指针
} MemoryPool;

//创建内存池
MemoryPool *create_memory_pool(size_t size);

//内存分配函数
void *pool_alloc(MemoryPool *mp, size_t size);

void pool_free(MemoryPool *mp, void *ptr);

void destroy_memory_pool(MemoryPool *mp);

size_t align_size(size_t size);
