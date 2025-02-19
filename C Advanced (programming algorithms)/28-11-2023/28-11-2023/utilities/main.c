#include "./main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../list/main.h"
#include "../queue/main.h"
#include <time.h>

#define ORDER_CANT_BE_DONE 2



int compeareOrders(const void*a, const void*b);
void updateRequiredStock(void *a, const void* b);
void showOrder(const void * data, FILE *file);
int LoadOrdersInList(Slist* orders, char* txtname);

int LoadUpdatedStockInQueque(Slist * _list, sQueue * _queue, char* namebin);

int loadBufferInOrder(Order *order, char *buffer);
int UpdateStock(sQueue *_queue, char* nameFile, char* Fordersdone);
int OrderCantBeDone(sQueue *_queue, char* nameFileError, char* nameBin);


int processStock(char * namebin, char*nametxt, char *stockIsRequired, char * FOrdersDone)
{
    int result;
    Slist orders;
    sQueue queueorders;

    createList(&orders);

    if(!LoadOrdersInList(&orders, NAME_TXT)) return -2;

    //printf("Products in list: \n%-s \t %-s \t%-s \n", "COD ORDER", "COD PROD", "CANT");
    //printList(&orders, NULL, showOrder);

    createQueue(&queueorders);

    result = LoadUpdatedStockInQueque(&orders, &queueorders, namebin);

    if(!result)return 0;

    if(result != ORDER_CANT_BE_DONE)
    {
        UpdateStock(&queueorders, namebin, FOrdersDone);
        remove(stockIsRequired);
    }
    else{
        printf("\n >The process cant be done. check %s \n\n", stockIsRequired);
        OrderCantBeDone(&queueorders, stockIsRequired, namebin);
    }

    destroyQueue(&queueorders);
    destroyList(&orders);

    return 1;
}

int UpdateStock(sQueue *_queue, char* nameFile, char* Fordersdone)
{
    Order order;
    Products prod;
    float totalOrder = 0;
    char date[30];
    time_t _time;
    struct tm *tmPtr;

    FILE* fileProd = fopen(nameFile, "r+b");
    if(!fileProd)return 0;

    while( getElementFromQueue(_queue, &order, sizeof(order))  )
    {
        fseek(fileProd, 1L * sizeof(Products) * (order.cod_prod - 1), SEEK_SET);
        fread(&prod, sizeof(Products), 1, fileProd);

        fseek(fileProd, -(long)sizeof(Products), SEEK_CUR);


        totalOrder += ((prod.stock) - order.quantity) * prod.price;
        prod.stock = order.quantity;

        fwrite(&prod, sizeof(Products), 1, fileProd);
        fseek(fileProd, 0, SEEK_CUR);

    }
    fclose(fileProd);

    FILE* fileOrdersDone = fopen(Fordersdone, "a");
    if(!fileOrdersDone)return 0;

    _time = time(NULL);
    tmPtr = localtime(&_time);


    strftime(date, sizeof(date), "%c", tmPtr);

    fprintf(fileOrdersDone, "DATE OF THE ORDER: %s , TOTAL: %f \n",date, totalOrder);


    return 1;
}

int OrderCantBeDone(sQueue *_queue, char* nameFileError, char* nameBin)
{
    Order order;
    Products prod;
    int band = 0;

    FILE* fileError= fopen(nameFileError, "w");
    if(!fileError)return 0;
    FILE* fileProd = fopen(nameBin, "rb");
    if(!fileProd)return 0;

    while( getElementFromQueue(_queue, &order, sizeof(order))  )
    {
        if(order.quantity >= 0)continue;

        fseek(fileProd, 1L * sizeof(Products) * (order.cod_prod - 1), SEEK_SET);
        fread(&prod, sizeof(Products), 1, fileProd);

        if(band)
        {
            fprintf(fileError, "%-20s \t | %-s\n", "DESCRIPTION", "STOCK REQUIRED TO BE DONE");
            band = 1;
        }

        fprintf(fileError, "%-20s \t | %-5d\n", prod.description, ((order.quantity) * -1) );
    }
    fclose(fileError);
    fclose(fileProd);
    return 1;
}
int LoadUpdatedStockInQueque(Slist * _list, sQueue * _queue, char* namebin)
{
    Order order;
    Products prodaux;
    int flag = 0;
    int total;

    FILE *file = fopen(namebin, "rb");
    if(!file)
        return 0;

    while( getFirstElement(_list, &order, sizeof(order)) )
    {
        fseek(file, 1L * sizeof(Products) * (order.cod_prod - 1), SEEK_SET);
        fread(&prodaux, sizeof(Products), 1, file);

        total = prodaux.stock - order.quantity;
        order.quantity = total;
        if(total < 0 && !flag)
            flag = 1;
        if(!putElementInQueue(_queue, &order, sizeof(order)))return 0;

    }
    fclose(file);
    return flag?ORDER_CANT_BE_DONE:1;
}

 int LoadOrdersInList(Slist* orders, char* txtname)
 {
     char buffer[BUFFER_MAX_SIZE];
     Order order;
     FILE* file = fopen(txtname,"rt");
     if(!file)
        return 0;

     while(fgets(buffer, BUFFER_MAX_SIZE, file) != NULL)
     {
         if(!loadBufferInOrder(&order, buffer))return 0;
         if(!InsertWithNoRepeatedInList(orders, &order, sizeof(order), compeareOrders, updateRequiredStock))
            return 0;
     }
     fclose(file);
     return 1;
 }

void printBin(char * filename, unsigned tamData, show SHOW)
{
    void* data;
    FILE* file = fopen(filename, "rb");
    if(!file)return;

    data = malloc(tamData);
    if(!data)return;

    while( 1 == fread(data, tamData, 1, file) )
    {
        SHOW(data);
    }
    free(data);

    return;
}

void showProducts(const void * data)
 {
     Products *prod = (Products*)data;
     printf("%-20s \t $%8.2f \t%-5u \n", prod->description, prod->price, prod->stock);
     return;
 }

void showOrder(const void * data, FILE *file)
 {
     Order * order = (Order*)data;
     printf("%-6u \t %-6u \t %-3u \n", order->cod_order, order->cod_prod, order->quantity);
     return;
 }

int loadBufferInOrder(Order *order, char *buffer)
 {
    char* punt;
    punt = strchr(buffer, '\n');
    if(!punt)return 0;
    *punt = '\0';
    if(sscanf(buffer, "%6u%6u%3u", &order->cod_order, &order->cod_prod, &order->quantity) != 3)return 0;
    return 1;


 }

int compeareOrders(const void*a, const void*b)
{
     Order * ai = (Order*)a;
     Order * bi = (Order*)b;
    return ai->cod_prod - bi->cod_prod;
}

void updateRequiredStock(void* a, const void *b)
{
    Order * ai = (Order*)a;
    Order * bi = (Order*)b;

    ai->quantity += bi->quantity;
    return;
}
