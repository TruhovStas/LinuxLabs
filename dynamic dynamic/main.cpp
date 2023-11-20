#include <iostream>
#include <dlfcn.h> 

int main() {
    // Открываем динамическую библиотеку
    void* lib = dlopen("/home/maksim/Документы/GitHub/SP/Matskevich/dynamic dynamic/libprogram.so", RTLD_LAZY);
    
    if (!lib) {
        std::cerr << "Ошибка загрузки библиотеки: " << dlerror() << std::endl;
        return 1;
    }
    
    // Загрузка функции из библиотеки
    typedef void (*PlayGameFunc)(int, int, int);
    PlayGameFunc playGame = reinterpret_cast<PlayGameFunc>(dlsym(lib, "_Z8playGameiii"));
    
    if (!playGame) {
        std::cerr << "Ошибка загрузки функции: " << dlerror() << std::endl;
        dlclose(lib);
        return 1;
    }
    
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
    
    // Закрытие библиотеки
    dlclose(lib);
    
    return 0;
}

