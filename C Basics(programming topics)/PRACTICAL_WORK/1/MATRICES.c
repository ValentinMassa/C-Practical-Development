#include "MATRICES.h"

void LiberarMatriz(void**, void**);
void PonerValoresEnSmatriz(SMatriz*, void**, int, int, int, size_t, float);

int CrearMatrizGenerica(SMatriz * Matriz, int filas, int col, size_t tamData, float FactorA)
{
    void**inicio, **fin, **punt;

    punt = (void**)malloc(filas * sizeof(void*));

    if(!punt)
        return 0;

    fin = punt + col;

    for(inicio = punt; inicio < fin; inicio++)
    {
        *inicio = calloc(col, tamData);
        if(!(*inicio))
        {
            LiberarMatriz(punt, inicio);
            PonerValoresEnSmatriz(Matriz, NULL, 0,0,0,0,0);
            return 0;
        }
    }
    PonerValoresEnSmatriz(Matriz, punt,0, filas, col, tamData, FactorA);
    return 1;
}


void LiberarMatriz(void** fin, void** principio)
{
    void** end;
    for(end = principio - 1; principio >= fin; end--)
        {
                free(*end);
        }
}



void LiberarTotalMatriz(SMatriz * matriz)
{
    void **fin = matriz->matriz + matriz->filas;
    for(void** inicio = matriz->matriz; inicio<fin; inicio ++)
    {
        free(*inicio);
    }
    free(matriz->matriz);
    PonerValoresEnSmatriz(matriz, NULL, 0,0,0,0,0);
}

void PonerValoresEnSmatriz(SMatriz* matriz, void** punt, int ceFIla,
                            int fila, int col, size_t tam, float FactorAumento)
{
    matriz->matriz = punt;
    matriz->ceFil = ceFIla;
    matriz->col = col;
    matriz->filas = fila;
    matriz->tamData = tam;
    matriz->faactorAumento = FactorAumento;
}

