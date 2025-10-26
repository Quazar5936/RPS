#ifndef RPS2_H
#define RPS2_H

constexpr double FACTOR = 1.247;
enum UserInterfaceChoice { Start = 1, Quit };
enum UserArrayDataInput {AutoInput = 1, ManualInput , FileInput};
enum SaveArrayChoice {SaveArray = 1, SaveSortedArray, SaveBoth, DontSave};
void UnsignedLongLongInput(unsigned long long& n);
void SaveArraysToFile(double* Array, unsigned long long n, double* SortedArray);
void SaveArrayToFile(double* Array, unsigned long long n);
bool FileNameCheck(std::string FileName);
std::pair<double*, unsigned long long> GetArrayFromFile(std::string FileName);
void ShowArray(double* Array, unsigned long long n);
void CopyArray(double* Array, unsigned long long n, double* NewArray);
void DoubleArrayInput(double* Array, unsigned long long n);
void AutoInputForArray(double* Array, unsigned long long n, std::default_random_engine RandEngine);
void Greeting(void);


#endif 
