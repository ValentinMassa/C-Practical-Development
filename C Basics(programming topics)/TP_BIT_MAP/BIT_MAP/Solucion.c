
#include <stdio.h>
#include <stdlib.h>
#include "Solucion.h"

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
    Imagenbmp = AbrirImagen( (char*)getElementofTDAlist(&vecImage, 0) , AperturaBin);
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
        char NombreFinal[200]= "NEW_IMAGE_";
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
