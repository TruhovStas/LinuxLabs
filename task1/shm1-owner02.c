#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define SHMEM_SIZE 4096

int main()
{
    int shm_id;
    char *shm_buf;
    struct shmid_ds ds;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <shm_id>\n", argv[0]);
        return 1;
    }

    // Получаем идентификатор сегмента из аргумента командной строки
    shm_id = atoi(argv[1]);

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
    strcat(shm_buf, "Hello from owner02!\n");

    printf("Press <Enter> to exit...");
    fgetc(stdin);

    // Отсоединяем сегмент от адресного пространства
    shmdt(shm_buf);

    // Удаляем сегмент общей памяти
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
