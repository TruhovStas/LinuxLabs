#include <iostream>
#include <csignal>
#include <unistd.h>

double accountBalance = 100.0;

void updateBalance(int signum) {
    accountBalance *= 1.1;
    std::cout << "Обновлённый баланс: " << accountBalance << std::endl;
}

int main() {
    signal(SIGUSR1, updateBalance);

    while (true) { 
        pause();
    }

    return 0;
}

