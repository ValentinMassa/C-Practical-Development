#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TDA_VECTOR.h"

bool CreateTdaVectorList(size_t MaxElem, size_t tamData, TDAVectList* vector)
{
    void * aux = calloc(MaxElem, tamData);

    if(!aux)
    {
        puts("ERROR AL DECLARAR MEMORIA --CreateTdaVectorLista ");
        vector->vec = NULL;
        vector->ce = 0;
        vector->maxElem = 0;
        vector->sizeE = 0;
        return false;
    }
    vector->vec = aux;
    vector->ce = 0;
    vector->maxElem = MaxElem;
    vector->sizeE = tamData;

    return true;
}

bool LoadElementsInList_NoRepit(TDAVectList* vect, void* elemnt, Cmp compare)
{
    if(vect->maxElem == vect->ce)
    {
        puts("Vector Lleno");
        return false;
    }
    if (vect == NULL || elemnt == NULL)
    {
        puts("Puntero o elemento NULL");
        return false;
    }

    if(vect->ce == 0)
    {
        memcpy(vect->vec, elemnt, vect->sizeE);
        vect->ce = 1;
        return true;
    }

    void* point;
    void* end = vect->vec + (vect->ce * vect->sizeE);

    for(point = vect->vec; point < end; point += vect->sizeE)
    {
        if(compare(point,elemnt) == 0)
        {
            return true;
        }
    }

    memcpy(end, elemnt, vect->sizeE);
    vect->ce ++;
    return true;
}


bool LoadElementsInList(TDAVectList* vect, void* elemnt)
{
    if(vect->maxElem == vect->ce)
    {
        puts("Vector Lleno");
        return false;
    }
    if (vect == NULL || elemnt == NULL)
    {
        puts("Puntero o elemento NULL");
        return false;
    }

    void* punt = vect->vec + (vect->ce * vect->sizeE);

    memcpy(punt, elemnt, vect->sizeE);
    vect->ce ++;
    return true;
}
void FreeListMemory(TDAVectList *vector)
{
    free(vector->vec);
    vector->vec = NULL;
    vector->ce = 0;
    vector->sizeE = 0;
    vector->maxElem = 0;
}

void initializesListStructToDefault(TDAVectList *vector)
{
    vector->vec = NULL;
    vector->ce = 0;
    vector->sizeE = 0;
    vector->maxElem = 0;
}

void* getElementofTDAlist(TDAVectList * vector, int elemnt)
{
    return (void*)(vector->vec + (vector->sizeE * elemnt)) ;
}

int getMAxElementOfTda(TDAVectList * vector)
{
    return vector->maxElem;
}

int getCeOfTda(TDAVectList * vector)
{
    return vector->ce;
}

int getSizeOfTda(TDAVectList * vector)
{
    return vector->sizeE;
}

