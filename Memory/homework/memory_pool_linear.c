#include "memory_pool_linear.h"

#define POOL_SIZE 1024  // 默认内存池大小
#define ALIGNMENT 8     // 对齐大小


MemoryPool *create_memory_pool(size_t size) {
    MemoryPool *mp = (MemoryPool *)malloc(sizeof(MemoryPool));
    if (mp == NULL) {
        perror("Failed to create memory pool");
        return NULL;
    }
    
    mp->pool = (char *)malloc(size);
    if (mp->pool == NULL) {
        perror("Failed to allocate memory for pool");
        free(mp);
        return NULL;
    }

    mp->size = size;
    mp->free_ptr = mp->pool;
    mp->free_size = size;
    return mp;
}


void *pool_alloc(MemoryPool *mp, size_t size) {
    size = align_size(size);  // 对齐分配大小
    if (mp->free_size < size) {
        return NULL;  // 内存不足
    }

    void *allocated_mem = mp->free_ptr;
    mp->free_ptr += size;
    mp->free_size -= size;
    return allocated_mem;
}


void pool_free(MemoryPool *mp) {
    if (mp) {
        free(mp->pool);
        free(mp);
    }
}


size_t align_size(size_t size) {
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

// int main() {
//     size_t pool_size = POOL_SIZE;
//     MemoryPool *mp = create_memory_pool(pool_size);
//     if (mp == NULL) {
//         return 1;
//     }

//     char *object1 = (char *)pool_alloc(mp, 16);
//     if (object1 != NULL) {
//         printf("Object 1 allocated\n");
//     } else {
//         printf("Failed to allocate Object 1\n");
//     }

//     char *object2 = (char *)pool_alloc(mp, 32);
//     if (object2 != NULL) {
//         printf("Object 2 allocated\n");
//     } else {
//         printf("Failed to allocate Object 2\n");
//     }

//     pool_free(mp);

//     return 0;
// }
