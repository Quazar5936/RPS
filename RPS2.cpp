#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "RPS2.h"


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
bool DeleteFileData(std::string FileName) {
    std::ofstream FileDataDeleter (FileName, std::ios::trunc);
    if (FileDataDeleter.is_open()) {
        FileDataDeleter.close();
        return true;
    }
    else {
        std::cout << "Стереть данные из файла не удалось, выберите другой файл для записи или попробуйте снова\n";
        return false;
    }
}


void SaveArrayToFile(double* Array, unsigned long long n) {
    bool SaveArrayUserInput = true;
    bool FileIsCorrect = true;
    bool DataIsDeleted = false;
    
    while (SaveArrayUserInput) {
        unsigned long long UserEraseFileChoice = 0;
        DataIsDeleted = false;
        std::string FileName;
        std::cout << "Введите название файла: ";
        std::getline(std::cin, FileName);
        bool FileNameIsCorrect = FileNameCheck(FileName);

        if (!FileNameIsCorrect) {
            std::cout << "Название файла некорректно, введите, пожалуйста, корректное\n";
            continue;
        }
        else {
            std::ifstream CheckFileData(FileName);
            if (CheckFileData.is_open()) {
                CheckFileData.seekg(0, std::ios::end);
                if (CheckFileData.tellg() == 0) {
                    std::cout << "Файл пуст, приступаю к записи...\n";
                    CheckFileData.close();

                    std::ofstream ArrayDataSaveToFile(FileName);
                    if (ArrayDataSaveToFile.is_open()) {
                        ArrayDataSaveToFile << std::to_string(n);
                        ArrayDataSaveToFile << '\n';
                        for (unsigned long long i = 0; i < n; i++) {
                            ArrayDataSaveToFile << std::to_string(Array[i]);
                            if (n + 1 != n) {
                                ArrayDataSaveToFile << ' ';
                            }

                        }
                        ArrayDataSaveToFile.close();
                        std::cout << "Данные успешно записаны в файл...\n";
                        SaveArrayUserInput = false;
                    }
                    else {
                        std::cout << "Файл для записи не открыт, попробуйте ввести название файла снова\n";
                    }
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
            else {
                std::cout << "Такого файла не существует или он не был открыт, создаю файл с таким названием...\n";
                std::ofstream ArrayDataSaveToFile(FileName);
                if (ArrayDataSaveToFile.is_open()) {
                    ArrayDataSaveToFile << std::to_string(n);
                    ArrayDataSaveToFile << '\n';
                    for (unsigned long long i = 0; i < n; i++) {
                        ArrayDataSaveToFile << std::to_string(Array[i]);
                        if (i + 1 != n) {
                            ArrayDataSaveToFile << ' ';
                        }
                        
                        

                    }
                    ArrayDataSaveToFile.close();
                    std::cout << "Данные успешно записаны в файл...\n";
                    SaveArrayUserInput = false;
                }

            }

        }


    }

}

void SaveArraysToFile(double* Array, unsigned long long n, double* SortedArray) {
    SaveArrayToFile(Array, n);
    SaveArrayToFile(SortedArray, n);
}

void SaveArrayInFileInterface(double* Array, unsigned long long n, double* SortedArray) {
    unsigned long long UserLoadArrayChoice = 0;
    bool UserFileLoad = true;

    while (UserFileLoad) {
        std::cout << "Выберите один из пунктов:\n1 - Сохранить исходный массив в файл\n2 - Сохранить отсортированный массив в файл\n3 - Сохранить оба массива в файлы\n4 - Ничего не сохранять\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserLoadArrayChoice);

        switch (UserLoadArrayChoice) {
            case SaveArray :
                SaveArrayToFile(Array, n);
                UserFileLoad = false;
                break;
            case SaveSortedArray:
                SaveArrayToFile(SortedArray, n);
                UserFileLoad = false;
                break;
            case SaveBoth:
                SaveArraysToFile(Array, n, SortedArray);
                break;
            case DontSave:
                UserFileLoad = false;
                break;
            default:
                std::cout << "Такого пункта не существует, введите новый\n";

        }
    }
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
                        CheckArrayFromFile.close();
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
                     
                    if (!ThisNumIsCorrect ) {
                        
                        std::cout << "Элемент массива под номером " << CountOfArrayElements << " некорректен\n";
                        CheckArrayFromFile.close();
                        return FileInputResult;
                    }
                }
                if (ThisNumIsCorrect) {
                    ++CountOfArrayElements;
                }

            }
            
        }
        
        CheckArrayFromFile.close();
    }
    
    else {
        std::cout << "Не удалось открыть файл для проверки содержимого, пожалуйста, попробуйте открыть его снова\n";
        return FileInputResult;
    }
    
    if (CountOfArrayElements != std::stoull(strn)) {
        std::cout << CountOfArrayElements << '\t' << std::stoull(strn);
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
        bool FileNameIsCorrect = FileNameCheck(FileName);

        if (!FileNameIsCorrect) {
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

void CopyArray(double* Array, unsigned long long n, double* NewArray) {
    for (unsigned long long i = 0; i < n; i++) {
        NewArray[i] = Array[i];
    }
}

static void Interface(void) {
    bool UserInMenu = true;
    unsigned long long UserInMenuChoice = 0;
    double* Array = nullptr;
    double* SortedArray = nullptr;
    unsigned long long n = 0;
    bool ArrayIsNotNullptr = false;

    while (UserInMenu) {
        if (ArrayIsNotNullptr) {
            
            delete[] Array;
            delete[] SortedArray;
            ArrayIsNotNullptr = false;
        }
        
        std::cout << "Выберите один из нижеперечисленных пунктов:\n1 - Приступить ко вводу данных\n2 - Выйти\n";
        std::cout << "Ваш выбор: ";
        UnsignedLongLongInput(UserInMenuChoice);
        switch (UserInMenuChoice) {
        case Start:
            ArrayIsNotNullptr = true;
            Array = InterfaceOfnAndArrayDataInput(n);
            SortedArray = new double[n] {};
            CopyArray(Array, n, SortedArray);
            CombSort(SortedArray, n);
            std::cout << "\n\n\nРезультат сортировки:\n";
            ShowArray(SortedArray, n);
            SaveArrayInFileInterface(Array, n, SortedArray);
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


