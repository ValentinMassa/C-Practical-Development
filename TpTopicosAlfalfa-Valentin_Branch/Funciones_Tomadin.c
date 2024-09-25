#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funciones_tomadin.h"




void cambiarTonalidad(Pixeles* pixel, const float procentaje, int const color)
{
    int valor;

    valor = (int)pixel->pixel[color] * procentaje;

    if(valor > 255)
        valor = 255;

    pixel->pixel[color] = (unsigned char)valor;
}

void transformarAGris (Pixeles *pixel,  const float No1, const int No2) // Este seria una copia. Para trabajar con el original (t_pixel *pixel)
{
    unsigned char promedio = (pixel->pixel[RED] + pixel->pixel[GREEN] + pixel->pixel[BLUE]) / 3;

    pixel->pixel[RED] = promedio;
    pixel->pixel[GREEN] = promedio;
    pixel->pixel[BLUE] = promedio;
}

void aumentarContraste (Pixeles *pixel , const float porcentaje, const int No2)
{
    int i,valorAumentado;

    for(i = 0 ; i < 3; i++)
    {
        valorAumentado = pixel->pixel[i] * porcentaje;
        if(valorAumentado > 255)
            valorAumentado = 255;

        pixel->pixel[i] = valorAumentado;
    }
}

void reducirContraste (Pixeles * pixel, const float porcentaje, const int No2)
{
    int i,valorDisminuido;

    for(i = 0 ; i < 3; i++)
    {
        valorDisminuido = pixel->pixel[i] * porcentaje;
        if(valorDisminuido < 0 )
            valorDisminuido = 0;

        pixel->pixel[i] = valorDisminuido;
    }
}
