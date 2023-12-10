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

    // Сервер выводит слово "Сервер" и ждет клиента
    while (1) {
        printf("Сервер: %s\n", data);
        sleep(1);
    }

    // Освобождаем ресурсы
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

