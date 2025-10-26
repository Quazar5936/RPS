#include <iostream>
#include <vector>
#include <string>

std::string GetUpperString(std::string String) {
    std::string NewString = "";

    for (size_t i = 0; i < String.size(); i++) {
        NewString += std::toupper(String[i]);
    }
    return NewString;
}

void Greeting(void) {
    std::cout << "Добро пожаловать в программу, которая сортирует массивы сортировкой расческой!(16 Вариант)\nПрограмму сделал студент группы 444 Заиграев Семён Сергеевич\n";
}

void CopyArray(double* Array, unsigned long long n, double* NewArray) {
    for (unsigned long long i = 0; i < n; i++) {
        NewArray[i] = Array[i];
    }
}

void ShowArray(double* Array, unsigned long long n) {
    for (unsigned long long i = 0; i < n; i++) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        std::cout << Array[i] << '\n';
    }
}
