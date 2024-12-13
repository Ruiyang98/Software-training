#include <stdio.h>

// 定义第一个版本的结构体，按照从大到小排列
struct Version1 {
    double d; // 8 bytes
    int i;    // 4 bytes
    char c;   // 1 byte
};

//使用pragma，设置对齐方式为1字节
//#pragma pack(1)
struct Version2 {
    char c;   // 1 byte
    double d; // 8 bytes
    int i;    // 4 bytes
};
// struct Version2 {
//     char c;   // 1 byte
//     int i;    // 4 bytes
//     double d; // 8 bytes
// };

int main() {
    printf("Size of struct Version1: %zu bytes\n", sizeof(struct Version1));
    printf("Size of struct Version2: %zu bytes\n", sizeof(struct Version2));

    // 打印每个字段的偏移量，以观察内存布局
    printf("\nMemory layout for struct Version1:\n");
    printf("Offset of 'd': %zu\n", (size_t)&((struct Version1 *)0)->d);
    printf("Offset of 'i': %zu\n", (size_t)&((struct Version1 *)0)->i);
    printf("Offset of 'c': %zu\n", (size_t)&((struct Version1 *)0)->c);

    printf("\nMemory layout for struct Version2:\n");
    printf("Offset of 'd': %zu\n", (size_t)&((struct Version2 *)0)->d);
    printf("Offset of 'i': %zu\n", (size_t)&((struct Version2 *)0)->i);
    printf("Offset of 'c': %zu\n", (size_t)&((struct Version2 *)0)->c);

    return 0;
}