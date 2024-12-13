#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
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