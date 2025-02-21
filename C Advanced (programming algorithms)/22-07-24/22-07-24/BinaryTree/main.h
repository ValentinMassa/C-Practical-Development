#ifndef BINARYTREE__MAIN_H_INCLUDED
#define BINARYTREE__MAIN_H_INCLUDED


typedef struct sNode{
    void* data;
    unsigned sizeData;
    struct sNode * left, *right;
}t_nodeTree;

typedef t_nodeTree * BinaryTree;

void createTree(BinaryTree *tree);
int loadTreeFromSortedFile(BinaryTree * tree, char* pf, unsigned tamInfo);
int loadNodeIntoTree(BinaryTree* tree, void* data, unsigned sizeD, int(*cmp)(const void*a, const void*b));
void walkPreOrder(BinaryTree* tree, void(*show)(void*a));
void printTreeWithLevels(BinaryTree * tree, int level, void (*showInfo)(void*));
void walkOrder(BinaryTree* tree, void* param, unsigned sized, void(*walk)(void*, void*, unsigned, unsigned) );
void walkInOrderUntilCondition(BinaryTree* Keytree, void* param, void* param2,void* param3, void(*walk)(void*, void*, void*),
                             int(*cmp)(const void*, const void*) );
BinaryTree * findNodeWithKey(BinaryTree * tree, void *key, unsigned sizekey, int(*cmp)(const void*, const void*));
void clearTree(BinaryTree * tree);
#endif // BINARYTREE__MAIN_H_INCLUDED
