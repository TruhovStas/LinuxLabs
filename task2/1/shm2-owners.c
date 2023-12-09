#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHMEM_SIZE 4096

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = 0;
    semop(sem_id, &sem_buf, 1);
}

void sem_signal(int sem_id) {
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = 0;
    semop(sem_id, &sem_buf, 1);
}

int main() {
    int shm_id;
    char *shm_buf;
    int sem_id;

    // Создаем сегмент общей памяти
    shm_id = shmget(IPC_PRIVATE, SHMEM_SIZE, IPC_CREAT | IPC_EXCL | 0600);

    if (shm_id == -1) {
        fprintf(stderr, "shmget() error\n");
        return 1;
    }

    // Присоединяем сегмент к адресному пространству процесса
    shm_buf = (char *)shmat(shm_id, NULL, 0);

    if (shm_buf == (char *)-1) {
        fprintf(stderr, "shmat() error\n");
        return 1;
    }

    // Создаем семафор
    sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    union semun sem_union;
    sem_union.val = 1;
    semctl(sem_id, 0, SETVAL, sem_union);

    // Процесс владельца 1
    if (fork() == 0) {
        // Дочерний процесс пишет в общий сегмент
        sem_wait(sem_id);
        strcat(shm_buf, "Message from owner01\n");
        sem_signal(sem_id);
    } else {
        // Родительский процесс пишет в общий сегмент
        sem_wait(sem_id);
        strcat(shm_buf, "Message from owner02\n");
        sem_signal(sem_id);

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Отсоединяем сегмент от адресного пространства
        shmdt(shm_buf);
        
        // Удаляем сегмент общей памяти
        shmctl(shm_id, IPC_RMID, NULL);
        
        // Удаляем семафор
        semctl(sem_id, 0, IPC_RMID);
    }

    return 0;
}
