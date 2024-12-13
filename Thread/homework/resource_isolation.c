#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 5
#define MAX_MESSAGE_SIZE 100

//定义结构体，存储进程及其对资源的访问权限
typedef struct {
    int pid;
    int authorized_resources[MAX_RESOURCES];
} ProcessInfo;

typedef struct {
    long msg_type;
    char msg_text[MAX_MESSAGE_SIZE];
} Message;

ProcessInfo process_table[MAX_PROCESSES];
int msg_queue_id;
FILE *log_file;

void init_process_table() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        process_table[i].pid = i + 1; // 模拟PID
        for (int j = 0; j < MAX_RESOURCES; j++) {
            process_table[i].authorized_resources[j] = (i == j) ? 1 : 0; // 每个进程只能访问一个资源
        }
    }
}

void log_access(int pid, const char *resource, const char *action) {
    fprintf(log_file, "Process %d %s %s\n", pid, action, resource);
    fflush(log_file);
}

void send_message(const char *msg_text) {
    Message msg;
    msg.msg_type = 1; // 消息类型设为1
    strncpy(msg.msg_text, msg_text, MAX_MESSAGE_SIZE);
    if (msgsnd(msg_queue_id, &msg, sizeof(msg.msg_text), 0) == -1) {
        perror("Error sending message");
    }
}

void *process_function(void *arg) {
    int pid = *((int *)arg);
    free(arg);
    char resource[20];
    char msg_text[MAX_MESSAGE_SIZE];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (process_table[pid - 1].authorized_resources[i]) {
            snprintf(resource, sizeof(resource), "Resource %d", i + 1);
            log_access(pid, resource, "accessed");

            // 发送消息
            snprintf(msg_text, MAX_MESSAGE_SIZE, "Process %d accessed %s", pid, resource);
            send_message(msg_text);

            sleep(1); // 模拟访问时间
        }
    }
    return NULL;
}

void *communication_function(void *arg) {
    while (1) {
        Message msg;
        if (msgrcv(msg_queue_id, &msg, sizeof(msg.msg_text), 0, 0) != -1) {
            fprintf(log_file, "Message received: %s\n", msg.msg_text);
            fflush(log_file);
        }
    }
    return NULL;
}

int main() {
    log_file = fopen("resource_access.log", "w");
    if (log_file == NULL) {
        perror("Error opening log file");
        return EXIT_FAILURE;
    }

    init_process_table();

    msg_queue_id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msg_queue_id == -1) {
        perror("Error creating message queue");
        return EXIT_FAILURE;
    }

    pthread_t process_threads[MAX_PROCESSES];
    for (int i = 0; i < MAX_PROCESSES; i++) {
        int *pid = malloc(sizeof(int));
        *pid = i + 1;
        pthread_create(&process_threads[i], NULL, process_function, pid);
    }

    pthread_t communication_thread;
    pthread_create(&communication_thread, NULL, communication_function, NULL);

    for (int i = 0; i < MAX_PROCESSES; i++) {
        pthread_join(process_threads[i], NULL);
    }

    pthread_cancel(communication_thread);

    msgctl(msg_queue_id, IPC_RMID, NULL);
    fclose(log_file);
    return 0;
}
