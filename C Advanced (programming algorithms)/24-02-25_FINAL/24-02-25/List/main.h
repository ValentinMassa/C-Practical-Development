#ifndef LIST__MAIN_H_INCLUDED
#define LIST__MAIN_H_INCLUDED

typedef struct sNode{
    void* data;
    unsigned sized;
    struct sNode *next;
}Node;
typedef Node* slist;


void createList(slist * l);
void deleteList(slist * l);
int insertNelementsInOrder(slist * l, void* data, unsigned sized, unsigned* n, int(*cmp)(const void*, const void*));
void walkList(slist * l, void* param,void(*action)( void*,  void*));


#endif // LIST__MAIN_H_INCLUDED
