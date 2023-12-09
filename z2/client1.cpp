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
    // Создаем очереди сообщений
    int msgQueueID1 = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    int msgQueueID2 = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    printf("Process 1: msgQueueID1 = %d, msgQueueID2 = %d\n", msgQueueID1, msgQueueID2);

    struct message msg;

    while (1) {
        msgrcv(msgQueueID1, &msg, sizeof(msg.mtext), 1, 0);

        printf("Received from Process 2: %s\n", msg.mtext);

        msg.mtype = 2;
        printf("Enter message for Process 2: ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);

        msgsnd(msgQueueID2, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}

