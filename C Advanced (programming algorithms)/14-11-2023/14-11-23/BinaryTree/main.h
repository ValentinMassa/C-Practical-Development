#ifndef BYNARYTREE__MAIN_H_
#define BYNARYTREE__MAIN_H_


typedef struct sNodeBtree {
    void* data;
    unsigned sizeData;
    struct sNodeBtree *left, *right;
}NodeBTree;

typedef NodeBTree* BTree;

void createTree(BTree * tree);
void destroyTree(BTree *tree);
int insertRegisterIntoTree(BTree* tree, void* data, unsigned sized, int(*cmp)(const void*, const void*));
void walkTreeInOrder(BTree * tree, void* param, unsigned sized,
                     void(*action)(void*data, void*param, unsigned sized, unsigned sizep));

int createTreeFromSortBin(BTree * tree, char * name, unsigned sized);
int DeleteTreeElement(BTree * tree, void* key, unsigned sized, int(*cmp)(const void*, const void*));
int deleteTreeRoot(BTree * root);
BTree * minorNodeTree( BTree * tree);
BTree * higherNodeTree( BTree * tree);
int getHightOfTree(const BTree * tree);
#endif // BYNARYTREE__MAIN_H_
