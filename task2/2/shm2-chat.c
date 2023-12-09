#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHMEM_SIZE 4096

int main() {
    int shm_id1, shm_id2;
    char *shm_buf1, *shm_buf2;

    // Создаем два сегмента общей памяти
    shm_id1 = shmget(IPC_PRIVATE, SHMEM_SIZE, IPC_CREAT | IPC_EXCL | 0600);
    shm_id2 = shmget(IPC_PRIVATE, SHMEM_SIZE, IPC_CREAT | IPC_EXCL | 0600);

    if (shm_id1 == -1 && shm_id2 == -1) {
        fprintf(stderr, "shmget() error\n");
        return 1;
    }

    // Присоединяем сегменты к адресному пространству процесса
    shm_buf1 = (char *)shmat(shm_id1, NULL, 0);
    shm_buf2 = (char *)shmat(shm_id2, NULL, 0);

    if (shm_buf1 == (char *)-1 && shm_buf2 == (char *)-1) {
        fprintf(stderr, "shmat() error\n");
        return 1;
    }

    // Процесс 1 (пишет в первый сегмент, читает из второго)
    if (fork() == 0) {
        // Дочерний процесс пишет в первый сегмент
        strcat(shm_buf1, "Message from process 1\n");

        // Ожидаем, чтобы дать время процессу 2 прочитать
        sleep(2);

        // Дочерний процесс читает из второго сегмента
        printf("Process 1 received: %s\n", shm_buf2);
    } else {
        // Родительский процесс пишет во второй сегмент
        strcat(shm_buf2, "Message from process 2\n");

        // Ждем завершения дочернего процесса
        wait(NULL);

        // Отсоединяем сегменты от адресного пространства
        shmdt(shm_buf1);
        shmdt(shm_buf2);
        
        // Удаляем сегменты общей памяти
        shmctl(shm_id1, IPC_RMID, NULL);
        shmctl(shm_id2, IPC_RMID, NULL);
    }

    return 0;
}

