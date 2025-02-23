#include "./main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define reserveMemory(X,Y,Z,W)(  (((X) = (typeof(X))malloc(Y)) == NULL ||  \
                                  ((Z) = malloc(W)) == NULL) ?free(X),0:1)


void createTree(tree* _tree)
{
    *_tree = NULL;
    return;
}
int insertIntoTree(tree* _tree, void* data, unsigned sized, int(*cmp)(const void*, const void*),
                   void(*action)(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata))
{
    int result;

    while( (*_tree) && (result = cmp((*_tree)->data, data)) )
    {
        if(result<0)
        _tree = &(*_tree)->left;
        else
        _tree = &(*_tree)->right;
    }

    if(result == 0)
    {
        action((*_tree)->data, data, (*_tree)->sizeData, sized);
        return 1;
    }

    if(!reserveMemory((*_tree), sizeof(t_Bnode),(*_tree)->data, sized))
        return 0;
    memcpy((*_tree)->data, data, sized);
    (*_tree)->sizeData = sized;
    (*_tree)->right = (*_tree)->left = NULL;
    return 1;

}

void deleteTree(tree *t){
    if(!(*t))return;

    deleteTree(&(*t)->left);
    deleteTree(&(*t)->right);
    free((*t)->data);
    free(*t);
}


void walkTreeInOrder(tree *t, void* param, unsigned sized,
                     void(*action)(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata))
{
    if(!*t)return;

    walkTreeInOrder(&(*t)->left, param, sized, action);
    action((*t)->data, param, (*t)->sizeData, sized);
    walkTreeInOrder(&(*t)->right, param, sized, action);
    return;
}
