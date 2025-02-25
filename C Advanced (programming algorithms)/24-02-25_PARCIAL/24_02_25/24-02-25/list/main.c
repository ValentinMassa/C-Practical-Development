#include "./main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN(X,Y) ((X) > (Y)?X:Y)

void createList(sList *l){
    *l = NULL;
}
void destroyList(sList *l){
    Node *aux;
    while(*l){
        aux = *l;
        l = &(*l)->next;
        free(aux->data);
        free(aux);
    }
    *l = NULL;
    return ;
}
int InsertIntoList(sList *l, const void* data, unsigned size){

    while(*l)
        l = &(*l)->next;

    *l = (Node*)malloc(sizeof(Node));

    if((*l) == NULL || ((*l)->data = malloc(size)) == NULL)
    {
        free(*l);
        return 0;
    }
    memcpy((*l)->data, data, size);
    (*l)->sized = size;
    (*l)->next = NULL;
    return 1;

}
int deleteFirstList(sList *l, void* data, unsigned size)
{
    Node *deleted;
    if(!*l)return 0;

    deleted = (*l);
    (*l) = deleted->next;

    memcpy(data, deleted->data, MIN(deleted->sized, size));

    free(deleted->data);
    free(deleted);
    return 1;
}

