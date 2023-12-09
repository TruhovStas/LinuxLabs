#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int shm_id;
    char *shm_buf;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <shm_id>\n", argv[0]);
        return 1;
    }

    // Получаем идентификатор сегмента из аргумента командной строки
    shm_id = atoi(argv[1]);
    shm_buf = (char *)shmat(shm_id, 0, 0);

    if (shm_buf == (char *)-1) {
        fprintf(stderr, "shmat() error\n");
        return 1;
    }

    // Выводим сообщение из общего сегмента
    printf("Message: %s\n", shm_buf);

    // Отсоединяем сегмент от адресного пространства
    shmdt(shm_buf);

    return 0;
}
