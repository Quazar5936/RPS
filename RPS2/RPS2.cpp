#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "RPS2.h"

void CombSort(int* Array, unsigned long long n) {
    double GapFactor = n / FACTOR;
    
    while (GapFactor > 1) {
        unsigned long long Gap = static_cast<unsigned long long>(std::floor(GapFactor)); // Округление шага в меньшую сторону

        for (unsigned long long i = 0, j = Gap; j < n; i++, j++) {

            if (Array[i] > Array[j]) {
                int temp = Array[i]; // Обмен значениями массива
                Array[i] = Array[j];
                Array[j] = temp;
            }
        }

        GapFactor = GapFactor / FACTOR;
    }
}

static void SaveArrayInFileInterface(int* Array, unsigned long long ArraySize, int* SortedArray) {
    unsigned long long UserLoadArrayChoice = 0;
    bool UserFileLoad = true;

    while (UserFileLoad) {
        std::cout << "Выберите один из пунктов:\n1 - Сохранить исходный массив в файл\n2 - Сохранить отсортированный массив в файл\n3 - Сохранить оба массива в файлы\n4 - Ничего не сохранять\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserLoadArrayChoice);

        switch (UserLoadArrayChoice) {

            case SaveArray :
                SaveArrayToFile(Array, ArraySize);
                UserFileLoad = false;
                break;
            case SaveSortedArray:
                SaveArrayToFile(SortedArray, ArraySize);
                UserFileLoad = false;
                break;
            case SaveBoth:
                SaveArraysToFile(Array, ArraySize, SortedArray);
                break;
            case DontSave:
                UserFileLoad = false;
                break;
            default:
                std::cout << "Такого пункта не существует, введите новый\n";

        }
    }
}



static std::pair<int*, unsigned long long> UserInterfaceForFileInput(void) {
    std::pair<int*, unsigned long long> FileInputResult;
 
    while (true) {
        std::string FileName;
        std::cout << "Введите название файла: ";
        std::getline(std::cin, FileName);
        bool FileNameIsCorrect = FileNameCheck(FileName);

        if (!FileNameIsCorrect) {
            std::cout << "Название файла некорректно, введите, пожалуйста, корректное\n";
            continue;
        }

        FileInputResult = GetArrayFromFile(FileName);

        if (FileInputResult.first != nullptr && FileInputResult.second != 0) {
            std::cout << "Данные из файла " << FileName << " занесены в массив успешно\nСодержимое массива:\n";
            ShowArray(FileInputResult.first, FileInputResult.second);
            return FileInputResult;
        }

        std::cout << "Попробуйте снова\n";
    }

    return FileInputResult;
}


static int * InterfaceOfArrayAndArraySizeInput(unsigned long long &ArraySize) {
    unsigned long long UserArraySizeInputChoice = 0;
    std::uniform_int_distribution<unsigned long long> GetRandVal{ 1,1000 };
    std::default_random_engine RandEngine{ static_cast<unsigned int> (time(NULL))};
    std::pair<int*, unsigned long long> PairForFileInput;
    int* NewArray = nullptr;
    bool UserSelectedFileInput = false;
    bool UserArraySizeInput = true;

    while (UserArraySizeInput) {
        std::cout << "Ввести количество элементов массива:\n1 - Автоматически\n2 - Вручную\n3 - Загрузить массив из файла\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserArraySizeInputChoice);
        
        switch (UserArraySizeInputChoice) {
            
        case AutoInput:
            std::cout << "Количество элементов массива: ";
            ArraySize = GetRandVal(RandEngine);
            std::cout << ArraySize << '\n';
            UserArraySizeInput = false;
            break;
        case ManualInput:
            std::cout << "Количество элементов массива: ";
            UnsignedLongLongInput(ArraySize);
            UserArraySizeInput = false;
            break;
        case FileInput:
            UserSelectedFileInput = true;
            UserArraySizeInput = false;
            PairForFileInput = UserInterfaceForFileInput();
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }
            
    }
    
    if (!UserSelectedFileInput) {
        NewArray = new int[ArraySize] {};
        unsigned long long UserArrayDataInputChoice = 0;

        while (true) {
            std::cout << "Ввести элементы массива:\n1 - Автоматически\n2 - Вручную\n";
            std::cout << "Ваш выбор: ";
            UnsignedLongLongInput(UserArrayDataInputChoice);
            switch (UserArrayDataInputChoice) {

            case AutoInput:
                AutoInputForArray(NewArray, ArraySize, RandEngine);
                return NewArray;
                break;
            case ManualInput:
                DoubleArrayInput(NewArray, ArraySize);
                return NewArray;
                break;
            default:
                std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
                break;
            }
        }
    }
    
    NewArray = PairForFileInput.first;
    ArraySize = PairForFileInput.second;
    return NewArray;

}

static void MainInterface(void) {
    Greeting();
    unsigned long long UserInMainInterfaceChoice = 0;
    int* Array = nullptr;
    int* SortedArray = nullptr;
    unsigned long long ArraySize = 0;
    bool ArrayIsNotNullptr = false;

    while (true) {
        if (ArrayIsNotNullptr) {
            delete[] Array;
            Array = nullptr;
            delete[] SortedArray;
            SortedArray = nullptr;
            ArrayIsNotNullptr = false;
        }
        
        std::cout << "Выберите один из нижеперечисленных пунктов:\n1 - Приступить ко вводу данных\n2 - Выйти\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserInMainInterfaceChoice);
        switch (UserInMainInterfaceChoice) {

        case Start:
            ArrayIsNotNullptr = true;
            Array = InterfaceOfArrayAndArraySizeInput(ArraySize);
            SortedArray = new int[ArraySize] {};
            CopyArray(Array, ArraySize, SortedArray);
            CombSort(SortedArray, ArraySize);
            std::cout << "\n\n\nРезультат сортировки:\n";
            ShowArray(SortedArray, ArraySize);
            SaveArrayInFileInterface(Array, ArraySize, SortedArray);
            break;
        case Quit:
            return;
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }
           
    }
}

int main(void){
    system("chcp 1251");
    system("cls");
    MainInterface();
    return EXIT_SUCCESS;
}


