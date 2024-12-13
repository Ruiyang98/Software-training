#include "memory_pool_linklist.h"

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
    mp->free_list = (FreeBlock *)mp->pool;
    mp->free_list->size = size;
    mp->free_list->next = NULL;

    return mp;
}

void *pool_alloc(MemoryPool *mp, size_t size) {
    size = align_size(size);  // 对齐分配大小
    FreeBlock *prev = NULL;
    FreeBlock *current = mp->free_list;

    while (current != NULL) { //遍历空闲链表
        if (current->size >= size) {
            if (current->size > size + sizeof(FreeBlock)) {
                // 剩余空间足够大，可以分割空闲块
                FreeBlock *new_block = (FreeBlock *)((char *)current + size);
                new_block->size = current->size - size;
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }

            // 从空闲链表中移除该块
            if (prev == NULL) {
                mp->free_list = current->next;// 如果 prev 为空，说明分配的是头节点
            } else {
                prev->next = current->next;// 否则，将 prev 的 next 指针指向当前块的 next 指针
            }

            return (void *)current;
        }

        prev = current;
        current = current->next;
    }

    return NULL;  // 内存不足
}

void pool_free(MemoryPool *mp, void *ptr) {
    if (ptr == NULL) {
        return;
    }

    FreeBlock *block = (FreeBlock *)ptr;
    block->next = mp->free_list;
    mp->free_list = block;
}

void destroy_memory_pool(MemoryPool *mp) {
    if (mp) {
        free(mp->pool);
        free(mp);
    }
}

size_t align_size(size_t size) {
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

int main() {
    size_t pool_size = POOL_SIZE;
    MemoryPool *mp = create_memory_pool(pool_size);
    if (mp == NULL) {
        return 1;
    }

    char *object1 = (char *)pool_alloc(mp, 16);
    if (object1 != NULL) {
        printf("Object 1 allocated\n");
    } else {
        printf("Failed to allocate Object 1\n");
    }

    char *object2 = (char *)pool_alloc(mp, 32);
    if (object2 != NULL) {
        printf("Object 2 allocated\n");
    } else {
        printf("Failed to allocate Object 2\n");
    }

    pool_free(mp, object1);
    printf("Object 1 freed\n");

    char *object3 = (char *)pool_alloc(mp, 8);
    if (object3 != NULL) {
        printf("Object 3 allocated\n");
    } else {
        printf("Failed to allocate Object 3\n");
    }

    destroy_memory_pool(mp);

    return 0;
}