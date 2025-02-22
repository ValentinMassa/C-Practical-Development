#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "fileCreator/main.h"


int main()
{
    createTxt(NAME_FILE_STUDENTS);
    processStudents(NAME_FILE_STUDENTS);
    return 0;
}
