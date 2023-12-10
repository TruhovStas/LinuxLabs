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

    // Создаем первый сегмент общей памяти
    int shmid1 = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid1 == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Получаем указатель на первый сегмент общей памяти
    char* data1 = (char*)shmat(shmid1, (void*)0, 0);
    if (data1 == (char*)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Создаем второй сегмент общей памяти
    int shmid2 = shmget(key + 1, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid2 == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Получаем указатель на второй сегмент общей памяти
    char* data2 = (char*)shmat(shmid2, (void*)0, 0);
    if (data2 == (char*)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Создаем семафор
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }


    while (1) {
        // Ждем, пока второй процесс освободит семафор
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(semid, &sem_op, 1);

        // Читаем из второго сегмента и пишем в первый
        printf("Процесс 2: %s\n", data2);
        printf("Введите сообщение для отправки процессу 2: ");
        fgets(data1, SHM_SIZE, stdin);

        // Освобождаем семафор для второго процесса
        sem_op.sem_op = 1;
        semop(semid, &sem_op, 1);
    }

    // Освобождаем ресурсы
    shmdt(data1);
    shmdt(data2);
    shmctl(shmid1, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

