#ifndef BREE__MAIN_H_INCLUDED
#define BREE__MAIN_H_INCLUDED


typedef struct sNodeBtree {
    void *data;
    unsigned sized;
    struct sNodeBtree *left, *right;
}NodeBtree;

typedef NodeBtree * tree;


void createBTree(tree * t);
void deleteBTree(tree * t);
int insertIntoBtree(tree * t, void* data, unsigned sized, int(*cmp)(const void*, const void*),
                     void(*action)(void*datat, void*data,unsigned sizedt, unsigned sized));
void walkTreeInOrder(tree * t, void* param, void(*action)(void*, void*));
int walkTreeInOrderLoadingSomething(tree * t, void* param, int(*action)(void*, void*));
int searchDataKeyNode(tree * t, void* data, unsigned sized, int(*cmp)(const void*, const void*));
#endif // BREE__MAIN_H_INCLUDED
