#include "program.h"
#include <iostream>

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    int minRange = 1;
    int maxRange = 100;
    int maxAttempts = 10;
    char playAgain;

    do {
        playGame(minRange, maxRange, maxAttempts);
        std::cout << "Хотите сыграть еще раз? (Y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    std::cout << "Спасибо за игру. До свидания!" << std::endl;
    return 0;
}

