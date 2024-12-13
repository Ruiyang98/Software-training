#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    fd_set read_fds;
    struct timeval timeout;

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);
    timeout.tv_sec = 5; // 设置超时时间为5秒
    timeout.tv_usec = 0;

    int ready = select(fd + 1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1)
    {
        perror("Error with select");
        close(fd);
        return 1;
    }
    else if (ready == 0)
    {
        printf("No data within 5 seconds\n");
    }
    else
    {
        if (FD_ISSET(fd, &read_fds))
        {
            char buffer[100];
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
            if (bytes_read > 0)
            {
                write(STDOUT_FILENO, buffer, bytes_read);
            }
        }
    }

    close(fd);
    return 0;
}
