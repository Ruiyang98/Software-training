#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

void write_data(int fd, size_t bytes_to_write, int use_lseek) {
    char *data = malloc(bytes_to_write);
    if (data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Fill data with a known pattern for easy verification
    memset(data, 'A', bytes_to_write);

    while (bytes_to_write > 0) {
        ssize_t bytes_written;
        if (use_lseek) {
            if (lseek(fd, 0, SEEK_END) == -1) {
                perror("lseek");
                free(data);
                exit(EXIT_FAILURE);
            }
        }

        bytes_written = write(fd, data, bytes_to_write);
        if (bytes_written == -1) {
            perror("write");
            free(data);
            exit(EXIT_FAILURE);
        }

        bytes_to_write -= bytes_written;
    }

    free(data);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <filename> <bytes> [x]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    size_t bytes_to_write = strtoul(argv[2], NULL, 10);
    int use_lseek = (argc == 4 && strcmp(argv[3], "x") == 0);

    int flags = O_WRONLY | O_CREAT;
    if (!use_lseek) {
        flags |= O_APPEND;
    }

    int fd = open(filename, flags, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    write_data(fd, bytes_to_write, use_lseek);

    close(fd);
    return EXIT_SUCCESS;
}