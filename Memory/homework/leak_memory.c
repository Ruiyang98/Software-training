#include <stdio.h>
#include <stdlib.h>

void leak_memory() {
    int *ptr = (int *)malloc(100 * sizeof(int));
    if (ptr == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    // 忘记释放内存，导致内存泄漏
}

int main() {
    leak_memory();
    printf("Memory leak simulation complete.\n");
    return 0;
}
