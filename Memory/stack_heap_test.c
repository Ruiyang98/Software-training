#include <stdio.h>
#include <stdlib.h>

// **数据段**部分
int global_var = 10;  // 存储在已初始化数据段 (.data)
static int static_var = 20;  // 存储在已初始化数据段 (.data)

// **函数声明**部分（这属于文本段 .text）
int add(int a, int b);  // 函数声明，返回值是 int 类型

int main() {
    // **栈区**部分
    int local_var = 30;  // 存储在栈区

    // **堆区**部分
    int *ptr = (int *)malloc(sizeof(int));  // 在堆上分配内存
    if (ptr != NULL) {
        *ptr = 40;  // 存储在堆区
        printf("Heap value: %d\n", *ptr);  // 输出堆区的值
    }

    // 打印数据段中的全局变量和静态变量
    printf("Global variable: %d\n", global_var);
    printf("Static variable: %d\n", static_var);
    printf("Local variable (Stack): %d\n", local_var);

    // 调用文本段中的函数，并获取返回值
    int sum = add(10, 20);
    printf("Sum returned from add function: %d\n", sum);

    // 释放堆上的内存
    free(ptr);

    return 0;
}

// **文本段**部分：返回值为 int 的函数
int add(int a, int b) {
    // **栈区**：函数的局部变量（a, b 和 return_value）存储在栈区
    int return_value = a + b;  // 存储在栈上
    return return_value;  // 返回值通过栈传递
}