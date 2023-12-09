#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define SHMEM_SIZE 4096

int main()
{
    int shm_id;
    char *shm_buf;
    struct shmid_ds ds;

    // Создаем сегмент общей памяти
    shm_id = shmget(IPC_PRIVATE, SHMEM_SIZE, IPC_CREAT | IPC_EXCL | 0600);

    if (shm_id == -1)
    {
        fprintf(stderr, "shmget() error\n");
        return 1;
    }

    // Присоединяем сегмент к адресному пространству процесса
    shm_buf = (char *)shmat(shm_id, NULL, 0);

    if (shm_buf == (char *)-1)
    {
        fprintf(stderr, "shmat() error\n");
        return 1;
    }

    // Узнаем информацию о сегменте
    shmctl(shm_id, IPC_STAT, &ds);

    printf("ID: %d\n", shm_id);

    // Добавляем свое сообщение в общий сегмент
    strcat(shm_buf, "Owner1 say: Grudinskiy Kirill\n");

    printf("Press <Enter> to exit...");
    fgetc(stdin);

    // Отсоединяем сегмент от адресного пространства
    shmdt(shm_buf);

    // Удаляем сегмент общей памяти
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
