#include "./main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../queue/main.h"
#include <time.h>

#define ORDER_CANT_BE_DONE 2



void updateRequiredStock(void *a, const void* b);
void showOrder(const void * data, FILE *file);
int loadBufferInOrder(Order *order, char *buffer);
void UpdateStock(sQueue *_queue, FILE* Products, FILE* Fordersdone);
void OrderCantBeDone(sQueue *_queue, FILE* fileError, FILE* fileProd);

int orderToFormat(Order *order, char *buffer);

void processOrders(char * namebin, char*nametxt, char *stockIsRequired, char * FOrdersDone)
{
    int quant, band, currentOrder;
    char buffer[BUFFER_MAX_SIZE], *checkgets;
    FILE* fileProd, *fileOrders, *filesrequired, *fileOrdersDone;

    sQueue queueorders;
    Order orderaux;
    Products auxproduc;

    createQueue(&queueorders);

    fileProd = fopen(namebin, "r+b");
    if(!fileProd)return;
    fileOrders = fopen(nametxt, "r");
    if(!fileOrders)return;
    filesrequired = fopen(stockIsRequired, "w");
    if(!filesrequired)return;
    fileOrdersDone = fopen(FOrdersDone, "w");
    if(!fileOrdersDone)return;


    checkgets = fgets(buffer, BUFFER_MAX_SIZE, fileOrders);
    if(checkgets == NULL)
    {
        puts("> Empty orders File. ABorted");
        return;
    }
    orderToFormat(&orderaux, buffer);
    currentOrder = orderaux.cod_order;

    while(checkgets != NULL)
    {
        band = 1;
        while(currentOrder == orderaux.cod_order && checkgets != NULL)
        {
            fseek(fileProd, sizeof(Products)*(orderaux.cod_prod - 1), SEEK_SET);
            fread(&auxproduc, sizeof(auxproduc), 1, fileProd);
            quant = auxproduc.stock - orderaux.quantity;
            if(quant < 0) band = 0;
            putElementInQueue(&queueorders, &orderaux, sizeof(orderaux));
            checkgets = fgets(buffer, BUFFER_MAX_SIZE, fileOrders);
            if(checkgets == NULL)continue;
            orderToFormat(&orderaux, buffer);
        }
        currentOrder = orderaux.cod_order;

        if(band)
        {
            UpdateStock(&queueorders, fileProd, fileOrdersDone);
            destroyQueue(&queueorders);
        }
        else{
            OrderCantBeDone(&queueorders,filesrequired, fileProd);
            destroyQueue(&queueorders);
        }
    }

    fclose(fileProd);
    fclose(fileOrders);
    fclose(fileOrdersDone);
    fclose(filesrequired);

}

int orderToFormat(Order *order, char *buffer)
 {
    char* punt;
    punt = strchr(buffer, '\n');
    if(!punt)return 0;
    *punt = '\0';
    if(sscanf(buffer, "%6u%6u%3u", &order->cod_order, &order->cod_prod, &order->quantity) != 3)return 0;
    return 1;
 }

void UpdateStock(sQueue *_queue, FILE* fileProd, FILE* fileOrdersDone)
{
    Order order;
    Products prod;
    float totalOrder = 0;

    while( getElementFromQueue(_queue, &order, sizeof(order))  )
    {
        fseek(fileProd, 1L * sizeof(Products) * (order.cod_prod - 1), SEEK_SET);
        fread(&prod, sizeof(Products), 1, fileProd);

        fseek(fileProd, -(long)sizeof(Products), SEEK_CUR);

        totalOrder += (order.quantity * prod.price);
        prod.stock -= order.quantity;

        fwrite(&prod, sizeof(Products), 1, fileProd);
        fseek(fileProd, 0, SEEK_CUR);
    }
    fprintf(fileOrdersDone, "ORDER: %u|TOTAL: %f \n", order.cod_order, totalOrder);

    return;
}

void OrderCantBeDone(sQueue *_queue, FILE* fileError, FILE* fileProd)
{
    Order order;
    Products prod;
    int totalMissing;

    while( getElementFromQueue(_queue, &order, sizeof(order))  )
    {
        fseek(fileProd, 1L * sizeof(Products) * (order.cod_prod - 1), SEEK_SET);
        fread(&prod, sizeof(Products), 1, fileProd);
        totalMissing = prod.stock - order.quantity ;
        if(totalMissing >= 0)continue;
        fprintf(fileError, "%-d | %-s \t | %-d\n", order.cod_order ,prod.description, totalMissing );
    }
    return;
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
