#include "main.h"
#include <stdio.h>
#include <stdlib.h>

//hechas por MASSA
bool VerificarYGenerarVectorDeDatosPadding(AdicDataBmp * data)
{
    if(data->padding != 0)
    {
        data->PaddingAdd = (unsigned char*)calloc(data->padding, sizeof(unsigned char));
        if(!data->PaddingAdd)
        {
            puts("Error asignacion memoria");
            data->PaddingAdd = NULL;
           return false;
        }
    }
    return true;
}


int CalcularPadding(int pancho)
{
    int padding = 0;

    while( ((pancho*3) + padding) % 4 != 0)
    {
        padding ++;
    }
    return padding;
}



////
