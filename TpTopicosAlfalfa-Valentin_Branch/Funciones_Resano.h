#ifndef Funciones_Resano_H_INCLUDED
#define Funciones_Resano_H_INCLUDED

#include "main.h"
#include "stdbool.h"
#include "TDA_VECTOR.h"
#include "Funciones_Massa.h"


#define BLUE 0
#define GREEN 1
#define RED 2


bool imagenTransformada(VecEffectList *, TDAVectList*, Pixeles ** , AdicDataBmp *,
        HeaderBmp *, FILE*);


#endif // Funciones_Resano_H_INCLUDED
