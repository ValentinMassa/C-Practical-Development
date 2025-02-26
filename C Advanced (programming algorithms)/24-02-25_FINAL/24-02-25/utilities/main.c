#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../List/main.h"
#include "./main.h"

#define isnumber1(x) ( (x)>= '0' && (x)<= '9'? 1 : 0 )
#define isnumber2(x) ( (x)>= '0' && (x)<= '2'? 1 : 0 )

int cmpOp1_(const void* a, const void* b);
int cmpOp2_(const void* a, const void* b);
void printProduc(void* prod, void* param);
int processFile(char* nameFile, int option, unsigned nodes);


int nMaxMin(char* namearch)
{
    char buffer[SIZE_BUFFER_MAX];
    int nodes, option;

    do{
        puts("Bienvenido a LA EMPRESA S.A nMaxMin");
        puts("  Ingresar cantidad de elementos a ver");
        fflush(stdin);
        fgets(buffer, SIZE_BUFFER_MAX, stdin);
        fflush(stdin);

    }while( !isnumber1(*buffer) );

    sscanf(buffer, "%d", &nodes);

    do{
        puts("Condicion:");
        puts("  1) ASCENDENTE");
        puts("  2) DESCENDENTE");
        puts("  0) SALIR");
        fflush(stdin);
        fgets(buffer, SIZE_BUFFER_MAX, stdin);
        fflush(stdin);
    }while( (isnumber2(*buffer) == 0));

    sscanf(buffer, "%d", &option);

    switch (option){

        case 0:{
            puts("leaving");
            break;
        }
        default:
            {
                processFile(namearch, option, nodes);
                break;
            }

    }
    return 1;
}

int processFile(char* nameFile, int option, unsigned nodes){

    FILE* fp = fopen(nameFile, "rb");
    cmp finalDecition = ((option == OP_1)?cmpOp1_:cmpOp2_);
    t_Products auxp;
    slist products;
    unsigned fnalNodes = nodes;

    if(!fp)return 0;

    createList(&products);

    while( fread(&auxp, sizeof(t_Products), 1, fp) == 1)
    {

        if(!insertNelementsInOrder(&products, &auxp, sizeof(t_Products),&fnalNodes, finalDecition))
        {
            deleteList(&products);
            fclose(fp);
            return 0;
        }
    }

    walkList(&products, NULL, printProduc);
    deleteList(&products);
    fclose(fp);
    return 1;

}

void printProduc(void* prod, void* param){

    t_Products *a = (t_Products*)prod;
    printf("code: %u | desc: %-s | cantidad: %u\n", a->codeNumber, a->description, a->quantity);
    return;
}

int cmpOp1_(const void* a, const void* b)
{
    t_Products *ai = (t_Products*)a;
    t_Products *bi = (t_Products*)b;

    return (bi->quantity - ai->quantity );
}

int cmpOp2_(const void* a, const void* b)
{
    t_Products *ai = (t_Products*)a;
    t_Products *bi = (t_Products*)b;

    return (ai->quantity - bi->quantity);
}


void createBin(char* fname){
    FILE* fp = fopen(fname, "wb");
    t_Products aux[] = {
        {001, "martillos", 5},
        {002, "pesas", 7},
        {003, "tornillos", 10},
        {004, "clavos", 2},
        {005, "gaza", 1},
        {001, "martillos", 6},
        {002, "pesas", 5},
        {003, "tornillos", 6},
        {004, "clavos", 7},
        {005, "gaza", 8}}; //in order con 3 nodos: op1- 005, 004, uno de 005
                                    //op 2: 003, 005, 002/004}

    if(!fp)return;
    fwrite(&aux, sizeof(t_Products), (sizeof(aux)/sizeof(t_Products)), fp );
    fclose(fp);
}

