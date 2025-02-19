#ifndef QUEUE__MAIN_H_INCLUDED
#define QUEUE__MAIN_H_INCLUDED

#ifndef NodeStruct
#define NodeStruct
typedef struct Node{
        void* data;
        unsigned sizeData;
        struct Node *next;
}Node;
#endif // Node

#ifndef MIN
#define MIN(X,Y)((X) < (Y)?X:Y)
#endif // MIN

typedef struct
{
    Node *first;
    Node* last;
}sQueue;


void createQueue(sQueue *_queue);
void destructQueue(sQueue *_queue);
int showFirstInQueue(const sQueue*_queue, void* data, unsigned sizeData);
int getQueueElement(sQueue*_queue, void* data, unsigned sizeData);
int putElementInQueue(sQueue*_queue, const void* data, unsigned sizeData);
int isQueueEmpty(const sQueue *_queue);
int isQueueFull(const sQueue *_queue, unsigned sizedata);



#endif // QUEUE__MAIN_H_INCLUDED
