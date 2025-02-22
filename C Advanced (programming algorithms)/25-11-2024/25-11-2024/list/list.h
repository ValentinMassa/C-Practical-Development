#ifndef LIST__LIST_H_INCLUDED
#define LIST__LIST_H_INCLUDED

typedef struct sNode
{
    void *data;
    unsigned sizeData;
    struct sNode *next;
}tNode;

typedef tNode* sList;

void createList(sList * _list);
int loadElementIntoList(sList * _list, const void* data,unsigned sized);
void sortList(sList * _list, int(*cmp)(const void*, const void*));
void invertList(sList * _list);
void freeList(sList * _list);
void walkList(sList *_list, void* param, unsigned sized,
              void(*action)(void*data, void*param,
                            unsigned sizeparam, unsigned sizedata));

#endif // LIST__LIST_H_INCLUDED
