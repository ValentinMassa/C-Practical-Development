#include "./list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tNode* findMinor(sList * _list, int(*cmp)(const void*, const void*));

void createList(sList * _list)
{
    (*_list) = NULL;
}
int loadElementIntoList(sList * _list, const void* data,unsigned sized)
{
    tNode * aux;
    aux = (tNode*)malloc(sizeof(tNode));
    if(aux == NULL || (aux->data = malloc(sized)) == NULL)
    {
        free(aux);
        return 0;
    }
    while(*(_list))
    {
        _list  = &(*_list)->next;
    }

    memcpy(aux->data, data, sized);
    aux->sizeData = sized;
    aux->next= NULL;

    *(_list) = aux;
    return 1;
}
void sortList(sList * _list, int(*cmp)(const void*, const void*))
{
    tNode *minor;
    void* aux; unsigned auxs;
    int result;
    while( (*_list)->next)
    {
        minor = findMinor(&(*_list)->next, cmp);
        result = cmp((*_list)->data, minor->data);
        if(result > 0) // A - B: 5 /
        {
            aux = (*_list)->data;
            auxs  = (*_list)->sizeData;

            (*_list)->data = minor->data;
            (*_list)->sizeData = minor->sizeData;

            minor->data = aux;
            minor->sizeData = auxs;
        }
        _list = &(*_list)->next;
    }
    return;
}

tNode* findMinor(sList * _list, int(*cmp)(const void*, const void*))
{
    tNode* minor;

    minor = (*_list);
    _list = &minor->next;
    while(*_list)
    {
       if(cmp((*_list)->data, minor->data) < 0)
        {
            minor = (*_list);
        }
        _list = &(*_list)->next;
    }
    return minor;
}


void freeList(sList * _list)
{
    tNode  *aux;
    while(*(_list))
    {
        aux  = (*_list);
        (*_list) = aux->next;
        free(aux->data);
        free(aux);
    }
    return;
}

void invertList(sList * _list)
{
    tNode *rest;
    if( (*_list) == NULL || (*_list)->next == NULL )
        return;

    rest = (*_list)->next;

    invertList(&rest);

    (*_list)->next->next = (*_list);
    (*_list)->next = NULL;
    (*_list)=rest;
    return;
}

void walkList(sList *_list, void* param, unsigned sized,
              void(*action)(void*data, void*param,
                            unsigned sizeparam, unsigned sizedata))
{
    if(!(*_list))return;
    action((*_list)->data, param, sized, (*_list)->sizeData);
    walkList(&(*_list)->next, param, sized, action);
}

