#ifndef Funciones_Massa_H_INCLUDED
#define Funciones_Massa_H_INCLUDED


#include "main.h"
#include "TDA_VECTOR.h"

#include <stdbool.h>

//ARGV

int ResultOfArgvOperations(char* [], int , TDAVectList*, TDAVectList*,VecEffectDefault* , int);


void RoutineMemoryLiberation(TDAVectList*, TDAVectList* ,AdicDataBmp*, Pixeles **, int, int);
////

//general
int LoadImageInMemory(HeaderBmp *,AdicDataBmp *, FILE*, Pixeles***);

//

void GenerarNuevaImagen(Pixeles **, HeaderBmp * , AdicDataBmp* , FILE*);
//liberar memoria de struct DATA
void VerificarYLiberarMemoriaData(AdicDataBmp *data);

//funciones

void CargarVectorOperaciones(VecEffectDefault*);
FILE* AbrirImagen(char*, char*);
void EliminarmatrizDIN_Pixeles(Pixeles**, const int, const int);
///////////

void LoadAuxWithData(VecEffectList *, TDAVectList *, const int);
void LoadAuxWithDataImg(VecImag *, TDAVectList *, const int);
void CrearNombreDeArchivo(char*, char*, char*);

#endif // Funciones_Massa_H_INCLUDED
