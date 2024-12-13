#include <stdio.h>       // 标准输入输出库
#include <fcntl.h>       // 文件控制选项库
#include <sys/mman.h>    // 内存映射操作库
#include <unistd.h>      // 标准符号常量库

int main() {
    // 打开一个文件
    int fd = open("largefile.txt", O_RDONLY);  //open函数返回一个文件描述符，如果文件打开失败，返回-1并输出错误信息。
    if (fd == -1) {
        perror("open");   // 打印错误信息
        return 1;         // 返回错误代码
    }

    // 获取文件的大小
    off_t file_size = lseek(fd, 0, SEEK_END); //lseek函数将文件偏移量设置到文件的末尾 (SEEK_END)，并返回文件的大小。off_t 是一个用于表示文件大小的类型。

    // 将文件映射到内存
    char* mapped_memory = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0); //如果mmap失败，返回MAP_FAILED并输出错误信息。     
    if (mapped_memory == MAP_FAILED) {
        perror("mmap");   // 打印错误信息
        return 1;         // 返回错误代码
    }
    /*  * mmap 的参数如下：
        * NULL：让内核选择映射的起始地址。
        * file_size：映射的大小。
        * PROT_READ：映射的内存区域为只读。
        * MAP_SHARED：对映射内存区域的修改会写回到文件中，并且其他进程对该文件的修改会反映到此映射中。
        * fd：文件描述符。
        * 0：映射的起始偏移量。
        */

    // 通过映射的内存访问文件内容
    printf("First byte: %c\n", mapped_memory[0]);

    // 解除映射
    munmap(mapped_memory, file_size);
    close(fd);

    return 0;   // 返回成功代码
}
