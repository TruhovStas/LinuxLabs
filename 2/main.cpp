#include <iostream>
#include <csignal>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

int score = 0; // Общий счет в игре

void alarmHandler1(int signum) {
    int randomScore = rand() % 10 + 1;
    score += randomScore;

    std::cout << "Первый игрок добавил " << randomScore << ". Общий счет: " << score << std::endl;
}

void alarmHandler2(int signum) {
    int randomScore = rand() % 10 + 1; 
    score -= randomScore;

    std::cout << "Второй игрок отнял " << randomScore << ". Общий счет: " << score << std::endl;
}

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел

    int moves = 10; // Количество ходов

    while (moves > 0) {
        signal(SIGALRM, alarmHandler1);
        alarm(1);
        sleep(1);

        signal(SIGALRM, alarmHandler2);
        alarm(1);
        sleep(1);

        moves--;
    }

    // Определение победителя
    if (score > 0) {
        std::cout << "Выиграл первый игрок!" << std::endl;
    } else if (score < 0) {
        std::cout << "Выиграл второй игрок!" << std::endl;
    } else {
        std::cout << "Ничья! Оба игрока набрали одинаковое количество очков." << std::endl;
    }

    return 0;
}

