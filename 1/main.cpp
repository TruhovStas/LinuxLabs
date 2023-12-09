#include <iostream>
#include <csignal>
#include <ctime>
#include <unistd.h>

void alarmHandler1(int signum) {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    std::cout << "First handler says\n"
              << asctime(localTime)<<std::endl;
}

void alarmHandler2(int signum) {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    std::cout << "Second handler says\n"
              << asctime(localTime)<<std::endl;
}

int main() {
    while (true) {
        signal(SIGALRM, alarmHandler1);
        alarm(1);
        sleep(1);
        signal(SIGALRM, alarmHandler2);
        alarm(1);
        sleep(1);
    }

    return 0;
}

