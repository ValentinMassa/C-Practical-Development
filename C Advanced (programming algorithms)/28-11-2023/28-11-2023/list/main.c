#include "./main.h"
#include <stdlib.h>
#include <string.h>

void createList(Slist * _list)
{
    *_list = NULL;
}

int isFullList(Slist *_list,unsigned sizeData)
{
    Node * auxNode = (Node*)malloc(sizeof(Node)) ;
    void* auxData = malloc(sizeData);

    free(auxNode);
    free(auxData);

    return auxNode == NULL || auxData == NULL;
}

int isEmptyList(Slist *_list)
{
    return *_list == NULL;
}


int InsertWithNoRepeatedInList(Slist *_list, void* data, unsigned sizeData, cmp CMP, action ACTION )
{
    Node * auxNode;

    while( *(_list) )
    {
        if( CMP( (*_list)->data, data) == 0)
        {
            if(ACTION)
                ACTION((*_list)->data, data);
            return 1;
        }
        _list = &(*_list)->next;
    }

    if( (auxNode = (Node*)malloc(sizeof(Node))) == NULL ||
                    (auxNode->data = malloc(sizeData)) == NULL )
    {
        free(auxNode);
        return 0;
    }

    memcpy(auxNode->data, data, sizeData);
    auxNode->sizeData = sizeData;
    auxNode->next = NULL;
    *_list = auxNode;

    return 1;
}


void printList(Slist *_list, FILE* pf, void(*showList)(const void * data, FILE* file))
{
    while(*_list)
    {
        showList((*_list)->data, pf);
        _list = &(*_list)->next;
    }
    return;
}

int getFirstElement(Slist * _list, void* data, unsigned sizeData)
{
    Node * nodeaux;

    if(!*_list)return 0;

    nodeaux = (*_list);
    (*_list) = nodeaux->next;

    memcpy(data, nodeaux->data, MIN(nodeaux->sizeData, sizeData));

    free(nodeaux->data);
    free(nodeaux);


    return 1;

}
void destroyList(Slist* _list)
{
    Node* nodeaux;

    while(*_list)
    {
        nodeaux = *_list;
        *_list = nodeaux->next;
        free(nodeaux->data);
        free(nodeaux);
        _list = &(*_list)->next;
    }

}

