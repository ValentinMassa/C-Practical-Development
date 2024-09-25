/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el �ltimo campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Massa
    Nombre: Valentin
    DNI: 44.510.875
    Entrega: Sí
    -----------------
    Apellido: Resano
    Nombre: Federico Mariano
    DNI: 38.521.538
    Entrega: Sí
    -----------------
    Apellido: Tomadin
    Nombre: Alberto Pedro
    DNI: 20.254.592
    Entrega: Sí
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:
*/
#include <stdio.h>
#include <stdlib.h>
#include "funciones_grupo.h"

int solucion(int argc, char* argv[])
{
    int resultado;
    //argv manipulator
    VecEffectDefault effectDefault[TamMaxVecEffectDefault];
    TDAVectList effectList;
    TDAVectList vecImage;

    //header manipulator
    HeaderBmp Header;
    AdicDataBmp Data;
    FILE* Imagenbmp;
    Pixeles ** MatrizImagen;

    //inicializacion de punteros dinamicos en null(para usar rutina generica de free() )
    Data.CabeceraDIBext = NULL;
    Data.PaddingAdd = NULL;
    MatrizImagen = NULL;


    initializesListStructToDefault(&effectList);
    initializesListStructToDefault(&vecImage);

    ///
    FILE* ImagenNueva;

    ////////////////////////////////CODIGO///////////////////

    //ARGV PRIMERA PARTE
    CargarVectorOperaciones(effectDefault);
    resultado = ResultOfArgvOperations(argv, argc, &effectList, &vecImage, effectDefault,
                                TamMaxVecEffectDefault);
    if(resultado != TODO_OK)
    {
        RoutineMemoryLiberation(&effectList, &vecImage,&Data , MatrizImagen,0,0 );
        switch(resultado)
        {
        case ERR_ARG_NULL:
            return ERR_ARG_NULL;
        case ERR_VEC_LLENO:
            return ERR_VEC_LLENO;
        case ERR_ARG_EMPTY:
            return ERR_ARG_EMPTY;
        case ERR_ASIG_MEM:
            return ERR_ASIG_MEM;
        case ERR_WITHOUT_EFFECT:
            return ERR_WITHOUT_EFFECT;
        case ERR_WITHOUT_IMAGE:
            return ERR_WITHOUT_IMAGE;
        }
    }
    //FIN ARGV PRIMERA PARTE
    //CARGAR IMAGEN EN MEMORIA
    Imagenbmp = AbrirImagen( ((VecImag*)(vecImage.vec))[0].NameImage , AperturaBin);
    if(!Imagenbmp)
    {
        RoutineMemoryLiberation(&effectList, &vecImage, &Data , MatrizImagen,0,0 );
        return ERR_APERTURA;
    }


    resultado = LoadImageInMemory(&Header, &Data, Imagenbmp, &MatrizImagen);
    if(resultado != TODO_OK)
    {
        RoutineMemoryLiberation(&effectList, &vecImage,&Data , MatrizImagen,Header.palto,Header.pancho );
        switch(resultado)
        {
        case ERR_FORMATO:
            return ERR_FORMATO;
        case ERR_MATRIZ_CREACION:
            return ERR_MATRIZ_CREACION;
        case ERR_ASIG_MEM:
            return ERR_ASIG_MEM;
        }
    }//cada funcion cierra en sus errores lo que abrio
    fclose(Imagenbmp); //imagen ya cargada EN MEMORIA
    //FIN CARGAR IMAGEN EN MEMORIA

    //////////Tratamiento

    VecEffectList Effaux;
    VecImag effAuxImage;
    int h = getCeOfTda(&effectList);

    for(int i = 0; i < h ; i++)
    {
        char NombreFinal[200]= "ALFALFA_";
        LoadAuxWithData(&Effaux, &effectList, i);
        LoadAuxWithDataImg(&effAuxImage, &vecImage, 0);

        CrearNombreDeArchivo(Effaux.NameEffect, NombreFinal, effAuxImage.NameImage);

        ImagenNueva = AbrirImagen(NombreFinal, NuevoArchExtBin);
        if(!ImagenNueva)
        {
            RoutineMemoryLiberation(&effectList, &vecImage, &Data , MatrizImagen, Header.palto,Header.pancho);
            return ERR_APERTURA;
        }

        imagenTransformada(&Effaux, &vecImage, MatrizImagen, &Data, &Header, ImagenNueva);
        fclose(ImagenNueva);
    }
    puts("Proceso realizado exitosamente");
    RoutineMemoryLiberation(&effectList, &vecImage,&Data , MatrizImagen,Header.palto,Header.pancho);

    return  TODO_OK;
}
