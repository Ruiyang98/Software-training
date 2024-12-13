#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_SIZE (10 * 1024 * 1024) // 10MB 文件大小
#define BUFFER_SIZE 1024             // 缓冲区大小 1KB

// 模拟处理数据：统计字符数量、查找字符和计算校验和
void process_data(const char *buffer, size_t length)
{
    static int total_count = 0;        // 总字符数
    static int target_count = 0;       // 查找目标字符 'A' 的次数
    static unsigned long checksum = 0; // 数据的校验和

    // 遍历缓冲区中的数据，进行处理
    for (size_t i = 0; i < length; i++)
    {
        total_count++; // 累加字符数量
        if (buffer[i] == 'A')
        {
            target_count++; // 查找字符 'A'
        }
        checksum += (unsigned char)buffer[i]; // 计算校验和
    }

    // 输出每次处理的数据统计
    printf("Processed %zu bytes. Total count: %d, 'A' count: %d, Checksum: %lx\n",
           length, total_count, target_count, checksum);
}

// 标准 I/O 读取文件并模拟处理数据
void standard_io_read(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for standard I/O read");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    while (fread(buffer, 1, BUFFER_SIZE, file) > 0)
    {
        // 模拟处理数据
        process_data(buffer, BUFFER_SIZE);
    }

    fclose(file);
}

// 底层 I/O 读取文件并模拟处理数据
void low_level_io_read(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file for low-level I/O read");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        // 模拟处理数据
        process_data(buffer, BUFFER_SIZE);
    }

    close(fd);
}

int main()
{
    const char *filename = "test_file.txt";

    // 标准 I/O 读取并处理数据
    printf("Standard I/O Read Performance and Data Processing:\n");
    standard_io_read(filename);

    // 底层 I/O 读取并处理数据
    printf("\nLow-level I/O Read Performance and Data Processing:\n");
    low_level_io_read(filename);

    return 0;
}
