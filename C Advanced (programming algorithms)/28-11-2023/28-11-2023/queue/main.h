#ifndef QUEUE__MAIN_H_INCLUDED
#define QUEUE__MAIN_H_INCLUDED

#ifndef node
#define node
    typedef struct Node{
        void* data;
        unsigned sizeData;
        struct Node *next;
    }Node;
#endif // node

typedef struct
{
    Node* first;
    Node* last;
}sQueue;

#define MIN(X, Y) ((X) < (Y)? X:Y)

void createQueue(sQueue *_Queque);
int isTheQuequeEmpty(sQueue *_Queque);
int isTheQuequeFull(sQueue *_Queque, unsigned sizeData);
int getElementFromQueue(sQueue* _Queque, void* data, unsigned sizeData);
int putElementInQueue(sQueue* _Queque, const void* data, unsigned sizeData);
void destroyQueue(sQueue* _Queque);
int sshowFirstElement(sQueue* _Queque, void* data, unsigned sizeData);




#endif // MAIN_H_INCLUDED
