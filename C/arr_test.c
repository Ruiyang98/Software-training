#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr; // 指针指向数组的起始地址

    // 使用数组方式访问元素
    printf("使用数组方式访问元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // 使用指针方式访问元素
    printf("\n使用指针方式访问元素:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }

    // 通过指针修改数组元素
    printf("\n通过指针修改数组元素:\n");
    for (int i = 0; i < 5; i++) {
        *(ptr + i) = *(ptr + i) * 2; // 将每个元素的值翻倍
    }

    // 再次使用数组方式访问元素，查看修改结果
    printf("\n修改后的数组元素（使用数组方式访问）:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
