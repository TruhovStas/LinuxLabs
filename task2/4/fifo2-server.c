#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO_NAME "myfifo"
#define BUF_SIZE 1024

int main(void) {
    FILE *fifo;
    char *buf;

    if (mkfifo(FIFO_NAME, 0640) == -1) {
        fprintf(stderr, "Can't create fifo\n");
        return 1;
    }

    fifo = fopen(FIFO_NAME, "r");
    if (fifo == NULL) {
        fprintf(stderr, "Cannot open fifo\n");
        return 1;
    }

    buf = (char *)malloc(BUF_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "malloc() error\n");
        return 1;
    }

    // Чтение из FIFO и вывод в консоль
    while (fgets(buf, BUF_SIZE, fifo) != NULL) {
        printf("%s", buf);
    }

    fclose(fifo);
    free(buf);
    unlink(FIFO_NAME);
    return 0;
}
