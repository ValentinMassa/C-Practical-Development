#ifndef TDA_VECTOR_H_INCLUDED
#define TDA_VECTOR_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    void* vec;
    int ce;
    int maxElem;
    size_t sizeE;
}TDAVectList;

//definiciones

typedef int(*Cmp)(const void*,const void*);
//typedef bool(*action)(TDAVectList*, void*);

void initializesListStructToDefault(TDAVectList *);
bool CreateTdaVectorList(size_t, size_t, TDAVectList*);
bool LoadElementsInList_NoRepit(TDAVectList*, void*, Cmp);
bool LoadElementsInList(TDAVectList*, void*);
void FreeListMemory(TDAVectList *);
void* getElementofTDAlist(TDAVectList *, int);
int getMAxElementOfTda(TDAVectList *);
int getCeOfTda(TDAVectList *);
int getSizeOfTda(TDAVectList *);

#endif // TDA_VECTOR_H_INCLUDED
