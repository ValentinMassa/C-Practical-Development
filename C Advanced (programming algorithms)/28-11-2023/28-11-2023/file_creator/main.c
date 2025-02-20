#include <stdio.h>
#include "./main.h"


unsigned char BinaryCreator(char* nameFile)
{
    FILE * file;
    Products _products[] = {
                                {"MARTILLO DE ACERO",5, 15.4},
                                {"PINZA CORTA CABLES",7, 11.7},
                                {"CABLES DE COBRE",6, 25.2},
                                {"MATES STANLEY",2, 60.8},
                                {"TORNILLOS PLANOS",78, 0.45},
                                {"TUERCAS DE 5",65, 0.4},
                                {"DESTORNILLADOR",5, 20.3},
                                {"CINTA METRICA",12, 140.4},
                                {"CINTA DE PAPEL",2, 11.7},
                                {"BOMBILLA STANLEY",17, 15.4}
    };
    file = fopen(nameFile, "wb");
    if(!file)
        return 0;

    if( fwrite(_products, sizeof(Products), (sizeof(_products)/(sizeof(Products))), file) != (sizeof(_products)/(sizeof(Products))))
    {
        puts("WRIITTING ERROR");
        fclose(file);
        remove(nameFile);
        return 0;
    }

    fclose(file);
    return 1;
}



unsigned char txtFixedCreator(char* txtName, int whatWeUpload)
{
    FILE* file;
    int iterator, quantReg;


    Order ordersHappyEnd[] =
    {
        {1,3, 2},
        {1,1, 3},
        {1,5, 50},
        {1,4, 1},//se puede hacer
        {2,10, 5},//se puede hacer
        {3,9, 1},
        {3,7, 2},//se puede hacer
        {4,6, 30},
        {4,1, 2},//se puede hacer
        {5,2, 6},
        {5,8, 7},
        {5,4, 1}//se puede hacer
    };
/*
{"MARTILLO DE ACERO",5, 15.4},
                                {"PINZA CORTA CABLES",7, 11.7},
                                {"CABLES DE COBRE",6, 25.2},
                                {"MATES STANLEY",2, 60.8},
                                {"TORNILLOS PLANOS",78, 0.45},
                                {"TUERCAS DE 5",65, 0.4},
                                {"DESTORNILLADOR",5, 20.3},
                                {"CINTA METRICA",12, 140.4},
                                {"CINTA DE PAPEL",2, 11.7},
                                {"BOMBILLA STANLEY",17, 15.4}
*/
     /* HOW IT HAS TO END
                                1{"MARTILLO DE ACERO",1, 15.4},
                                2{"PINZA CORTA CABLES",1, 11.7},
                                3{"CABLES DE COBRE",4, 25.2},
                                4{"MATES STANLEY",0, 60.8},
                                5{"TORNILLOS PLANOS",28, 0.45},
                                6{"TUERCAS DE 5",35, 0.4},
                                7{"DESTORNILLADOR",3, 20.3},
                                8{"CINTA METRICA",5, 140.4},
                                9{"CINTA DE PAPEL",1, 11.7},
                                10{"BOMBILLA STANLEY",12, 15.4}
                            */
    Order ordersNoPossible[] =
    {
        {1,3, 2},
        {1,1, 3},
        {1,5, 50},
        {1,4, 1},//se peude hacer
        {2,10, 5},//se peude hacer
        {3,9, 3},//no
        {3,7, 2},
        {4,6, 30},
        {4,1, 3},
        {5,2, 6},
        {5,8, 7},
        {5,4, 1}
    };

    /*HOW IT HAS TO END
                                1{"MARTILLO DE ACERO",-1, 15.4},
                                2{"PINZA CORTA CABLES",1, 11.7},
                                3{"CABLES DE COBRE",4, 25.2},
                                4{"MATES STANLEY",0, 60.8},
                                5{"TORNILLOS PLANOS",28, 0.45},
                                6{"TUERCAS DE 5",25, 0.4},
                                7{"DESTORNILLADOR",3, 20.3},
                                8{"CINTA METRICA",5, 140.4},
                                9{"CINTA DE PAPEL",-1, 11.7},
                                10{"BOMBILLA STANLEY",12, 15.4}
        */

    if(whatWeUpload != HAPPY_END){
        if(whatWeUpload != BAD_END){
            puts("Invalid input");
            return 0;}
    }

    file = fopen(txtName, "w");
    if(!file){return 0;}



    if(whatWeUpload == HAPPY_END)
    {
        quantReg = sizeof(ordersHappyEnd) / sizeof(Order);
        for( iterator =0; iterator < quantReg; iterator ++){

            fprintf(file, "%06u%06u%03u\n", ordersHappyEnd[iterator].cod_order, ordersHappyEnd[iterator].cod_prod, ordersHappyEnd[iterator].quantity );

        }
    }
    else
    {
        quantReg = sizeof(ordersNoPossible) / sizeof(Order);
        for( iterator =0; iterator < quantReg; iterator ++){

            fprintf(file, "%06u%06u%03u\n", ordersNoPossible[iterator].cod_order, ordersNoPossible[iterator].cod_prod, ordersNoPossible[iterator].quantity );

        }
    }

    fclose(file);
    return 1;




}
