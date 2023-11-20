#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILENAME "myfile"

int main(void) {
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0640);

    if (fd == -1) {
        fprintf(stderr, "open() error\n");
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

    // Создание строки для записи в файл
    char message[1024];
    snprintf(message, sizeof(message), "%s%s%s\nWeek: 12\n", os_info, date_time, calendar);

    // Запись в файловый дескриптор
    if (write(fd, message, strlen(message)) == -1) {
        fprintf(stderr, "write() error\n");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}
