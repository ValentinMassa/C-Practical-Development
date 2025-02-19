#include "./main.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void createQueue(sQueue *_queue)
{
    _queue->first = _queue->last = NULL;
    return ;
}
void destructQueue(sQueue *_queue)
{
    Node * auxnode;
    while(_queue->first)
    {
        auxnode = _queue->first;
        _queue->first = auxnode->next;
        free(auxnode->data);
        free(auxnode);
    }
    _queue->last = NULL;
    return;
}
int showFirstInQueue(const sQueue*_queue, void* data, unsigned sizeData)
{
    if(!_queue->first)return 0;

    memcpy(data, _queue->first->data, MIN(_queue->first->sizeData, sizeData));



    return 1;
}
int getQueueElement(sQueue*_queue, void* data, unsigned sizeData)
{
    Node * nodeaux = _queue->first;
    if(!nodeaux)return 0;

    _queue->first = nodeaux->next;

    memcpy(data, nodeaux->data, MIN(sizeData, nodeaux->sizeData));

    if(!_queue->first) _queue->last = NULL;

    return 1;
}
int putElementInQueue(sQueue*_queue, const void* data, unsigned sizeData)
{
    Node *nodeaux;

    if( (nodeaux = (Node*)malloc(sizeof(Node)))== NULL ||
       (nodeaux->data = malloc(sizeData))==NULL )
    {
        free(nodeaux);
        return 0;
    }
    nodeaux->next =NULL;
    memcpy(nodeaux->data,data,sizeData);
    nodeaux->sizeData = sizeData;

    if(_queue->last)_queue->last->next = nodeaux;
    else _queue->first = nodeaux;

    _queue->last = nodeaux;

    return 1;
}
int isQueueEmpty(const sQueue *_queue)
{
    return _queue->first == NULL;
}
int isQueueFull(const sQueue *_queue, unsigned sizedata)
{
    Node *aux;
    void * data;

    aux = (Node*)malloc(sizeof(Node));
    data = malloc(sizedata);
    free(data);
    free(aux);
    return data == NULL|| aux == NULL;
}
