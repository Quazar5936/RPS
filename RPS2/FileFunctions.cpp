#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FileFunctions.h"


bool FileNameCheck(std::string Path) {
    std::vector<std::string> ForbiddenNamesOfFiles{ "CON","PRN", "AUX", "NUL", "COM0", "COM1", "COM2", "COM3", 
                                                    "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "LPT0",
                                                    "LPT1", "LPT2" , "LPT3" , "LPT4" , "LPT5" , "LPT6" , "LPT7",
                                                    "LPT8" , "LPT9" ,"LPTNO", "LPTSCSI" , "COMSCSI" 
    };
    const std::string TxtString = ".TXT";

    const std::string MinShortForbiddenCombination = "CON";
    std::string FileName = "";
    size_t j = Path.size();
    const std::string StopSymbols{ 47,92 };// символы \/

    if (Path.size() < MinShortForbiddenCombination.size()) {
        return true;
    }
    else {
        while ((Path[j] != StopSymbols[0]) && (Path[j] != StopSymbols[1]) && (j > 0)) {
            j--;
        }

        if (j != 0) {
            j++;
        }
        for (j; j < Path.size(); j++) {
            FileName += Path[j];
        }

        const std::string MaxLongForbiddenCombination = "COMSCSI.txt";
        const std::string ForbiddenSymbols{ 47,92,60,62,58,34,124,42,63 }; // Запрещенные символы /\<>:"|*?

        if (FileName.size() > MaxLongForbiddenCombination.size()) {
            return true;
        }

        for (size_t i = 0; i < FileName.size(); i++) {
            for (size_t k = 0; k < ForbiddenSymbols.size(); k++) {

                if (FileName[i] == ForbiddenSymbols[k]) {
                    std::cout << "Недопустимое имя файла\n";
                    return false;
                }
            }
        }
    }
    for (size_t i = 0; i < FileName.size(); i++) {

        if ((GetUpperString(FileName) == ForbiddenNamesOfFiles[i]) || (GetUpperString(FileName) == (ForbiddenNamesOfFiles[i] + TxtString))) {
            return false;
        }
    }

    return true;

}

static bool DeleteFileData(std::string FileName) {
    std::ofstream FileDataDeleter(FileName, std::ios::trunc);

    if (!FileDataDeleter.is_open()) {
        std::cout << "Стереть данные из файла не удалось, выберите другой файл для записи или попробуйте снова\n";
        return false;
    }
    FileDataDeleter.close();
    return true;
}

static bool WriteDataToFile(int* Array, unsigned long long ArraySize,std::string FileName) {

    std::ofstream ArrayDataSaveToFile;
    ArrayDataSaveToFile.open(FileName);

    if (!ArrayDataSaveToFile.is_open()) {
        std::cout << FileName << '\n';
        std::cout << "Файл для записи не открыт, попробуйте ввести название файла снова\n";
        return false;
    }
    ArrayDataSaveToFile << std::to_string(ArraySize);
    ArrayDataSaveToFile << '\n';

    for (unsigned long long i = 0; i < ArraySize; i++) {
        ArrayDataSaveToFile << std::to_string(Array[i]);

        if (i + 1 != ArraySize) {
            ArrayDataSaveToFile << ' ';
        }
    }

    ArrayDataSaveToFile.close();
    std::cout << "Данные успешно записаны в файл...\n";
    return true;
        
}

void SaveArrayToFile(int* Array, unsigned long long ArraySize) {

    while (true) {
        unsigned long long UserEraseFileChoice = 0;
        bool DataIsWrittenToFile = false;
        bool DataIsDeleted = false;
        std::string FileName;

        std::cout << "Введите название файла: ";
        std::getline(std::cin, FileName);
        bool FileNameIsCorrect = FileNameCheck(FileName);

        if (!FileNameIsCorrect) {
            std::cout << "Название файла некорректно, введите, пожалуйста, корректное\n";
            continue;
        }
        std::ifstream CheckFileData(FileName);

        if (!CheckFileData.is_open()) {
            DataIsWrittenToFile = WriteDataToFile(Array, ArraySize, FileName);

            if (!DataIsWrittenToFile) {
                continue;
            }
           
            return;
        }
        CheckFileData.seekg(0, std::ios::end);

        if (CheckFileData.tellg() == 0) {
            CheckFileData.close();
            std::cout << "Файл пуст, приступаю к записи...\n";
            DataIsWrittenToFile = WriteDataToFile(Array, ArraySize, FileName);

            if (!DataIsWrittenToFile) {
                continue;
            }
           
            return;
        }

        else {
            CheckFileData.close();

            while (!DataIsDeleted) {
                std::cout << "Файл не пуст, стереть содержимое?\n1 - Да, cтереть\n2 - Нет, не стирать\n";
                std::cout << "Ваш выбор: ";
                UnsignedLongLongInput(UserEraseFileChoice);
                switch (UserEraseFileChoice) {

                case EraseFileData:
                    DataIsDeleted = DeleteFileData(FileName);

                    if (DataIsDeleted) {
                        std::cout << "Данные стерты из файла, начинаю запись...\n";
                        DataIsWrittenToFile = WriteDataToFile(Array, ArraySize, FileName);
                        
                        if (DataIsWrittenToFile) {
                            
                            return;
                        }
                        
                    }
                    break;
                case DontEraseFileData:
                    DataIsDeleted = true;
                    break;
                default:
                    std::cout << "Такого пункта не существует\n";
                }
            }
        }
    }
        
    
}

