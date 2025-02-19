#include "./main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createStack(Stack* _stack)
{
    *_stack = NULL;
    return;
}
void destroyStack(Stack* _stack)
{
    Node *aux;
    while(*_stack)
    {
        aux = *_stack;
        *_stack = aux->next;
        free(aux->data);
        free(aux);
    }
    return;
}
int showTop(const Stack * _stack, void* data, unsigned sizeData)
{
    if(!(*_stack)) return 0;

    memcpy(data, (*_stack)->data, MIN((*_stack)->sizeData, sizeData));
    return 1;
}
int popElement(Stack *_stack, void*data, unsigned sizeData)
{
    Node *aux = *_stack;
    if(!aux)return 0;

    *(_stack) = aux->next;
    memcpy(data, aux->data, MIN(aux->sizeData, sizeData));
    free(aux->data);
    free(aux);
    return 1;
}
int pushElemnt(Stack *_stack, const void*data, unsigned sizeData)
{
    Node * aux = (Node*)malloc(sizeof(Node));

    if(aux == NULL || (aux->data = malloc(sizeData)) == NULL)
    {
        free(aux);
        return 0;
    }

    memcpy(aux->data, data, sizeData);
    aux->sizeData = sizeData;
    aux->next = *_stack;
    *_stack = aux;
    return 1;
}
int isStackFull(Stack *_stack,unsigned sizeData)
{
    Node * aux = (Node*)malloc(sizeof(Node));
    void* data = malloc(sizeData);
    free(aux);
    free(data);
    return data== NULL || aux == NULL;
}
int isEmptyStack(Stack *_stack)
{
    return *_stack == NULL;
}
