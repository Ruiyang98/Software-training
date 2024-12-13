#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSG_KEY 1234
#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key = MSG_KEY;
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    struct msg_buffer message;
    message.msg_type = 1;
    snprintf(message.msg_text, MAX_MSG_SIZE, "Hello from message queue!");

    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Message sent: %s\n", message.msg_text);

    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    printf("Received message: %s\n", message.msg_text);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}