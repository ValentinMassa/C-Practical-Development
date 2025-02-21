#include "./main.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ReserveNodeMemory(X, Y, Z, W)(\
                        ((X) = (typeof(X))malloc(Y)) == NULL || \
                        ((Z) = malloc(W)) == NULL ? free(X), 0 : 1)

int loadFromSortedFileRec(BinaryTree* tree, void* parameter,
                       int (*read)(void*data, void*parameter, int offset, unsigned tam),
                          int inferiorLimit, int superiorLimit, unsigned sizedata);

int loadRegisterfromFile(void* data, void *parameter, int offset, unsigned sizeData);
void walkPosOrderToDelete(BinaryTree* tree, void(*action)(void*a));
void deleteNode(void * node);


void createTree(BinaryTree *tree)
{
    *tree = NULL;
    return;
}

int loadTreeFromSortedFile(BinaryTree * tree, char* pf, unsigned tamInfo)
{
    int cantReg, r;
    FILE* file;

    if(*tree) return 0;

    if(! (file = fopen(pf, "rb")))return 0;

    fseek(file, 0L, SEEK_END);
    cantReg = ftell(file)/tamInfo;
    r = loadFromSortedFileRec(tree, file, loadRegisterfromFile, 0, cantReg-1, tamInfo);
    fclose(file);

    return r;
}

int loadFromSortedFileRec(BinaryTree* tree, void* parameter,
                       int (*read)(void*, void*, int, unsigned tam),
                          int inferiorLimit, int superiorLimit, unsigned sizedata)
{
    int middle = (inferiorLimit+superiorLimit)/2, r;

    if(inferiorLimit > superiorLimit)
        return 1;//thats nice bcs you walked all file

    if(!ReserveNodeMemory((*tree), sizeof(t_nodeTree), (*tree)->data, sizedata))
        return 0;//memory error

    if(!read((*tree)->data, parameter, middle, sizedata))
    {
        free((*tree)->data);
        free(*tree);
        return -1;//read error
    }
    (*tree)->sizeData = sizedata;
    (*tree)->left = (*tree)->right = NULL;

    if( (r = loadFromSortedFileRec(&(*tree)->left, parameter,read, inferiorLimit, middle-1, sizedata)) != 1)
            return r;
    return loadFromSortedFileRec(&(*tree)->right, parameter,read, middle+1, superiorLimit, sizedata);
}


int loadRegisterfromFile(void* data, void *parameter, int offset, unsigned sizeData)
 {
     fseek((FILE*)parameter, offset * sizeData, SEEK_SET);
     return fread(data, sizeData, 1, (FILE*)parameter);

 }


int loadNodeIntoTree(BinaryTree* tree, void* data, unsigned sizeD, int(*cmp)(const void*a, const void*b))
{
    int result;
    t_nodeTree* newNode;
    while(*tree)
    {
        result = cmp((*tree)->data, data);
        if(result < 0)
            tree = &(*tree)->left;
        else if(result > 0)
            tree = &(*tree)->right;
        else return -1;
    }

    if(!ReserveNodeMemory(newNode, sizeof(t_nodeTree), newNode->data, sizeD)) return 0;

    memcpy(newNode->data,data, sizeD);
    newNode->sizeData = sizeD;
    newNode->left = newNode->right = NULL;
    *tree = newNode;
    return 1;
}


  void walkPreOrder(BinaryTree* tree, void(*show)(void*a))
  {
        if(!(*tree))return;

        show((*tree)->data);
        walkPreOrder(&(*tree)->left, show);
        walkPreOrder(&(*tree)->right, show);
  }

void walkInOrderUntilCondition(BinaryTree* Keytree, void* param, void* param2,void* param3, void(*walk)(void*, void*, void*),
                             int(*cmp)(const void*, const void*) )
  {
        if(!(*Keytree))return;

        if(cmp((*Keytree)->data, param) == 0)
        {
            walkInOrderUntilCondition(&(*Keytree)->left, param, param2, param3, walk, cmp);
            walk((*Keytree)->data,param2,param3);
            walkInOrderUntilCondition(&(*Keytree)->right, param, param2, param3, walk, cmp);
        }
        if(cmp((*Keytree)->data, param) != 0)
        {
            walkInOrderUntilCondition(&(*Keytree)->left, param, param2, param3, walk, cmp);
            walkInOrderUntilCondition(&(*Keytree)->right, param, param2, param3, walk, cmp);
        }
        return;
  }

void printTreeWithLevels(BinaryTree * tree, int level, void (*showInfo)(void*)) {
    if ((*tree) == NULL) {
        return;
    }

    printTreeWithLevels(&(*tree)->right, level + 1, showInfo); // Print right subtree

    for (int i = 0; i < level; i++) {
        printf("    "); // Indentation for each level
    }

    printf("level %d: ", level);
    showInfo((*tree)->data);  // Print info of the current node
    printf("\n");

    printTreeWithLevels(&(*tree)->left, level + 1, showInfo); // Print left subtree
}

BinaryTree * findNodeWithKey(BinaryTree * tree, void *key, unsigned sizekey, int(*cmp)(const void*, const void*))
{
    int r;

    while(*tree && (r = cmp((*tree)->data, key)))
    {
        if(r<0)
            tree = &(*tree)->left;
        else
            tree = &(*tree)->right;
    }
    if(!*tree)return NULL;
    return tree;
}

void clearTree(BinaryTree * tree)
{
    walkPosOrderToDelete(tree,deleteNode);
}

void deleteNode(void * element)
{
    t_nodeTree * node = (t_nodeTree *)element;
    if(!node)return;
    free(node->data);
    free(node);
    return;
}


void walkPosOrderToDelete(BinaryTree* tree, void(*action)(void*a))
  {
        if(!(*tree))return;

        walkPosOrderToDelete(&(*tree)->left, action);
        walkPosOrderToDelete(&(*tree)->right, action);
        action(*tree);
  }

