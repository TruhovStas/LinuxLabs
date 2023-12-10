#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 128

int main() {
    key_t key = ftok("shmfile", 65);

    // Создаем общую память
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Получаем указатель на разделяемую память
    char* data = (char*)shmat(shmid, (void*)0, 0);
    if (data == (char*)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Создаем семафор
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем начальное значение семафора
    semctl(semid, 0, SETVAL, 1);

    while(1)
    {
        // Захватываем семафор
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(semid, &sem_op, 1);

        // Сервер 1 пишет сообщение
        strcpy(data, "1: Привет!");

        // Освобождаем семафор
        sem_op.sem_op = 1;
        semop(semid, &sem_op, 1);
        
        printf("записано");
        sleep(2);
    }
    



    // Освобождаем ресурсы
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

