#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FactAumento 0.5

typedef struct
{
    void ** matriz;
    int col;
    int filas;
    int ceFil;
    float faactorAumento;
    size_t tamData;
}SMatriz;


int CrearMatrizGenerica(SMatriz *, int, int, size_t, float);
void LiberarTotalMatriz(SMatriz *);
#endif // MATRICES_H_INCLUDED
