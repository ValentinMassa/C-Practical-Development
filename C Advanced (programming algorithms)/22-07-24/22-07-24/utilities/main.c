#include "./main.h"
#include "../BinaryTree/main.h"
#include "../structs/main.h"
#include "../queue/main.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isNumber(x)( (x)>= '0' && (x)<='9'? 1:0)

void operateStudent(void*a, void* punt, void* helper);
int IdCompeare(const void*b, const void*a);
int isId(char * line);


int generateInformOfStudentById(char * namefile, char* txtreport, int id)
{
    char buffer[SIZE_BUFFER];
    FILE* f_txt, *f_final;
    int result;

    BinaryTree students;
    BinaryTree* idDad;

    helperStudent help = {0,0,0};

    f_txt = fopen(NAME_AUX_TXT, "w");
    if(!f_txt)return ERROR;

    createTree(&students);
    result = loadTreeFromSortedFile(&students, namefile, sizeof(idx_Academics));
    if(result == 0)
    {
        clearTree(&students);
        return ERROR;
    }

    idDad = findNodeWithKey(&students, &id, sizeof(id),IdCompeare);
    if(!idDad)
    {
        clearTree(&students);
        return NOT_FOUNDED;
    }

    fprintf(f_txt, "MATERIA \t PERIODO \t NOTA\n");
    walkInOrderUntilCondition(idDad, &id, f_txt,&help,operateStudent,IdCompeare);

    fclose(f_txt);

    f_txt = fopen(NAME_AUX_TXT, "r");
    if(!f_txt){
        clearTree(&students);
        return ERROR;
    }
    f_final = fopen(txtreport, "w");
    if(!f_final){
        fclose(f_txt);
        clearTree(&students);
        return ERROR;
    };

    fprintf(f_final, "\tINFORME DE MATERIAS APROBADAS\n");
    fprintf(f_final, "-------------DNI: %d --------------\n",id);
    fprintf(f_final, "Materias Aprobadas: %d \tPromedio: %.2f \n\n",help.passedTest, (float)((float)help.adder/help.quantSubjects));

    while(fgets(buffer, sizeof(buffer), f_txt)!= NULL)
    {
        fprintf(f_final, "%s", buffer);
    }

    fclose(f_txt);
    fclose(f_final);
    remove(NAME_AUX_TXT);
    clearTree(&students);
    return DONE;
}



void operateStudent(void*a, void* punt, void* helper)
{
    helperStudent * helpaux = (helperStudent*)helper;
    idx_Academics *aux = (idx_Academics*)a;

    helpaux->adder += aux->__final - '0';
    helpaux->quantSubjects ++;
    if(aux->__final - '0' > 4)
        helpaux->passedTest ++;

    fprintf((FILE*)punt, "%-11s\t %-s-%c \t %c\n", aux->__assigment, aux->__academicYear, aux->__term, aux->__final);
}


int askIdFromStdin()
{
    char id[SIZE_ID];
    do
    {
        puts("Ingrese el DNI a generar el reporte:");
        fflush(stdin);
        fgets(id, SIZE_ID, stdin);
        fflush(stdin);
    }while(!isId(id));

    return atoi(id);
}

int isId(char * line)
{
    while(isNumber(*line) && (*line) != '\0')
        line ++;
    if((*line) == '\0' )return 1;
    else
    {
        puts("> Is not an id. Try again!");
        }return 0;
}

void createFinalName(char *namefinal,char *nametxt,int _id)
{
    char id[SIZE_ID];

    sprintf(id, "%d", _id);
    strcat(namefinal, id);
    strcat(namefinal, "_");
    strcat(namefinal, nametxt);
    return;

}
int IdCompeare(const void*a, const void*b)
{
    idx_Academics *ai = (idx_Academics*)a;
    int *bi = (int*)b;

    return (*bi) - (ai->ID);
}

