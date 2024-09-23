#include "main.h"
#include "TDA_VECTOR.h"
#include "Funciones_Massa.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el �ltimo campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Antunez
    Nombre: Matias
    DNI: 40.808.544
    Entrega: 05/05/2024
    -----------------
    Apellido: Resano
    Nombre: Federico Mariano
    DNI: 38.521.538
    Entrega: 05/05/2024
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/
////ARGV FUNCIONES DE USO PROPIO.
bool checkArgv(int);
int TreatmentOfArgv(char*[], int , TDAVectList* , TDAVectList* , VecEffectDefault* , int);
int Comparing_NameVsName(const void*,const void*);
void ErrorParametro(const char*);
bool IsThisABMPExtension(char *);
bool IsThisElementAEffectWithEqual(char *, VecEffectDefault*, int);
bool IsThisElementAEffect(char*, VecEffectDefault* , int );
bool IsThereADot(char*);
bool IsThereADash(char* aux);
bool IsThereAnEqual(char* aux);
void UploadValueWithEqual(char *, VecEffectList *);
void UploadValueWithoutEqual(char *, VecEffectList *);
void RoutineMemoryArgvLiberation(TDAVectList*, TDAVectList*);


////IMAGE IN MEMORY
//MATRIZ
Pixeles** CrearmatrizDIN_Pixel(const int, const int);
void EliminarmatrizDIN_Pixeles(Pixeles**, const int, const int);
//HEADER
int CargarHeaderEnMemoriaYcargarData(HeaderBmp*, AdicDataBmp *, FILE*);
bool VerificarQueEsBMP(HeaderBmp*, FILE*, char, char);
void LeerHeaderBmp(HeaderBmp*, FILE*);
bool VerificarYAsignarMemoriaDeSerNecHEaderExtendido(HeaderBmp *, AdicDataBmp *,FILE*, const int);


//Cargar Imag en memoria
void CargarMatrizImagen(FILE * Imagenbmp, Pixeles **MatrizImagen, const int, const int, const int, const int);



//

void CargarVectorOperaciones(VecEffectDefault * vector)
{
    strcpy(vector[0].NameEffect, "--escala-de-grises");
    strcpy(vector[1].NameEffect, "--espejar-horizontal");
    strcpy(vector[2].NameEffect, "--espejar-vertical");
    strcpy(vector[3].NameEffect, "--aumentar-contraste=");
    strcpy(vector[4].NameEffect, "--reducir-contraste=");
    strcpy(vector[5].NameEffect, "--tonalidad-azul=");
    strcpy(vector[6].NameEffect, "--tonalidad-verde=");
    strcpy(vector[7].NameEffect, "--tonalidad-roja=");
    strcpy(vector[8].NameEffect, "--recortar=");
    strcpy(vector[9].NameEffect, "--achicar=");
    strcpy(vector[10].NameEffect, "--rotar-derecha");
    strcpy(vector[11].NameEffect, "--rotar-izquierda");
    strcpy(vector[12].NameEffect, "--concatenar-horizontal");
    strcpy(vector[13].NameEffect, "--concatenar-vertical");
    strcpy(vector[14].NameEffect, "--comodin");
}

FILE* AbrirImagen(char* ruta, char* apertura)
{
    FILE* arch;
    arch = fopen(ruta, apertura);
    if(!arch)
    {
        fclose(arch);
        puts("Error apertura de iamgen");
        return NULL;
    }
    return arch;
}

///////////ARGV////////////


