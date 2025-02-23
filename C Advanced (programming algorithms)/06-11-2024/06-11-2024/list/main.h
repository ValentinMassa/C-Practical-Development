#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct sNode
{
    void* data;
    unsigned sized;
    struct sNode *next;
}tNode;

typedef tNode * tlist;

void createList(tlist * l);
int insertIntoList(tlist * l, const void*data, unsigned sized);
void deleteList(tlist * l);
void sortList(tlist * l, int(*cmp)(const void*, const void*));
int showFirst(const tlist * l, void*data, unsigned sized);
int showLast(const tlist * l, void*data, unsigned sized);
void walkList(tlist *l, void* param, unsigned sized,void(*action)(void*, void*, unsigned, unsigned));
void invertList(tlist *l);

#endif // MAIN_H_INCLUDED
