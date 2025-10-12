#ifndef RPS2_H
#define RPS2_H

constexpr double FACTOR = 1.247;
enum UserInterfaceChoice { Start = 1, Quit };
enum UserArrayDataInput {AutoInput = 1, ManualInput , FileInput};
enum SaveArrayChoice {SaveArray = 1, SaveSortedArray, SaveBoth, DontSave};
enum EraseFileDataOrNotChoice{EraseFileData = 1, DontEraseFileData};

#endif 
