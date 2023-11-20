#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define FIFO_NAME "myfifo"

int main(void) {
    int fifo;
    
    fifo = open(FIFO_NAME, O_WRONLY);
    if (fifo == -1) {
        fprintf(stderr, "Cannot open fifo\n");
        return 1;
    }

    // Определение информации об операционной системе и ядре
    char os_info[256];
    snprintf(os_info, sizeof(os_info), "OS: %s, Kernel: %s\n", getenv("OSTYPE"), getenv("KERNEL_VERSION"));

    // Получение системной даты и времени
    FILE *date_pipe = popen("date", "r");
    char date_time[256];
    fgets(date_time, sizeof(date_time), date_pipe);
    pclose(date_pipe);

    // Получение календаря
    FILE *cal_pipe = popen("cal", "r");
    char calendar[512];
    fgets(calendar, sizeof(calendar), cal_pipe);
    pclose(cal_pipe);

    // Создание строки для записи в FIFO
    char message[1024];
    snprintf(message, sizeof(message), "%s%s%s\nWeek: 12\n", os_info, date_time, calendar);

    // Запись в FIFO
    if (write(fifo, message, strlen(message)) == -1) {
        fprintf(stderr, "write() error\n");
        close(fifo);
        return 1;
    }

    close(fifo);
    return 0;
}
