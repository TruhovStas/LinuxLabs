#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key = ftok("server_client_communication", 1);
    int msgQueueID = msgget(key, IPC_CREAT | 0666);

    struct message msg;

    while (1) {
        msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 0, 0);

        if (msg.mtype == 1) {
            printf("Received from Server 1: %s\n", msg.mtext);
        } else if (msg.mtype == 2) {
            printf("Received from Server 2: %s\n", msg.mtext);
        }
    }

    return 0;
}

