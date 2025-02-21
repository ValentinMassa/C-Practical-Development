#ifndef STRUCTS__MAIN_H_INCLUDED
#define STRUCTS__MAIN_H_INCLUDED

#include "../DEFINES.h"

typedef struct
{
    unsigned ID;
    char __assigment[SIZE_ASSIGMENT];
    char __academicYear[SIZE_ACADEMIC_YEAR];
    unsigned char __term;
    unsigned char __final;
}idx_Academics;

typedef struct
{
    int quantSubjects;
    int adder;
    int passedTest;
}helperStudent;
#endif // STRUCTS__MAIN_H_INCLUDED
