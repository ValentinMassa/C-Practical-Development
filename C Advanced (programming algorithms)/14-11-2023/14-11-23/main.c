#include <stdio.h>
#include <stdlib.h>
#include "fileCreator/main.h"
#include "defines.h"
#include "utilities/main.h"


int main()
{
    //studentsCrator(NAME_STUDENTS_DAT);
    //createIdxStudents(NAME_STUDENTS_DAT, NAME_IDX_STUDENTS_DAT);
    //printIdxBin(NAME_IDX_STUDENTS_DAT);

    menu(NAME_IDX_STUDENTS_DAT, NAME_STUDENTS_DAT);

    printf("> FINAL STATE OF %s\n",NAME_IDX_STUDENTS_DAT);
    printIdxBin(NAME_IDX_STUDENTS_DAT);
    puts("Thanks for using this student Manager");


    return 0;
}
