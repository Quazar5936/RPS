#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include "RPS2.h"



static void CombSort(double* Array, unsigned long long n) {
    double GapFactor = n / FACTOR;
    
    while (GapFactor > 1) {
        unsigned long long Gap = static_cast<unsigned long long>(std::floor(GapFactor)); // Округление шага в меньшую сторону

        for (unsigned long long i = 0, j = Gap; j < n; i++, j++) {
            if (Array[i] > Array[j]) {
                std::swap(Array[i], Array[j]); // Обмен значениями массива

            }
        }

        GapFactor = GapFactor / FACTOR;
    }
}

static void Greeting(void) {
    std::cout << "Добро пожаловать в программу, которая сортирует массивы сортировкой расческой!(16 Вариант)\nПрограмму сделал студент группы 444 Заиграев Семён Сергеевич\n";
}

static void DoubleInput(double* Array, unsigned long long n) {
    unsigned long long i = 0;
    while (i < n) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        std::cin >> Array[i];
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Вы ввели некорректные данные, пожалуйста, повторите ввод: ";
            std::cin >> Array[i];
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++i;
    }
   
}

static void UnsignedLongLongInput(unsigned long long &n) {
     
    std::cin >> n;
    while (std::cin.fail() || n <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Вы ввели некорректные данные, пожалуйста, повторите ввод: ";
        std::cin >> n;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    
}
static void AutoInputForArray(double* Array, unsigned long long n, std::default_random_engine RandEngine) {
    std::uniform_real_distribution<double> GetRandDoubleVal{ -100000,100000 };
    for (unsigned long long i = 0; i < n; i++) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        Array[i] = GetRandDoubleVal(RandEngine);
        std::cout << Array[i] << '\n';
    }
}
static void ShowArray(double* Array, unsigned long long n) {
    for (unsigned long long i = 0; i < n; i++) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        std::cout << Array[i] << '\n';
    }
}

static double * InterfaceOfnAndArrayDataInput(unsigned long long &n) {
    bool UserInAllDataInput = true;
    unsigned long long UsernInputChoice = 0;
    std::uniform_int_distribution<unsigned long long> GetRandVal{ 1,1000 };
    std::default_random_engine RandEngine{ static_cast<unsigned int> (time(NULL))};

   
    bool UsernInput = true;
    while (UsernInput) {
        std::cout << "Ввести количество элементов массива:\n1 - Автоматически\n2 - Вручную\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UsernInputChoice);
        std::cout << "Количество элементов массива: ";
        switch (UsernInputChoice) {
            
        case AutoInput:
            n = GetRandVal(RandEngine);
            std::cout << n << '\n';
            UsernInput = false;
            break;
        case ManualInput:
            UnsignedLongLongInput(n);
            UsernInput = false;
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }
            
    }

    double * NewArray = new double[n] {};
    std::cout << "Память выделена\n";
    bool UserArrayDataInput = true;
    unsigned long long UserArrayDataInputChoice = 0;
    while (UserArrayDataInput) {
        std::cout << "Ввести элементы массива:\n1 - Автоматически\n2 - Вручную\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserArrayDataInputChoice);
        switch (UserArrayDataInputChoice) {
        case AutoInput:
            AutoInputForArray(NewArray, n, RandEngine);
            UserArrayDataInput = false;
            break;
        case ManualInput:
            DoubleInput(NewArray, n);
            UserArrayDataInput = false;
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }

    }

    return NewArray;

}

static void Interface(void) {
    bool UserInMenu = true;
    unsigned long long UserInMenuChoice = 0;
    double* Array = nullptr;
    unsigned long long n = 0;
    bool ArrayIsNotNullptr = false;

    while (UserInMenu) {
        if (ArrayIsNotNullptr) {
            std::cout << "Память очищена\n";
            delete[] Array;
            ArrayIsNotNullptr = false;
        }
        
        std::cout << "Выберите один из нижеперечисленных пунктов:\n1 - Приступить ко вводу данных\n2 - Выйти\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserInMenuChoice);
        switch (UserInMenuChoice) {
        case Start:
            ArrayIsNotNullptr = true;
            Array = InterfaceOfnAndArrayDataInput(n);
            CombSort(Array, n);
            std::cout << "\n\n\nРезультат сортировки:\n";
            ShowArray(Array, n);
            break;
        case Quit:
            UserInMenu = false;
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }
           
    }
}

int main(void){
    setlocale(LC_ALL, "Russian");
    Interface();
    return EXIT_SUCCESS;
}



