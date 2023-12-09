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
        msg.mtype = 2; 
        snprintf(msg.mtext, sizeof(msg.mtext), "Message from Server 2");

        msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

        sleep(3);
    }

    return 0;
}

