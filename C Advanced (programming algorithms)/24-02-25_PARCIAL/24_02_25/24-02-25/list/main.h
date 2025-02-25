#ifndef LIST__MAIN_H_INCLUDED
#define LIST__MAIN_H_INCLUDED

typedef struct sNode {
    void *data;
    unsigned sized;
    struct sNode *next;
}Node;

typedef Node * sList;


void createList(sList *l);
void destroyList(sList *l);
int InsertIntoList(sList *l, const void*, unsigned);
int deleteFirstList(sList *l, void*, unsigned);


#endif // LIST__MAIN_H_INCLUDED
