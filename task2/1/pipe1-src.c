#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define WAIT_SECS 5

int main (int argc, char ** argv)
{
    int i, fd;
    
    if (argc < 2) {
        fprintf (stderr, "src: Too few arguments\n");
        return 1;
    }

    fd = atoi (argv[1]);
    fprintf (stderr, "Wait please");
    
    for (i = 0; i < WAIT_SECS; i++, sleep (1))
        fprintf (stderr, ".");

    fprintf (stderr, "\n");

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

    // Создание строки для передачи
    char message[1024];
    snprintf(message, sizeof(message), "%s%s%s\nWeek: 12\n", os_info, date_time, calendar);

    // Запись в файловый дескриптор
    if (write(fd, message, strlen(message)) == -1) {
        fprintf(stderr, "src: write() error\n");
        return 1;
    }

    close(fd);
    return 0;
}
