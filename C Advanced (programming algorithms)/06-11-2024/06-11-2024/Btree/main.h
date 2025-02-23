#ifndef BTREE_MAIN_H_INCLUDED
#define BTREE_MAIN_H_INCLUDED

typedef struct Bnode
{
    void* data;
    unsigned sizeData;
    struct Bnode *left, *right;
}t_Bnode;

typedef t_Bnode *tree;

void createTree(tree* _tree);
int insertIntoTree(tree* _tree, void* data, unsigned sized, int(*cmp)(const void*, const void*),
                   void(*action)(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata));

void deleteTree(tree *t);
void walkTreeInOrder(tree *t, void* param, unsigned sized,
                     void(*action)(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata));
#endif // BTREE_MAIN_H_INCLUDED
