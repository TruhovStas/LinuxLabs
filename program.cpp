#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

vector<pair<int, int>> generateUniqueMultiplicationExamples(int n) {
    vector<pair<int, int>> examples;

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(nullptr)));

    while (examples.size() < n) {
        int num1 = rand() % 8 + 2;  // Генерируем первый множитель от 2 до 9
        int num2 = rand() % 8 + 2;  // Генерируем второй множитель от 2 до 9
        pair<int, int> example(num1, num2);

        // Проверяем, что такой пример ещё не использовался
        if (find(examples.begin(), examples.end(), example) == examples.end()) {
            examples.push_back(example);
        }
    }

    return examples;
}

