#include <stdio.h>
#include "DEFINES.h"
#include "utilities/main.h"
#include "fileCreator/main.h"

int main()
{
    int _id, result;
    char namefinal[FINAL_SIZE] = {""};

    binCreator(NAME_FILE_IDX_STUDENTS);

    _id = askIdFromStdin();

    createFinalName(namefinal,DEFAULT_NAME_FILE_TXT_STUDENT, _id);

    result = generateInformOfStudentById(NAME_FILE_IDX_STUDENTS,namefinal, _id);

    if(result == NOT_FOUNDED)
        puts("> ID DOESNT EXIST");
    if(result == ERROR)
        puts("> SOMETHING WENT WRONG.");
    if(result == DONE)
        printf("> DONE! check: %s to see the results",namefinal);

    return 0;
}
