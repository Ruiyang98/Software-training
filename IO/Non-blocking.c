#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    int fd = open("test.txt", O_RDONLY | O_NONBLOCK);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    ssize_t bytes_read;

    while (1)
    {
        bytes_read = read(fd, buffer, sizeof(buffer));

        if (bytes_read == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // 数据不可用，继续其他操作
                printf("Data not ready, retrying...\n");
            }
            else
            {
                perror("Error reading file");
                close(fd);
                return 1;
            }
        }
        else if (bytes_read == 0)
        {
            // 到达文件结尾
            break;
        }
        else
        {
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        usleep(100000); // 模拟等待，避免 CPU 占用过高
    }

    close(fd);
    return 0;
}