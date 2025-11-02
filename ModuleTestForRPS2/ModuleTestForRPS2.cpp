
#include "pch.h"
#include "CppUnitTest.h"
#include "..\RPS2\FileFunctions.cpp"
#include "..\RPS2\HelpingFunctions.cpp"
#include "..\RPS2\InputFunctions.cpp"
#include "..\RPS2\RPS2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModuleTestForRPS2 {
	TEST_CLASS(ModuleTestForRPS2) {
	public:
		
		TEST_METHOD(ModuleTest1) {
				std::string FileNameForTest1 = "con.txt"; // Проверка на недопустимое имя
				bool FileNameIsCorrect = FileNameCheck(FileNameForTest1);
				const bool CorrectResult = false;
				Assert::IsTrue(FileNameIsCorrect == CorrectResult);
		}

		TEST_METHOD(ModuleTest2) {
				std::string FileName = "Testfile.txt"; // Некорректные данные в файле
				const std::pair<int*, unsigned long long> CorrectRes(nullptr, 0);
				std::pair<int*, unsigned long long> Result = GetArrayFromFile(FileName);
				Assert::IsTrue(CorrectRes == Result);
		}

		TEST_METHOD(ModuleTest3) {
				const unsigned long long ArrSize = 10;
				int* TestArr = new int[ArrSize]; // {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
				int* ResArr = new int[ArrSize]; // ожидаемый результат сортировки {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
				for (long i = 9, j = 0; i >= 0; i--,j++) {
						TestArr[j] = i;
						ResArr[j] = j;
				}
				CombSort(TestArr, ArrSize);
				bool ArraysAreEqual = true;
				const bool TestResult = true;
				for (unsigned long long i = 0; i < ArrSize; i++) {
						if (TestArr[i] != ResArr[i]) {
								ArraysAreEqual = false;
								break;
						}
				}
				delete[] TestArr;
				TestArr = nullptr;
				delete[] ResArr;
				ResArr = nullptr;
				Assert::IsTrue(ArraysAreEqual == TestResult);
				Logger::WriteMessage(L"Тестирование прошло успешно\n");
		}
	};
}
