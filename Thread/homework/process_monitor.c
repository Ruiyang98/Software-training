#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

void log_restart(int restart_count) {
    FILE *log_file = fopen("process_monitor.log", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    time_t now;
    time(&now);
    fprintf(log_file, "Process restarted at %sRestart count: %d\n", ctime(&now), restart_count);
    fclose(log_file);
}

void start_process(char *process_name, char **args) {
    if (execvp(process_name, args) == -1) {
        perror("Error executing process");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <process_name> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *process_name = argv[1];
    char **args = &argv[1];

    int restart_count = 0;
    pid_t pid;
    
    while (1) {
        pid = fork();
        if (pid == 0) {
            // 子进程：启动进程
            start_process(process_name, args);
            //printf("子进程启动，进程号为%d\n", pid);
        } else if (pid > 0) {
            // 父进程：监控子进程
            int status;
            waitpid(pid, &status, 0);
            
            //用宏检查子进程的退出状态
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                restart_count++;
                log_restart(restart_count);
                printf("Process %s terminated. Restarting... (count: %d)\n", process_name, restart_count);
            } else {
                printf("Unexpected status for process %s. Exiting...\n", process_name);
                return EXIT_FAILURE;
            }
        } else {
            // fork失败
            perror("Error forking process");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
