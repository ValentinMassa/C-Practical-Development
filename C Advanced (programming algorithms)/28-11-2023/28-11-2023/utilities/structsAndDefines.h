#ifndef UTILITIES__STRUCTSANDDEFINES_H_INCLUDED
#define UTILITIES__STRUCTSANDDEFINES_H_INCLUDED

#define NAME_BIN "productos.dat"
#define NAME_TXT "pedidos.txt"
#define NAME_STOCK_REQUIRED "pedidos_faltantes.txt"
#define NAME_ORDERS_DONE "pedidios_realizados.txt"
#define BUFFER_MAX_SIZE 200
#define SIZE_MAX_NAME_PROD 20

typedef struct
{
    char description[SIZE_MAX_NAME_PROD];
    unsigned stock;
    float price;
}Products;

typedef struct
{
    unsigned cod_order;
    unsigned cod_prod;
    int quantity;
}Order;

#endif // STRUCTSANDDEFINES_H_INCLUDED
