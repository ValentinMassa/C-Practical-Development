#include "../structs.h"
#include "./main.h"
#include "../list/list.h"

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int formatStudent(char* buffer, t_student *aux);
int cmpId(const void*a, const void* b);
int cmpCBestAverageWithoutFail(const void*a, const void* b);
int cmpCLnNId(const void*a, const void* b);
int cmpLnNId(const void*a, const void* b);
int cmpBestAverage(const void*a, const void* b);
void printStudent(void* astudent, void* param, unsigned sizedata, unsigned sizeParam);



int processStudents(char* namefile)
{
    FILE* ft;
    char buffer[SIZE_BUFFER];
    sList students;
    t_student aux;


    ft = fopen (namefile, "r");
    if(!ft)return 0;

    createList(&students);

    while( fgets(buffer, SIZE_BUFFER, ft)!= NULL )
    {
        if(!formatStudent(buffer, &aux))
        {
            freeList(&students);
            return 0;
        }
        if(!loadElementIntoList(&students, &aux, sizeof(aux)))
        {
            freeList(&students);
            return 0;
        }
    }

    puts("> NORMAL LIST: ");
    walkList(&students, NULL, 0, printStudent);
    puts("-------------------------------------------------");
    puts("");

    puts("> INVERTED LIST: ");
    invertList(&students);
    walkList(&students, NULL, 0, printStudent);
    puts("-------------------------------------------------");
    puts("");

    puts("> SORTED BY: ID");
    sortList(&students, cmpId);
    walkList(&students, NULL, 0, printStudent);
    puts("-------------------------------------------------");
    puts("");

    puts("> SORTED BY: LAST NAME, NAME, ID");

    sortList(&students, cmpLnNId);
    walkList(&students, NULL, 0, printStudent);

    puts("-------------------------------------------------");
    puts("");
    puts("> SORTED BY: CARREER, LAST NAME, NAME, ID");

    sortList(&students, cmpCLnNId);
    walkList(&students, NULL, 0, printStudent);

    puts("-------------------------------------------------");
    puts("");
    puts("> SORTED BY: BEST AVERAGE");

    sortList(&students, cmpBestAverage);
    walkList(&students, NULL, 0, printStudent);

    puts("-------------------------------------------------");
    puts("");
    puts("> SORTED BY: CARREER, BEST AVERAGE WITHOUT FAILED TEST");

    sortList(&students, cmpCBestAverageWithoutFail);
    walkList(&students, NULL, 0, printStudent);



    puts("-------------------------------------------------");
    puts("");
    puts("> ALL DONE!");
    freeList(&students);
    return 1;
}

int formatStudent(char* buffer, t_student *aux)
{
    char * pointer = buffer;
    int i;
    sscanf(pointer, "%8u%20s%20s%3s", &aux->id, aux->last_name, aux->name, aux->code_carreer);

    pointer = strchr(buffer, '\n');
    if(!pointer)return 0;

    *pointer = '\0';
    pointer -= 2;
    sscanf(pointer, "%u", &aux->subjects.amount_subjetcs);
    *pointer = '\0';
    for(i = 0; i < aux->subjects.amount_subjetcs; i++)
    {
        pointer -= 12;

        sscanf(pointer, "%4u%6s%02d", &aux->subjects.subjetc[i].code_subject, aux->subjects.subjetc[i].course_code, &aux->subjects.subjetc[i].final_note );

        *pointer = '\0';
    }
    return 1;
}

int cmpId(const void*a, const void* b)
{
    t_student *ai =  (t_student*)a;
    t_student *bi =  (t_student*)b;

    return (ai->id - bi->id);
}

int cmpLnNId(const void*a, const void* b)
{
    int result;
    t_student *ai =  (t_student*)a;
    t_student *bi =  (t_student*)b;

    result = strcmp(ai->last_name, bi->last_name);

    if(result < 0)
        return -1;
    else if(result > 0)
        return 1;

    result = strcmp(ai->name, bi->name);
    if(result < 0)
        return -1;
    else if(result > 0)
        return 1;

    return ai->id - bi->id;
}
int cmpCLnNId(const void*a, const void* b)
{
    int result;
    t_student *ai =  (t_student*)a;
    t_student *bi =  (t_student*)b;

    result = strcmp(ai->code_carreer, bi->code_carreer);
    if(result < 0)
        return -1;
    else if(result > 0)
        return 1;


    result = strcmp(ai->last_name, bi->last_name ); //B - A

    if(result < 0)
        return -1;
    else if(result > 0)
        return 1;

    result = strcmp(ai->name, bi->name);
    if(result < 0)
        return -11;
    else if(result > 0)
        return 1;

    return ai->id - bi->id;
}

int cmpBestAverage(const void*a, const void* b)
{
    int i;
    int counta = 0, countb = 0;
    t_student *ai =  (t_student*)a;
    t_student *bi =  (t_student*)b;

    for(i = 0; i < ai->subjects.amount_subjetcs; i++)
    {
        counta += ai->subjects.subjetc[i].final_note;
    }
    for(i = 0; i < bi->subjects.amount_subjetcs; i++)
    {
        countb += bi->subjects.subjetc[i].final_note;
    }


    return  (countb / bi->subjects.amount_subjetcs ) - (counta / ai->subjects.amount_subjetcs );
}

int cmpCBestAverageWithoutFail(const void*a, const void* b)
{
    int i, result;
    int counta = 0, countb = 0;
    t_student *ai =  (t_student*)a;
    t_student *bi =  (t_student*)b;

    result = strcmp(ai->code_carreer, bi->code_carreer);
    if(result < 0)
        return -1;
    else if(result > 0)
        return 1;

    for(i = 0; i < ai->subjects.amount_subjetcs; i++)
    {
        if(ai->subjects.subjetc[i].final_note >3)
            counta += ai->subjects.subjetc[i].final_note;
    }
    for(i = 0; i < bi->subjects.amount_subjetcs; i++)
    {
        if(bi->subjects.subjetc[i].final_note > 3)
            countb += bi->subjects.subjetc[i].final_note;
    }
    return  (countb / bi->subjects.amount_subjetcs ) - (counta / ai->subjects.amount_subjetcs ) ;
}

void printStudent(void* astudent, void* param, unsigned sizedata, unsigned sizeParam)
{
    t_student* aux  = (t_student*)astudent;
    int i;
    printf("%d~%-20s|%-20s|%3s|",aux->id, aux->last_name, aux->name, aux->code_carreer);
            for(i= 0; i < aux->subjects.amount_subjetcs; i++)
            {
                printf("%4d-%-6s-%02d|", aux->subjects.subjetc[i].code_subject, aux->subjects.subjetc[i].course_code,
                       aux->subjects.subjetc[i].final_note);
            }
        printf("%02d\n", aux->subjects.amount_subjetcs);

}

