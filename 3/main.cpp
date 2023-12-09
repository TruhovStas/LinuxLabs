#include <iostream>
#include <csignal>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

double accountBalance = 100.0;

void updateBalance(int signum) {
    accountBalance*=1.1;
    std::cout<<"Обновлённый баланс: "<<accountBalance<<std::endl;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Неверное количество параметров" << std::endl;
        return 1;
    }
    int moves = std::stoi(argv[1]);
    signal(SIGALRM, updateBalance);
    while (moves > 0) {
        
        alarm(1);
        sleep(1);
        moves--;
    }

    std::cout<<"Конченый баланс: "<<accountBalance;

    return 0;
}

