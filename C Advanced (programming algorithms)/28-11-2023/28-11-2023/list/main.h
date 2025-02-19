#ifndef LIST__MAIN_H_INCLUDED
#define LIST__MAIN_H_INCLUDED

#include <stdio.h>

#define MIN(X, Y) ((X) < (Y)? X:Y)

#ifndef node
#define node
    typedef struct Node{
        void* data;
        unsigned sizeData;
        struct Node *next;
    }Node;
#endif // node

typedef Node * Slist;


typedef int(*cmp)(const void*a, const void*b);
typedef void (*action)(void *a, const void* b);

int InsertWithNoRepeatedInList(Slist *_list, void* data, unsigned sizeData, cmp CMP, action ACTION );
int isEmptyList(Slist *_list);
int isFullList(Slist *_list, unsigned sizeData);
void createList(Slist * _list);
void printList(Slist *_list, FILE* pf, void(*showList)(const void * data, FILE* file));
int getFirstElement(Slist * _list, void* data, unsigned sizeData);
void destroyList(Slist* _list);

#endif // MAIN_H_INCLUDED