int ResultOfArgvOperations(char* Argv[], int argc, TDAVectList* VecEfectTDA, TDAVectList* VecImageTDA,
                        VecEffectDefault* effectDefault, int cantEComp)
{
    int resultado;
    if (!checkArgv(argc))
    {
        return ERR_ARG_EMPTY;
    }

    if(!CreateTdaVectorList(TamMaxVecEffectDefault, sizeof(VecEffectList), VecEfectTDA))
    {
        return ERR_ASIG_MEM;
    }
    if(!CreateTdaVectorList(MaxImages, sizeof(VecImag), VecImageTDA))
    {
        RoutineMemoryArgvLiberation(VecEfectTDA, VecImageTDA);
        return ERR_ASIG_MEM;
    }

    resultado = TreatmentOfArgv(Argv, argc, VecEfectTDA, VecImageTDA, effectDefault,
                                TamMaxVecEffectDefault);

    if(getCeOfTda(VecImageTDA) == 0 )
    {
        puts("no se cargo ninguna imagen, vamos a cancelar el proceso");
        RoutineMemoryArgvLiberation(VecEfectTDA, VecImageTDA);
        return ERR_WITHOUT_IMAGE;
    }

    if( getCeOfTda(VecEfectTDA) == 0 )
    {
        puts("Ingrese Al menos Un efecto a realizar");
        RoutineMemoryArgvLiberation(VecEfectTDA, VecImageTDA);
        return ERR_WITHOUT_EFFECT;
    }

    if(resultado != TODO_OK)
    {
        RoutineMemoryArgvLiberation(VecEfectTDA, VecImageTDA);
        switch(resultado)
        {
            case ERR_ARG_NULL:
                return ERR_ARG_NULL;
            case ERR_VEC_LLENO:
                return ERR_VEC_LLENO;
        }
    }


    return TODO_OK;
}


bool checkArgv(int cantElem)
{
    if(cantElem < 2 || cantElem >= TamMaxVecEffectDefault + MaxImages + 1)
        //el + 1 es por el parametro del exec, total total 17 parametros(15 + 2) + 1
    {
        puts("Los parametros ingresados son cero o hubo exceso de parametros");
        return false;
    }
    return true;
}

void ErrorParametro(const char* data)
{
    puts("ERROR EN UN PARAMETRO:");
    printf("%s \n", data);
}

int TreatmentOfArgv(char* Argv[], int cantElemnt, TDAVectList* VecEfectTDA, TDAVectList* VecImageTDA,
                    VecEffectDefault* ListToComp, int cantEComp)
{
    int i;
    char auxGral[maxTamImage]; // lo maximo que puede tomar

    VecEffectList VecEffectAux;
    VecImag ImageAux;

    for(i=1; i<cantElemnt; i++)
    {
        if( ( (Argv[i] == NULL) || strlen(Argv[i]) > maxTamImage ) )
            {
                ErrorParametro(Argv[i]);
            }
        else
        {
            strcpy(auxGral, Argv[i]); //nos aseguramos q no sea null ni q supere el maximo de cadena
            if(IsThereADash(auxGral)) // hay -- ?
                {
                    if(IsThereAnEqual(auxGral)) // hay un = ?
                       {
                            if(IsThisElementAEffectWithEqual(auxGral, ListToComp, cantEComp))
                            {
                                UploadValueWithEqual(Argv[i], &VecEffectAux);
                                if ( LoadElementsInList_NoRepit(VecEfectTDA, &VecEffectAux,
                                                                Comparing_NameVsName) == false)
                                {
                                    puts("Vector lleno");
                                    return ERR_VEC_LLENO;
                                }
                            }
                            else
                            {
                                 ErrorParametro(Argv[i]);//iinformamos
                            }
                       }
                    else
                    {
                        if(IsThisElementAEffect(auxGral, ListToComp, cantEComp))
                        {
                            UploadValueWithoutEqual(Argv[i], &VecEffectAux);
                            if ( LoadElementsInList_NoRepit(VecEfectTDA, &VecEffectAux,
                                                                Comparing_NameVsName) == false)
                            {
                                    puts("Vector lleno");
                                    return ERR_VEC_LLENO;
                                }
                        }
                        else
                        {
                             ErrorParametro(Argv[i]);//iinformamos
                        }
                    }
                }
            else
                {
                    if(IsThereADot(auxGral)) // hay un punto?
                    {
                        if(IsThisABMPExtension(auxGral))//es una bmp?
                        {
                            strcpy(ImageAux.NameImage, Argv[i]);
                            if ( !LoadElementsInList(VecImageTDA,&ImageAux) )
                            {
                                puts("PARAMETROS .BMP ENVIADOS DEMAS");
                                return ERR_VEC_LLENO;
                            }
                        }
                        else
                            ErrorParametro(Argv[i]);//iinformamos
                    }
                    else
                    {
                        ErrorParametro(Argv[i]);
                    }
                }
        }
    }
    return TODO_OK;
}

