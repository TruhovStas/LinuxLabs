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

    // Получаем идентификатор общей памяти
    int shmid = shmget(key, SHM_SIZE, 0666);
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

    // Получаем идентификатор семафора
    int semid = semget(key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Захватываем семафор
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(semid, &sem_op, 1);

        // Читаем сообщение и определяем от кого оно пришло
        if (strncmp(data, "1: ", 3) == 0) {
            printf("Получено сообщение от Сервера 1: %s\n", data + 3);
        } else if (strncmp(data, "2: ", 3) == 0) {
            printf("Получено сообщение от Сервера 2: %s\n", data + 3);
        } else {
            printf("Некорректное сообщение: %s\n", data);
        }

        // Освобождаем семафор
        sem_op.sem_op = 1;
        semop(semid, &sem_op, 1);

        sleep(1);
    }

    // Освобождаем ресурсы
    shmdt(data);

    return 0;
}

