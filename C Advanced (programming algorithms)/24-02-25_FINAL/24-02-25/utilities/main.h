#ifndef UTILITIES__MAIN_H_INCLUDED
#define UTILITIES__MAIN_H_INCLUDED


#define SIZE_BUFFER_MAX 2
#define SIZE_DESCRIPTION_MAX 30
#define OP_1 1
#define OP_2 2

int nMaxMin(char* namearch);


typedef struct{
    unsigned codeNumber;
    char description[SIZE_DESCRIPTION_MAX];
    unsigned quantity;

}t_Products;

typedef int(*cmp)(const void* a, const void* b);
void createBin(char* fname);
#endif // UTILITIES__MAIN_H_INCLUDED
