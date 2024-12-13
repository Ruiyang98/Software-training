#include <stdio.h>
#include <string.h>

void printArray(const char* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

int main() {
    char source[] = "HelloWorld";
    char dest1[20];
    char dest2[20];

    // 使用 memcpy 进行内存拷贝
    printf("使用 memcpy 进行内存拷贝:\n");
    memcpy(dest1, source, strlen(source) + 1); // +1 包括 null 终止符
    printf("Source: ");
    printArray(source, strlen(source) + 1);
    printf("Dest1: ");
    printArray(dest1, strlen(dest1) + 1);

    // 使用 memmove 进行内存拷贝
    printf("\n使用 memmove 进行内存拷贝:\n");
    memmove(dest2, source, strlen(source) + 1); // +1 包括 null 终止符
    printf("Source: ");
    printArray(source, strlen(source) + 1);
    printf("Dest2: ");
    printArray(dest2, strlen(dest2) + 1);

    // 演示 memmove 的适用场景：重叠区域拷贝
    printf("\n演示 memmove 的适用场景：重叠区域拷贝:\n");
    printf("Before memmove, Source: ");
    printArray(source, strlen(source) + 1);
    memmove(source + 2, source, strlen(source) + 1); // 拷贝重叠区域
    printf("After memmove, Source: ");
    printArray(source, strlen(source) + 1);

    return 0;
}
