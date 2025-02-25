#include "./main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_(X,Y) ((X) > (Y)?X:Y)

void createBTree(tree * t)
{
    *t = NULL;
}


void deleteBTree(tree * t)
{
    if(!*t)return;

    deleteBTree(&(*t)->left);
    deleteBTree(&(*t)->right);
    free((*t)->data);
    free(*t);
    return;
}

int insertIntoBtree(tree * t, void* data, unsigned sized, int(*cmp)(const void*, const void*),
                     void(*action)(void*datat, void*data,unsigned sizedt, unsigned sized)){

   int result;

   while( (*t) && (result = cmp((*t)->data, data)) )
   {
       if(result < 0)
        t = &(*t)->left;
       else
        t = &(*t)->right;
   }

    if(result == 0)
    {
        action((*t)->data, data, (*t)->sized, sized);
        return 1;
    }

    *t = (NodeBtree*)malloc(sizeof(NodeBtree));

    if((*t) == NULL || ((*t)->data = malloc(sized)) == NULL)
    {
        free(*t);
        return 0;
    }
    (*t)->left = (*t)->right = NULL;
    memcpy((*t)->data, data, sized);
    (*t)->sized = sized;
    return 1;
}

int searchDataKeyNode(tree * t, void* data, unsigned sized, int(*cmp)(const void*, const void*))
{
    int result;
    while( (*t) && (result = cmp((*t)->data, data)) )
   {
       if(result < 0)
        t = &(*t)->left;
       else
        t = &(*t)->right;
   }
   if(result == 0)
    {
        memcpy(data, (*t)->data, MIN_(sized, (*t)->sized));
        return 1;
    }
    return 0;

}


void walkTreeInOrder(tree * t, void* param, void(*action)(void*, void*))
{
    if(!(*t))return;
    walkTreeInOrder(&(*t)->left, param, action);
    action((*t)->data, param);
    walkTreeInOrder(&(*t)->right, param, action);
    return;
}
int walkTreeInOrderLoadingSomething(tree * t, void* param, int(*action)(void*, void*))
{
    if(!(*t))return 1;

    walkTreeInOrderLoadingSomething(&(*t)->left, param, action);
    if(!action((*t)->data, param))return 0;
    walkTreeInOrderLoadingSomething(&(*t)->right, param, action);
    return 1;
}
