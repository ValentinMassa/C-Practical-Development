#ifndef MATRIZ_MATRIZ_H
#define MATRIZ_MATRIZ_H

#include <stddef.h>


void** crearMatriz(int fil, int col, size_t tamElem);
void destruirMatriz(void** mat, int fil);
void mostrarMatriz(int fil, int col, int** mat);


#endif //MATRIZ_MATRIZ_H
