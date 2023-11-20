#include "program.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void playGame(int minRange, int maxRange, int maxAttempts) {
    int numberToGuess = getRandomNumber(minRange, maxRange);
    int attempts = 0;
    int guess;

    std::cout << "Добро пожаловать в игру 'Попробуй угадать число'!" << std::endl;
    std::cout << "Я загадал число от " << minRange << " до " << maxRange << ". Попробуйте угадать." << std::endl;

    while (attempts < maxAttempts) {
        std::cout << "Попытка " << attempts + 1 << ". Введите вашу догадку: ";
        std::cin >> guess;

        if (guess < minRange || guess > maxRange) {
            std::cout << "Ваша догадка вне диапазона. Попробуйте снова." << std::endl;
            continue;
        }

        attempts++;

        if (guess < numberToGuess) {
            std::cout << "Загаданное число больше." << std::endl;
        } else if (guess > numberToGuess) {
            std::cout << "Загаданное число меньше." << std::endl;
        } else {
            std::cout << "Поздравляем! Вы угадали число " << numberToGuess << " за " << attempts << " попыток." << std::endl;
            break;
        }
    }

    if (attempts == maxAttempts) {
        std::cout << "Game Over. Вы исчерпали все попытки. Загаданное число было " << numberToGuess << "." << std::endl;
    }
}
