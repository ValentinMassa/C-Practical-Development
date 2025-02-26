#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./main.h"

#define reserveMemory(X,Y,Z,W)( ( ((X) = (typeof(X))malloc(Y)) == NULL) || \
                               (((Z) = malloc(W)) == NULL)? free(X),0:1)

void createList(slist * l){
    *l = NULL;
    return;
}
void deleteList(slist * l){
    Node *aux;

    while(*l){
        aux = (*l);
        (*l) = aux->next;
        free(aux->data);
        free(aux);
    }
    *l = NULL;
    return;
}
int insertNelementsInOrder(slist * l, void* data, unsigned sized, unsigned* n,
                           int(*cmp)(const void*, const void*)){
    Node *aux, **end;
    int result;

    while((*l) != NULL){
        result = cmp((*l)->data, data);
        if(result<0)break;
        l = &(*l)->next;
    }

    if((*n)>0){
        if(!reserveMemory(aux, sizeof(Node), aux->data, sized)) return 0;
        memcpy(aux->data, data, sized);
        aux->sized = sized;

        if((*l) == NULL)//hay q insertar al final
        {
            aux->next = NULL;
            (*l) = aux;
        }
        else{
            aux->next = (*l);
            (*l) = aux;
        }
        (*n) -= 1;
        return 1;
    }
    else{
        if((*l) == NULL)return 1;
        end = l;
        while((*end)->next){
            end = &(*end)->next;
            }
        free((*end)->data);
        free(*end);
        (*end) = NULL;
        if(!reserveMemory(aux, sizeof(Node), aux->data, sized)) return 0;
        memcpy(aux->data, data, sized);
        aux->sized = sized;
        aux->next = (*l);
        (*l) = aux;
        return 1;
    }

}


void walkList(slist * l, void* param, void(*action)( void*,  void*))
{
    if(!*l)return;

    action((*l)->data, param);
    walkList(&(*l)->next, param, action);
    return;
}
