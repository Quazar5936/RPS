#ifndef RPS2_H
#define RPS2_H

constexpr double FACTOR = 1.247;
enum UserInterfaceChoice { Start = 1, Quit };
enum UserArrayDataInput {AutoInput = 1, ManualInput , FileInput};
enum SaveArrayChoice {SaveArray = 1, SaveSortedArray, SaveBoth, DontSave};
void UnsignedLongLongInput(unsigned long long& n);
void SaveArraysToFile(int* Array, unsigned long long n, int* SortedArray);
void SaveArrayToFile(int* Array, unsigned long long n);
bool FileNameCheck(std::string FileName);
std::pair<int*, unsigned long long> GetArrayFromFile(std::string FileName);
void ShowArray(int* Array, unsigned long long n);
void CopyArray(int* Array, unsigned long long n, int* NewArray);
void DoubleArrayInput(int* Array, unsigned long long n);
void AutoInputForArray(int* Array, unsigned long long n, std::default_random_engine RandEngine);
void Greeting(void);


#endif 
