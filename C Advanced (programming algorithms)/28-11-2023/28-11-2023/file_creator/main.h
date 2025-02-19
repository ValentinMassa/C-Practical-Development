#ifndef FILE_CREATOR__MAIN_H_INCLUDED
#define FILE_CREATOR__MAIN_H_INCLUDED
#include "../utilities/structsAndDefines.h"

#define HAPPY_END 0
#define BAD_END 1

unsigned char txtFixedCreator(char* txtName, int whatWeUpload);
unsigned char BinaryCreator(char* nameFile);

#endif // MAIN_H_INCLUDED
