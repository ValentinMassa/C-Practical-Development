#ifndef SOLUCION_H_INCLUDED
#define SOLUCION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR 0
#define OK 1

//Matriz
#define Filasmin 10
#define ColMax 30
#define MaxFilas 80000

//Tda
#define tamMaxVec 10
//Compartido
#define FactorIncremento 0.6


#define Tambuffer 300
#define PermIdx "Perm.txt"

int restaurarColumnaALU(char *TABLAPERMUTADA, char* TABLARESTAURADA, int NUMEROCAMPO);

#endif // SOLUCION_H_INCLUDED
