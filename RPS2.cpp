#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "RPS2.h"

extern "C" void CombSort_(double* Array, unsigned long long n);


static void ShowArray(double* Array, unsigned long long n) {
    for (unsigned long long i = 0; i < n; i++) {
        std::cout << "Элемент массива под номером " << i + 1 << ". ";
        std::cout << Array[i] << '\n';
    }
}

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
static unsigned char StrSize(std::string Str) {
    unsigned char SizeStr = 0;
    for (size_t i = 0; i < Str.size(); i++) {
        ++SizeStr;
    }
    return SizeStr;
}

void GenerateCombinations(const std::string Str, std::vector<std::string>& Combinations) {
    unsigned char n = StrSize(Str);
    unsigned char TotalCombinations = 1 << n;

    for (unsigned char i = 0; i < TotalCombinations; ++i) {
        std::string Combination = "";
        for (unsigned char j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                Combination += Str[j] + 32;
            }
            else {
                Combination += Str[j];
            }
        }
        Combinations.push_back(Combination);
    }
}

bool FileNameCheck(std::string FileName) {
    bool FileIsCorrect = true;
    std::vector<std::string> ForbiddenNamesOfFiles(0);
    GenerateCombinations("CON", ForbiddenNamesOfFiles);
    GenerateCombinations("PRN", ForbiddenNamesOfFiles);
    GenerateCombinations("AUX", ForbiddenNamesOfFiles);
    GenerateCombinations("NUL", ForbiddenNamesOfFiles);
    GenerateCombinations("COM0", ForbiddenNamesOfFiles);
    GenerateCombinations("COM1", ForbiddenNamesOfFiles);
    GenerateCombinations("COM2", ForbiddenNamesOfFiles);
    GenerateCombinations("COM3", ForbiddenNamesOfFiles);
    GenerateCombinations("COM4", ForbiddenNamesOfFiles);
    GenerateCombinations("COM5", ForbiddenNamesOfFiles);
    GenerateCombinations("COM6", ForbiddenNamesOfFiles);
    GenerateCombinations("COM7", ForbiddenNamesOfFiles);
    GenerateCombinations("COM8", ForbiddenNamesOfFiles);
    GenerateCombinations("COM9", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT0", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT1", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT2", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT3", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT4", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT5", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT6", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT7", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT8", ForbiddenNamesOfFiles);
    GenerateCombinations("LPT9", ForbiddenNamesOfFiles);
    GenerateCombinations("LPTNO", ForbiddenNamesOfFiles);
    GenerateCombinations("LPTSCSI", ForbiddenNamesOfFiles);
    GenerateCombinations("COMSCSI", ForbiddenNamesOfFiles);

    const std::string FileExtension = ".txt";
    std::string Path = "";
    const std::string MinShortForbiddenCombination = "CON.txt";

    size_t j = FileName.size();
    const std::string StopSymbols{ 47,92 };

    if (FileName.size() >= MinShortForbiddenCombination.size()) {
        while ((FileName[j] != StopSymbols[0]) && (FileName[j] != StopSymbols[1]) && (j > 0)) {
            j--;

        }
        if (j != 0) {
            j++;

        }

        for (j; j < FileName.size(); j++) {
            Path += FileName[j];
        }
        if (Path == ".txt") {
            std::cout << "Имя файла некорректно\n";
            FileIsCorrect = false;
            return FileIsCorrect;
        }


        const std::string MaxLongForbiddenCombination = "COMSCSI.txt";
        const std::string ForbiddenSymbols{ 47,92,60,62,58,34,124,42,63 }; // Запрещенные символы /\<>:"|*?

        for (size_t i = 0; i < Path.size(); i++) {
            for (size_t k = 0; k < ForbiddenSymbols.size(); k++) {

                if (Path[i] == ForbiddenSymbols[k]) {
                    FileIsCorrect = false;
                    std::cout << "Недопустимое имя файла\n";
                    return FileIsCorrect;
                }
            }
        }
        if (Path.size() > MaxLongForbiddenCombination.size()) {
            FileIsCorrect = true;
            return FileIsCorrect;
        }
    }
    else {
        FileIsCorrect = true;
        return FileIsCorrect;
    }
    for (size_t i = 0; i < ForbiddenNamesOfFiles.size(); i++) {
        if (Path == (ForbiddenNamesOfFiles[i] + ".txt")) {
            FileIsCorrect = false;
            std::cout << "Недопустимое имя файла\n";
            return FileIsCorrect;
        }

    }
    FileIsCorrect = true;
    return FileIsCorrect;

}

static std::pair<double*, unsigned long long> InputArrayFromFile(std::string FileName) {
    std::ifstream CheckArrayFromFile;
    std::pair<double*, unsigned long long> FileInputResult(nullptr,0);
    std::string strCheckFileData;
    CheckArrayFromFile.open(FileName);
    bool ThisIsnCheck = true;
    const char ZeroNumCodeBound = 48;
    const char NineNumCodeBound = 57;
    const char MinusCode = 45;
    const char CommaCode = 44;
    bool ThisNumIsCorrect = false;
    unsigned long long CountOfArrayElements = 0;
    std::string strn;

    if (CheckArrayFromFile.is_open()) {
        while (!CheckArrayFromFile.eof()) {
            CheckArrayFromFile >> strCheckFileData;
            
            if (ThisIsnCheck){
                ThisIsnCheck = false;
                for (unsigned long long i = 0; i < strCheckFileData.size(); i++) {
                    
                    ThisNumIsCorrect = false;
                    for (char j = ZeroNumCodeBound; j <= NineNumCodeBound; j++) {
                       
                        if (strCheckFileData[i] == j) {
                            ThisNumIsCorrect = true;
                            break;
                        }
                    }
                    if (!ThisNumIsCorrect) {
                        std::cout << "Число количества элементов массива в файле " << FileName << " некорректно\n";
                        return FileInputResult;
                    }
                }
                strn = strCheckFileData;
                
            }
            else {
                
                for (unsigned long long i = 0; i < strCheckFileData.size(); i++) {
                    ThisNumIsCorrect = false;
                    for (char j = ZeroNumCodeBound; j <= NineNumCodeBound; j++) {
                        if ((strCheckFileData[i] == j) || (strCheckFileData[i] == MinusCode) || (strCheckFileData[i] == CommaCode)) {
                            ThisNumIsCorrect = true;
                            break;
                        }
                        
                    }
                     
                    if (!ThisNumIsCorrect) {
                        std::cout << strCheckFileData[i] << '\n';
                        std::cout << "Элемент массива под номером " << CountOfArrayElements << " некорректен\n";
                        return FileInputResult;
                    }
                }
                ++CountOfArrayElements;

            }
            
        }
        CheckArrayFromFile.close();
    }
    
    else {
        std::cout << "Не удалось открыть файл для проверки содержимого, пожалуйста, попробуйте открыть его снова\n";
        return FileInputResult;
    }

    if (CountOfArrayElements != std::stoull(strn)) {
        std::cout << "Количество заявленных элементов массива не совпадает с действительным, файл некорректен\n";
        return FileInputResult;
    }

    std::cout << "Содержимое файла корректно...\n";

    std::ifstream GetArrayFromFile(FileName);
    std::string strGetData;
    bool Getn = true;
    unsigned long long i = 0;

    if (GetArrayFromFile.is_open()) {
        while (!GetArrayFromFile.eof()) {
            GetArrayFromFile >> strGetData;
            if (Getn) {
                FileInputResult.second = std::stoull(strGetData);
               
                FileInputResult.first = new double[FileInputResult.second] {};
                Getn = false;
            }
            else {
                FileInputResult.first[i] = std::stod(strGetData);
                
                ++i;
            }

        }
    }
    else {
        std::cout << "Не удалось открыть файл для записи в массив\n";
        return FileInputResult;
    }

    return FileInputResult;
}

static std::pair<double*, unsigned long long> UserInterfaceForFileInput(void) {
    bool UserFileInput = true;
    std::pair<double*, unsigned long long> FileInputResult;
 
    while (UserFileInput) {
        std::string FileName;
        std::cout << "Введите название файла: ";
        std::getline(std::cin, FileName);
        bool FileIsCorrect = FileNameCheck(FileName);

        if (!FileIsCorrect) {
            std::cout << "Название файла некорректно, введите, пожалуйста, корректное\n";
            continue;
        }
        else {
            FileInputResult = InputArrayFromFile(FileName);
            if (FileInputResult.first != nullptr && FileInputResult.second != 0) {
                std::cout << "Данные из файла " << FileName << " занесены в массив успешно\nСодержимое массива:\n";
                ShowArray(FileInputResult.first, FileInputResult.second);
                UserFileInput = false;
            }
            else {
                std::cout << "Попробуйте снова\n";
                
            }

            
        }

    }
    return FileInputResult;

}


static double * InterfaceOfnAndArrayDataInput(unsigned long long &n) {
    bool UserInAllDataInput = true;
    unsigned long long UsernInputChoice = 0;
    std::uniform_int_distribution<unsigned long long> GetRandVal{ 1,1000 };
    std::default_random_engine RandEngine{ static_cast<unsigned int> (time(NULL))};
    std::pair<double*, int> PairForFileInput;
    double* NewArray = nullptr;
    bool UserSelectedFileInput = false;
    bool UsernInput = true;

    while (UsernInput) {
        std::cout << "Ввести количество элементов массива:\n1 - Автоматически\n2 - Вручную\n3 - Загрузить массив из файла\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UsernInputChoice);
        
        switch (UsernInputChoice) {
            
        case AutoInput:
            std::cout << "Количество элементов массива: ";
            n = GetRandVal(RandEngine);
            std::cout << n << '\n';
            UsernInput = false;
            break;
        case ManualInput:
            std::cout << "Количество элементов массива: ";
            UnsignedLongLongInput(n);
            UsernInput = false;
            break;
        case FileInput:
            UserSelectedFileInput = true;
            UsernInput = false;
            PairForFileInput = UserInterfaceForFileInput();
            break;
        default:
            std::cout << "Вы выбрали несуществующий пункт, введите существующий\n";
            break;
        }
            
    }
    if (!UserSelectedFileInput) {
        NewArray = new double[n] {};
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
    }
    else {
        n = PairForFileInput.second;
        NewArray = PairForFileInput.first;
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


