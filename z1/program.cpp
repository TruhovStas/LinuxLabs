#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

struct message {
    long mtype; 
    char mtext[100]; 
};

int msgQueueID;

void *clientThread(void *arg) {
    struct message msg;
    
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    
    msg.mtype = 1; 
    snprintf(msg.mtext, sizeof(msg.mtext), "Hello from client thread!");
    
    msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

    msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 2, 0);

    printf("Client Thread received: %s\n", msg.mtext);

    msgctl(msgid, IPC_RMID, NULL);

    pthread_exit(NULL);
}

int main() {
    msgQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    pthread_t thread;
    pthread_create(&thread, NULL, clientThread, NULL);

    struct message msg;

    msgrcv(msgQueueID, &msg, sizeof(msg.mtext), 1, 0);

    printf("Server received: %s\n", msg.mtext);

    msg.mtype = 2; 
    snprintf(msg.mtext, sizeof(msg.mtext), "Hello from server!");

    msgsnd(msgQueueID, &msg, sizeof(msg.mtext), 0);

    pthread_join(thread, NULL);

    msgctl(msgQueueID, IPC_RMID, NULL);

    return 0;
}