void UploadValueWithEqual(char *aux, VecEffectList * VecEffectAux)
{
    char * PointerHelp = NULL;

    PointerHelp = strchr(aux, '=');

    sscanf(PointerHelp + 1, "%d", &VecEffectAux->ProcentajeAAgregar);

    *(PointerHelp + 1) = '\0';
    sscanf(aux, "%s", VecEffectAux->NameEffect);
}

void UploadValueWithoutEqual(char *aux, VecEffectList * VecEffectAux)
{
    sscanf(aux, "%s", VecEffectAux->NameEffect);
    VecEffectAux->ProcentajeAAgregar = 0;
}

bool IsThereADash(char* aux)
{
    char * PointerHelp = NULL;

    PointerHelp = strstr(aux, "--");
    if(!PointerHelp)
        return false;
    return true;
}
bool IsThereAnEqual(char* aux)
{
    char * PointerHelp = NULL;

    PointerHelp = strchr(aux, '=');
    if(!PointerHelp)
        return false;
    return true;
}

bool IsThisElementAEffect(char* aux, VecEffectDefault* ListToComp, int cantEComp)
{
    VecEffectDefault * pointer;
    VecEffectDefault* end = ListToComp + cantEComp;

    for(pointer = ListToComp; pointer < end ; pointer++)
    {
        if(Comparing_NameVsName(pointer, aux) == 0)
        {
                return true;
        }
    }
    return false;
}

