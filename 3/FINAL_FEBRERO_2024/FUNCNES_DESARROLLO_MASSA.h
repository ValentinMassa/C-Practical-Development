#ifndef FUNCNES_DESARROLLO_MASSA_H_INCLUDED
#define FUNCNES_DESARROLLO_MASSA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ARCH_A "posicionesA.csv"
#define N_ARCH_B "posicionesB.csv"
#define N_ARCH_AB "posicionesAB.csv"
#define TAM_ID 9
#define TAM_BUFFER 300

#define FactorIncremento 0.6
#define TamMax 10


//structs
typedef struct
{
    double fecha;
    char id[TAM_ID];
    double lat;
    double long_;
}
RegistrosPos;

typedef struct
{
    char id[TAM_ID];
    double lat;
    double longitud;
    double cont;
    double minima;
}RegistrosFinal;

typedef struct
{
    void* vec;
    int ce;
    int tamMax;
    size_t tamDato;
    float factorIncr;
}TdaVec;

typedef struct
{
    TdaVec* vec;
    void* act;
    void* fin;
    size_t tamDato;
}VecIt;




typedef int(*Cmp)(const void*, const void*);
typedef void(*Accion)(void*, const void*);
typedef void(*Trozar)(char*, void* dato);
typedef void(*Imprimir)(FILE*, void* dato);
typedef void(*Mostrar)(void*);

int SolucionEjercicio(char* NPosA, char* NposB, char* NposAB);


#endif // FUNCNES_DESARROLLO_MASSA_H_INCLUDED
