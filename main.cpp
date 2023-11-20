#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <dlfcn.h> 
using namespace std;

int main() {
    void* lib = dlopen("libprogram.so", RTLD_LAZY);
    
    if (!lib) {
        cerr << "Ошибка загрузки библиотеки: " << dlerror() << endl;
        return 1;
    }
    
    typedef vector<pair<int, int>> (*GenerateUniqueMultiplicationExamples)(int);
    GenerateUniqueMultiplicationExamples generateUniqueMultiplicationExamples = reinterpret_cast<GenerateUniqueMultiplicationExamples>(dlsym(lib, "_Z36generateUniqueMultiplicationExamplesi"));
    
    if (!generateUniqueMultiplicationExamples) {
        cerr << "Ошибка загрузки функции: " << dlerror() << endl;
        dlclose(lib);
        return 1;
    }


    int n = 15;  // Количество уникальных примеров, которые нужно сгенерировать
    vector<pair<int, int>> uniqueExamples = generateUniqueMultiplicationExamples(n);

    // Выводим сгенерированные примеры на экран
    for (const auto& example : uniqueExamples) {
        cout << example.first << " * " << example.second << " = " << (example.first * example.second) << endl;
    }

    return 0;
}

