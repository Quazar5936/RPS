#include <limits>
#include <random>
#include <iostream>

void AutoInputForArray(int* Array, unsigned long long Number, std::default_random_engine RandEngine) {
    std::uniform_int_distribution<int> GetRandIntVal{ -100000,100000 };

    for (unsigned long long i = 0; i < Number; i++) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        Array[i] = GetRandIntVal(RandEngine);
        std::cout << Array[i] << '\n';
    }
}


void DoubleArrayInput(int* Array, unsigned long long Number) {
    unsigned long long ArrayIndex = 0;

    while (ArrayIndex < Number) {
        std::cout << "Элемент массива под номером " << ArrayIndex + 1 << ". ";
        std::cin >> Array[ArrayIndex];

        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Вы ввели некорректные данные, пожалуйста, повторите ввод: ";
            std::cin >> Array[ArrayIndex];
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++ArrayIndex;
    }
}

void UnsignedLongLongInput(unsigned long long& Number) {

    std::cin >> Number;

    while (std::cin.fail() || Number <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Вы ввели некорректные данные, пожалуйста, повторите ввод: ";
        std::cin >> Number;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}