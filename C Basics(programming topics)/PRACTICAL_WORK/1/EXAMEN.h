#ifndef EXAMEN_H_INCLUDED
#define EXAMEN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCAMPOS 30
#define FILAS 30
#define TamBuffer 1000
#define TAM_IDX_CAMPO 5

#define PermutacionesTxt "perm.txt"


#define ESespacio(a)(a == ' '?1:0)

int RestaurarColumna_Solucion(char* ,char* , int );




#endif // EXAMEN_H_INCLUDED
