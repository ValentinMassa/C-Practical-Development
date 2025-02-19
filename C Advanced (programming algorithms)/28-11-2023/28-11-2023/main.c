#include <stdio.h>
#include <stdlib.h>
#include "file_creator/main.h"
#include "utilities/main.h"

int main()
{
    if(!BinaryCreator(NAME_BIN))return 0;
    if(!txtFixedCreator(NAME_TXT, HAPPY_END))return 0;

    puts("----------------PRODUCTOS BEFORE UPDATE--------------------------");
    printf("\n%-20s \t %-9s \t%-5s \n", "DESCRIPTION", "PRICE", "STOCK");
    printBin(NAME_BIN, sizeof(Products), showProducts);
    puts("-----------------------------------------------------------------");


    processStock(NAME_BIN, NAME_TXT, NAME_STOCK_REQUIRED, NAME_ORDERS_DONE);




    puts("----------------PRODUCTOS AFTER UPDATE--------------------------");
    printf("\n %-20s \t %-9s \t%-5s \n", "DESCRIPTION", "PRICE", "STOCK");
    printBin(NAME_BIN, sizeof(Products), showProducts);
    puts("-----------------------------------------------------------------");


    return 0;
}