bool IsThisElementAEffectWithEqual(char* aux, VecEffectDefault* ListToComp, int cantEComp)
{
    char * PointerHelp = NULL;
    int numero;

    PointerHelp = strchr(aux, '=');
    sscanf(PointerHelp + 1, "%d", &numero);

    *(PointerHelp + 1) = '\0';

    VecEffectDefault * pointer;
    VecEffectDefault* end = ListToComp + cantEComp;

    for(pointer = ListToComp; pointer < end ; pointer++)
    {
        if(Comparing_NameVsName(pointer, aux) == 0)
        {
            if(numero <= 100 && numero >= 0)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool IsThereADot(char* aux)
{
    char* pointer = NULL;

    pointer = strchr(aux, '.');
    if(!pointer)
        return false;

    return true;
}


bool IsThisABMPExtension(char *aux)
{
    char* pointer = NULL;

    char cadena[TamIncludingpointbmp];
    pointer = strchr(aux, '.');
    memcpy(cadena, pointer, TamIncludingpointbmp - 1);

    *(cadena + TamIncludingpointbmp - 1) = '\0';

    if (strcmp(cadena, ExtensionBmp) == 0)
        return true;

    return false;
}

int Comparing_NameVsName(const void* a, const void* b)
{
    unsigned char * Ai = (unsigned char*)a;
    unsigned char* Bi = (unsigned char*)b;

    return (strcmp((char*)Ai, (char*)Bi));
}

void RoutineMemoryArgvLiberation(TDAVectList* VecEfectTDA, TDAVectList* VecImageTDA)
{
    FreeListMemory(VecEfectTDA);
    FreeListMemory(VecImageTDA);
}

void RoutineMemoryLiberation(TDAVectList* VecEfectTDA,
                             TDAVectList* VecImageTDA , AdicDataBmp* data,Pixeles ** Matriz, int alto, int ancho)
{
    RoutineMemoryArgvLiberation(VecEfectTDA, VecImageTDA);
    EliminarmatrizDIN_Pixeles(Matriz, alto, ancho);
    VerificarYLiberarMemoriaData(data);
}


////////////////////header////////


int LoadImageInMemory(HeaderBmp * Header, AdicDataBmp * Data, FILE* Imagenbmp, Pixeles*** MatrizImagen)
{
    int resultado;

    resultado = CargarHeaderEnMemoriaYcargarData(Header,Data,Imagenbmp);
    if(resultado != 0)
    {
        if(resultado == ERR_FORMATO)
            return ERR_FORMATO;
        else
            return ERR_ASIG_MEM;
    }
    *MatrizImagen = CrearmatrizDIN_Pixel(Header->palto, Header->pancho);

    if(!(*MatrizImagen))
        return ERR_MATRIZ_CREACION;

    CargarMatrizImagen(Imagenbmp, *MatrizImagen,
                       Header->palto, Header->pancho ,Header->inicioDatos, Data->padding);
    return  TODO_OK;
}

Pixeles ** CrearmatrizDIN_Pixel(const int p_cant_f, const int p_cant_c)
{
    int i,j;
    Pixeles** matriz = (Pixeles**) malloc(p_cant_f * sizeof(Pixeles*));
    if(!matriz)
    {
        puts("ERROR EN LA PRIMER ASIGNACION DE MEMORIA DE LA MATRIZ");
        return NULL;
    }

    for(i=0; i< (p_cant_f); i++)
    {
        matriz[i] = (Pixeles*) malloc(sizeof(Pixeles) * p_cant_c);
        if(!matriz[i])
        {
            for(j=i; j>=0; j--)
            {
                free(matriz[j]);
            }
            free(matriz);
            puts("ERROR EN LA ASIGNACION DE MEMORIA DE LA MATRIZ , MEM. EXCEDIDA");
            return NULL;
        }
    }
    return matriz;
}
void EliminarmatrizDIN_Pixeles(Pixeles** matriz, const int cant_f, const int cant_c)
{
    int i;

    if(matriz != NULL)
    {
        for(i=0; i< (cant_f); i++)
        {
            free(matriz[i]);
        }
        free(matriz);
    }
}
int CargarHeaderEnMemoriaYcargarData(HeaderBmp* header, AdicDataBmp *data , FILE* imagen)
{
    if(VerificarQueEsBMP(header, imagen, TipoBmpB, TipoBmpM) != true)
        return ERR_FORMATO;

    LeerHeaderBmp(header,imagen);

    if(VerificarYAsignarMemoriaDeSerNecHEaderExtendido(header,data,imagen, TamHeaderB)!= true)
        return ERR_ASIG_MEM;

    data->padding = CalcularPadding(header->pancho);

    if(VerificarYGenerarVectorDeDatosPadding(data)!= true)
    {
        return ERR_ASIG_MEM;
    }
    return TODO_OK;

}

bool VerificarQueEsBMP(HeaderBmp* header, FILE* imagen, char Letra1, char Letra2)
{
    fread(header->bm, sizeof(unsigned char), sizeof(header->bm), imagen);
    if(header->bm[0] != Letra1 || header->bm[1] != Letra2)
    {
        puts("La imagen no es del tipo BMP");
        puts("cancelando el proceso");
        return false;
    }
    return true;
}

void LeerHeaderBmp(HeaderBmp* header, FILE* imagen)
{
    fread(&header->tamano, sizeof(unsigned char), sizeof(header->tamano), imagen);
    fread(&header->reservado1, sizeof(unsigned char), sizeof(header->reservado1), imagen);
    fread(&header->reservado2, sizeof(unsigned char), sizeof(header->reservado2), imagen);
    fread(&header->inicioDatos, sizeof(unsigned char), sizeof(header->inicioDatos), imagen);
    fread(&header->TamCabecera, sizeof(unsigned char), sizeof(header->TamCabecera), imagen);
    fread(&header->pancho, sizeof(unsigned char), sizeof(header->pancho), imagen);
    fread(&header->palto, sizeof(unsigned char), sizeof(header->palto), imagen);
    fread(&header->numeroPlanos, sizeof(unsigned char), sizeof(header->numeroPlanos), imagen);
    fread(&header->tamPuntos, sizeof(unsigned char), sizeof(header->tamPuntos), imagen);
    fread(&header->tipoCompresion, sizeof(unsigned char), sizeof(header->tipoCompresion), imagen);
    fread(&header->tamImag, sizeof(unsigned char), sizeof(header->tamImag), imagen);
    fread(&header->pxmh, sizeof(unsigned char), sizeof(header->pxmh), imagen);
    fread(&header->pxmv, sizeof(unsigned char), sizeof(header->pxmv), imagen);
    fread(&header->coloresUsados, sizeof(unsigned char), sizeof(header->coloresUsados), imagen);
    fread(&header->coloresImportantes, sizeof(unsigned char), sizeof(header->coloresImportantes), imagen);
}

bool VerificarYAsignarMemoriaDeSerNecHEaderExtendido(HeaderBmp *header, AdicDataBmp *data ,
                                                     FILE*imagen, const int tamHeader)
{
    if(header->inicioDatos > tamHeader)
    {
        data->CabeceraDIBext = (unsigned char*)calloc(header->inicioDatos - tamHeader, sizeof(unsigned char));
        if(!data->CabeceraDIBext)
        {
            puts("Error asignacion memoria");
            data->CabeceraDIBext = NULL;
            return false;
        }
        fread(data->CabeceraDIBext, header->inicioDatos - tamHeader, 1, imagen);
    }
    return true;
}

void VerificarYLiberarMemoriaData(AdicDataBmp * data)
{
    if(!data->CabeceraDIBext)
    {
        free(data->CabeceraDIBext);
    }
    if(!data->PaddingAdd)
        free(data->PaddingAdd);
}



void CargarMatrizImagen(FILE * Imagenbmp, Pixeles **MatrizImagen, const int alto,
                        const int ancho, const int offset, const int padding)
{
    int i,j;

    fseek(Imagenbmp, 1L * offset, SEEK_SET);

    for(i=0; i < alto; i ++)
    {

        for(j=0; j<ancho; j++)
        {
            fread(&MatrizImagen[i][j], sizeof(Pixeles),1, Imagenbmp);
        }
        if (padding != 0)
            fseek(Imagenbmp,padding, SEEK_CUR);
    }
}

///////////////////////////

void LoadAuxWithData(VecEffectList * auxiliar, TDAVectList * VecEffect, const int element)
{
    VecEffectList *aux = (VecEffectList*)getElementofTDAlist(VecEffect, element);

    strcpy(auxiliar->NameEffect, aux->NameEffect);
    auxiliar->ProcentajeAAgregar = aux->ProcentajeAAgregar;
}


void LoadAuxWithDataImg(VecImag *auxiliar, TDAVectList * VecImagen, const int element)
{
    VecImag *aux = (VecImag*)getElementofTDAlist(VecImagen, element);

    strcpy(auxiliar->NameImage, aux->NameImage);
}

void CrearNombreDeArchivo(char* nombre, char* Final, char* nombreImagen)
{
    char * pointer = NULL;

    strcat(Final, nombre + 2);

    if (IsThereAnEqual(Final))
    {
        pointer = strrchr(Final, '=');
        *pointer = '_';
    }
    else
    {
        pointer = strrchr(Final, '\0');
        pointer++;
        *pointer = '\0';
        pointer --;
        *pointer = '_';
    }
    strcat(Final, nombreImagen);
}

