#include "../BinaryTree/main.h"
#include "../structs.h"
#include "./main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isNumber(x)((x)>= '0' && (x)<='9'?1:0)

int compeareId(const void* a, const void* b);
void fwritefIdx(void*data, void*param, unsigned sized, unsigned sizep);
int printBin(char* fname, void* aux, void* param,  unsigned sizeA, void(*action)(const void*, void*));
void printRegisterOfIdxBin(const void* data, void* param);
int idValidId(char * buffer);
void askforTheid(unsigned* id);
void processOption2(BTree * tree, char *FnameStudentidx);
void processOption1(BTree * tree, char *FnameStudent);
void printRegister( void* data, void* param, unsigned b, unsigned a);

void menu(char * fnameIdx, char* FnameStudent)
{
    int result;
    BTree students;


    createTree(&students);
    result = createTreeFromSortBin(&students, fnameIdx, sizeof(t_students_idx));

    puts("---------Original IDX------------");
    walkTreeInOrder(&students, NULL, 0,printRegister );
    puts(" ");
    puts("---------STARTING PROCESS------------");

    result = -1;
    while(result)
    {
        puts("> 1- DAR DE BAJA ALUMNO:");
        puts("> 2- GRABAR NUEVO ARCHIVO INDICE");
        puts("> 0- SALIR");
        puts("> INGRESE UNA OPCION:");
        fflush(stdin);
        fscanf(stdin, "%d", &result);
        fflush(stdin);
        switch(result)
            {
            case 1:{
                    processOption1(&students, FnameStudent);
                    puts("ID deleted. Do not forget to save the changes into .index!");
                    break;
                }
            case 2:{
                    processOption2(&students,fnameIdx );
                    puts("Changes Saved");
                    break;
                }
            case 0:{
                puts("Leaving....");
                system("Pause");
                break;
                }
            default:
                puts("Wrong option. Try again!");
                break;
            };
    }

    return;
}

void processOption2(BTree * tree, char *FnameStudentidx)
{

    FILE* fp = fopen(FnameStudentidx, "wb");

    walkTreeInOrder(tree, fp, 0, fwritefIdx);
    fclose(fp);
    return;
}

void processOption1(BTree * tree, char *FnameStudent)
{
    FILE* fp;
    unsigned id;
    t_students_idx data;
    t_students auxst;
    int result;

    askforTheid(&id);

    data.ID = id;



    result = DeleteTreeElement(tree, &data, sizeof(data),compeareId);
    if(result == -1)
    {
        puts("ID DOESNT EXISTS");
        return;
    }
    if(result == 0)

    {
        puts("OUT OF MEMORY");
        return;
    }

    fp = fopen(FnameStudent, "r+b");
    if(!fp){
        puts("> AN ERROR OCURRIED OPENING STUDENT DATABASE");
       return;
    }
    fseek(fp, ((data.posRegister)* sizeof(t_students)), SEEK_SET);
    fread(&auxst, sizeof(t_students),1, fp);
    auxst.logical_status = 0;
    fseek(fp, (long int)-sizeof(t_students), SEEK_CUR);
    fwrite(&auxst, sizeof(t_students), 1, fp);
    fclose(fp);


    puts ("-------newtree--------");
    walkTreeInOrder(tree, NULL, 0,printRegister );
    puts ("---------------");
    return;
}
void askforTheid(unsigned* id)
{
    char buffer[9];
    puts(" ");

    puts("Write the ID to eliminate:");
    do{
        fflush(stdin);
        fgets(buffer, 9, stdin);
        fflush(stdin);
    }while(!idValidId(buffer));

    *id =atoi(buffer);
    return;
}

int idValidId(char * buffer)
{
    char *punt = buffer;

    while(isNumber(*punt) && (*punt) != '\0' && *punt != '\n')
    {
        punt++;
    }
    if((*punt) == '\0' || *punt == '\n')
    {
        *punt = '\0';
        return 1;
    }
    puts("Thats not an ID, try again!");
    return 0;
}
int createIdxStudents(char* nameFileStudents, char* nameIdxStudents)
{
    FILE* f_students, *f_idxstudents;
    t_students_idx idxsaux;
    t_students saux;
    BTree idx_students;


    f_students = fopen(nameFileStudents, "rb");
    if(!f_students)return 0;

    createTree(&idx_students);

    while(fread(&saux, sizeof(saux), 1, f_students) == 1)
    {
        if(saux.logical_status == '0')continue;
        idxsaux.ID  = saux.ID;
        idxsaux.posRegister = (ftell(f_students)/sizeof(t_students)) -1;
        if( insertRegisterIntoTree(&idx_students, &idxsaux, sizeof(idxsaux),compeareId) != 1)
        {
            puts("An error happen creating treeIdx");
            destroyTree(&idx_students);
            fclose(f_students);
            remove(nameFileStudents);
            return 0;
        }
    }
    fclose(f_students);

    f_idxstudents = fopen(nameIdxStudents, "wb");

    if(!f_idxstudents)
    {
        destroyTree(&idx_students);
        return 0;
    }

    walkTreeInOrder(&idx_students, f_idxstudents, 0,fwritefIdx);
    destroyTree(&idx_students);

    fclose(f_idxstudents);
    return 1;

}


int compeareId(const void* a, const void* b)
{
    t_students_idx * ai = (t_students_idx*)a;
    t_students_idx * bi = (t_students_idx*)b;

    return bi->ID - ai->ID;
}

void fwritefIdx(void*data, void*param, unsigned sized, unsigned sizep)
{
    t_students_idx *auxd = (t_students_idx*)data;

    fwrite(auxd, sized, 1, (FILE*)param);

}
void printRegister( void* data, void* param, unsigned b, unsigned a)
{
    t_students_idx *auxd = (t_students_idx*)data;

    printf("%u | %u \n", auxd->ID, auxd->posRegister);
    return;
}

void printRegisterOfIdxBin(const void* data, void* param)
{
    t_students_idx *auxd = (t_students_idx*)data;

    printf("%u | %u \n", auxd->ID, auxd->posRegister);
    return;
}

int printBin(char* fname, void* aux, void* param,  unsigned sizeA, void(*action)(const void*, void*))
{
    FILE* fp = fopen(fname, "rb");
    if(!fp)return 0;
    while(fread(aux, sizeA, 1, fp) == 1)
    {
        action(aux, param);
    }
    return 1;
}


void printIdxBin(char* fname)
{
    t_students_idx aux;

    printBin(fname, &aux,NULL, sizeof(t_students_idx),printRegisterOfIdxBin);
}




