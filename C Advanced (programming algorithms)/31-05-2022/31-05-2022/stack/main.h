#ifndef STACK__MAIN_H_INCLUDED
#define STACK__MAIN_H_INCLUDED

#ifndef NodeStruct
#define NodeStruct
typedef struct Node{
        void* data;
        unsigned sizeData;
        struct Node *next;
}Node;
#endif // NodeStruct

#define MIN(X,Y)((X) < (Y)?X:Y)

typedef Node * Stack;

void createStack(Stack* _stack);
void destroyStack(Stack* _stack);
int showTop(const Stack * _stack, void* data, unsigned sizeData);
int popElement(Stack *_stack, void*data, unsigned sizeData);
int pushElemnt(Stack *_stack, const void*data, unsigned sizeData);
int isStackFull(Stack *_stack,unsigned sizeData);
int isEmptyStack(Stack *_stack);


#endif // STACK__MAIN_H_INCLUDED
