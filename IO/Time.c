#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <fcntl.h>
#include <unistd.h>

int read_large_file(const char *file_path) {

    // 用不同的IO模型读取文件
   int fd = open("test.txt", O_RDONLY);
    if(fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));

    if(bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO, buffer, bytes_read);

    close(fd);
    return 0;
}

int main() {
    const char *file_path = "test.txt";  //替换为你的文件路径

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    read_large_file(file_path);

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Reading the file took %.6f seconds.\n", elapsed_time);

    return 0;
}



