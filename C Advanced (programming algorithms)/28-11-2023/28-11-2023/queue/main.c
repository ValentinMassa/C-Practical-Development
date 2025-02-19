#include "./main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void createQueue(sQueue *_queue)
{
    _queue->first = NULL;
    _queue->last = NULL;
    return;
}
int isTheQueueEmpty(sQueue *_queue)
{
    return _queue->first == NULL;
}
int isTheQueueFull(sQueue *_queue, unsigned sizeData)
{
    Node * auxNode = (Node*)malloc(sizeof(Node));
    void* auxdata = malloc(sizeData);

    free(auxdata);
    free(auxNode);
    return auxdata == NULL || auxNode == NULL;
}
int getElementFromQueue(sQueue* _queue, void* data, unsigned sizeData)
{
    Node *nodaux = _queue->first;
    if(!nodaux)return 0;

    _queue->first = nodaux->next;

    memcpy(data, nodaux->data, MIN(nodaux->sizeData, sizeData) );
    free(nodaux->data);
    free(nodaux);
    if(_queue->first == NULL)
        _queue->last = NULL;
    return 1;
}
int putElementInQueue(sQueue* _queue, const void* data, unsigned sizeData)
{
    Node * newnode = (Node*)malloc(sizeof(Node));

    if( (newnode == NULL) || ((newnode->data = malloc(sizeData)) == NULL) )
    {
        free(newnode);
        return 0;
    }

    memcpy(newnode->data, data, sizeData);
    newnode->sizeData = sizeData;
    newnode->next = NULL;

    if(_queue->last)
        _queue->last->next = newnode;
    else
        _queue->first = newnode;

    _queue->last = newnode;

    return 1;
}
void destroyQueue(sQueue* _queue)
{
    Node * auxnode;
    while( _queue->first)
    {
        auxnode = _queue->first;
        _queue->first = auxnode->next;
        free(auxnode->data);
        free(auxnode);
    }
    _queue->last = NULL;

}
int sshowFirstElement(sQueue* _queue, void* data, unsigned sizeData)
{
    if(_queue->first == NULL)return 0;

    memcpy(data, _queue->first->data, MIN(_queue->first->sizeData, sizeData));
    return 1;
}