void SaveArraysToFile(int* Array, unsigned long long ArraySize, int* SortedArray) {
    SaveArrayToFile(Array, ArraySize);
    SaveArrayToFile(SortedArray, ArraySize);
}

std::pair<int*, unsigned long long> GetArrayFromFile(std::string FileName) {
    const char ZeroNumCodeBound = '0';
    const char NineNumCodeBound = '9';
    const char MinusCode = '-';

    std::pair<int*, unsigned long long> ArrayAndArraySizeFromFile(nullptr, 0);
   
    bool ThisNumIsCorrect = false;
    bool ThisIsArraySizeCheck = true;
    unsigned long long CountOfArrayElements = 0;
    std::string DataFromFile;
    std::string ArraySizeStr;
    std::ifstream CheckArrayFromFile;

    CheckArrayFromFile.open(FileName);

    if (!CheckArrayFromFile.is_open()) {
        std::cout << "Не удалось открыть файл для проверки содержимого, пожалуйста, попробуйте открыть его снова\n";
        return ArrayAndArraySizeFromFile;
    }

    while (!CheckArrayFromFile.eof()) {
        CheckArrayFromFile >> DataFromFile;

        if (ThisIsArraySizeCheck) {
            ThisIsArraySizeCheck = false;
            for (unsigned long long i = 0; i < DataFromFile.size(); i++) {

                ThisNumIsCorrect = false;
                for (char j = ZeroNumCodeBound; j <= NineNumCodeBound; j++) {

                    if (DataFromFile[i] == j) {
                        ThisNumIsCorrect = true;
                        break;
                    }
                }

                if (!ThisNumIsCorrect) {
                    CheckArrayFromFile.close();
                    std::cout << "Число количества элементов массива в файле " << FileName << " некорректно\n";
                    return ArrayAndArraySizeFromFile;
                }
            }
            ArraySizeStr = DataFromFile;

        }

        else {

            for (unsigned long long i = 0; i < DataFromFile.size(); i++) {
                ThisNumIsCorrect = false;
                for (char j = ZeroNumCodeBound; j <= NineNumCodeBound; j++) {

                    if ((DataFromFile[i] == j) || (DataFromFile[i] == MinusCode)) {
                        ThisNumIsCorrect = true;
                        break;
                    }
                }

                if (!ThisNumIsCorrect) {
                    std::cout << "Элемент массива под номером " << CountOfArrayElements << " некорректен\n";
                    CheckArrayFromFile.close();
                    return ArrayAndArraySizeFromFile;
                }
            }
            if (ThisNumIsCorrect) {
                ++CountOfArrayElements;
            }

        }
    }

    CheckArrayFromFile.close();
    
    if (CountOfArrayElements != std::stoull(ArraySizeStr)) {
        std::cout << CountOfArrayElements << '\t' << std::stoull(ArraySizeStr);
        std::cout << "Количество заявленных элементов массива не совпадает с действительным, файл некорректен\n";
        return ArrayAndArraySizeFromFile;
    }

    std::cout << "Содержимое файла корректно...\n";

    std::ifstream GetArrayFromFile(FileName);
    bool GetArraySize = true;
    unsigned long long IndexOfArrayElement = 0;

    if (!GetArrayFromFile.is_open()) {
        std::cout << "Не удалось открыть файл для записи в массив\n";
        return ArrayAndArraySizeFromFile;
    }
    
    while (!GetArrayFromFile.eof()) {
        GetArrayFromFile >> DataFromFile;

        if (GetArraySize) {
            GetArraySize = false;
            ArrayAndArraySizeFromFile.second = std::stoull(DataFromFile);
            ArrayAndArraySizeFromFile.first = new int[ArrayAndArraySizeFromFile.second] {};
        }

        else {
            ArrayAndArraySizeFromFile.first[IndexOfArrayElement] = std::stoi(DataFromFile);
            ++IndexOfArrayElement;
        }
    }
    
    return ArrayAndArraySizeFromFile;
}