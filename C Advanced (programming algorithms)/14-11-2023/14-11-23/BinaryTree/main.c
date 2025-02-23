#include "./main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define reserveMemory(X,Y,Z,W)( ((X) = ((typeof(X))malloc(Y))) == NULL || \
                               (((Z) = malloc(W)) == NULL)?free(X), 0:1)
#define MIN(X,Y)((X)<(Y)?(X):(Y))

int readRegisterOfFileBy(void*data, void* puntFile, unsigned offset ,unsigned sizeData );
int loadTreefromFile(BTree * tree, void* param, unsigned sizedata, int li, int ls,
                     int(*action)(void* data, void* param, unsigned param2, unsigned sized));
BTree* findNodeKey(BTree * tree, void* key, int(*cmp)(const void*, const void*));



void createTree(BTree * tree)
{
    (*tree) = NULL;
}

void destroyTree(BTree *tree)
{
    if(!(*tree))return;

    destroyTree(&(*tree)->left);
    destroyTree(&(*tree)->right);
    free((*tree)->data);
    free((*tree));
    return;
}

int insertRegisterIntoTree(BTree* tree, void* data, unsigned sized, int(*cmp)(const void*, const void*))
{
    NodeBTree *aux;
    int result;

    while( (*tree) && (result = cmp((*tree)->data, data)))
    {
        if(result < 0)
            tree = &(*tree)->left;
        if(result > 0)
            tree = &(*tree)->right;
    }

    if(result == 0)
        return -1;

    if(!reserveMemory(aux, sizeof(NodeBTree), aux->data, sized))return 0;

    memcpy(aux->data, data, sized);
    aux->sizeData = sized;
    aux->left = aux->right = NULL;

    *(tree) = aux;
    return 1;
}



void walkTreeInOrder(BTree * tree, void* param, unsigned sized,
                     void(*action)(void*data, void*param, unsigned sized, unsigned sizep))
{
    if(!(*tree))return;

    walkTreeInOrder(&(*tree)->left, param, sized, action);
    action((*tree)->data, param, (*tree)->sizeData, sized);
    walkTreeInOrder(&(*tree)->right, param, sized, action);
    return;

}



int createTreeFromSortBin(BTree * tree, char * name, unsigned size)
{
    int amountreg, r;
    FILE* fp;
    if((*tree))return 0;

    fp = fopen(name, "rb");
    if(!fp)return 0;

    fseek(fp, 0L, SEEK_END);

    amountreg = (ftell(fp)/size);
    r = loadTreefromFile(tree, fp, size, 0, amountreg - 1, readRegisterOfFileBy);
    fclose(fp);
    return r;
}


int loadTreefromFile(BTree * tree, void* param, unsigned sizedata, int li, int ls,
                     int(*action)(void* data, void* param, unsigned param2, unsigned sized))
{
    int medium, r;

    if(li>ls)return 1;

    medium = (ls + li)/2;

    if(!reserveMemory((*tree), sizeof(NodeBTree), (*tree)->data, sizedata))return 0;

    if(!action((*tree)->data, param, medium, sizedata))
    {
        free((*tree)->data);
        free((*tree));
        return -1;
    }
    (*tree)->sizeData = sizedata;
    (*tree)->right = (*tree)->left = NULL;

    if( (r = loadTreefromFile(&(*tree)->left, param, sizedata, li, medium-1, action) != 1) )
        return r;
    return loadTreefromFile(&(*tree)->right, param, sizedata, medium + 1, ls, action);

}

int readRegisterOfFileBy(void*data, void* puntFile, unsigned offset ,unsigned sizeData )
{
    fseek((FILE*)puntFile, offset * sizeData, SEEK_SET);
    return fread(data, sizeData, 1, puntFile);
}


int DeleteTreeElement(BTree * tree, void* key, unsigned size, int(*cmp)(const void*, const void*))
{
    BTree *keyNode;
    if( !(keyNode = findNodeKey(tree, key, cmp)) )
        return -1;
    memcpy(key, (*keyNode)->data, MIN((*keyNode)->sizeData, size));
    return deleteTreeRoot(keyNode);
}

BTree* findNodeKey(BTree * tree, void* key, int(*cmp)(const void*, const void*))
{
    int result;

    while((*tree) && (result = cmp( (*tree)->data, key) ) )
    {
         if(result < 0)
            tree = &(*tree)->left;
         else
            tree = &(*tree)->right;
    }
    if(result == 0)
        return (BTree *)tree;
    return NULL;
}


int deleteTreeRoot(BTree * root)
{
    NodeBTree ** replacement, *deleted;

    if(!*root)return 0;

    free((*root)->data);
    if(!(*root)->left && !(*root)->right)
    {
        free(*root);
        *root = NULL;
        return 1;
    }

    replacement = getHightOfTree(&(*root)->left) > getHightOfTree(&(*root)->right)?
                    higherNodeTree(&(*root)->left):
                        higherNodeTree(&(*root)->right);

    deleted = *replacement;
    (*root)->data = deleted->data;
    (*root)->sizeData = deleted->sizeData;

     *replacement = deleted->left?deleted->left:deleted->right;
     free(deleted);
     return 1;
}

BTree * minorNodeTree(BTree * tree)
{
    if(!tree)return NULL;

    while((*tree)->left)
        tree = &(*tree)->left;
    return tree;
}

BTree * higherNodeTree( BTree * tree)
{
    if(!tree)return NULL;

    while((*tree)->right)
        tree = &(*tree)->right;
    return tree;
}

int getHightOfTree(const BTree * tree)
{
    int hl, hr;

    if(!(*tree))
        return 0;

    hl = getHightOfTree(&(*tree)->left);
    hr = getHightOfTree(&(*tree)->right);

    return (hl> hr? hl: hr) +1;
}
