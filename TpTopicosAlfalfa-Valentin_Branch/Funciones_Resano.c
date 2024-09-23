#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "main.h"
#include "Funciones_Resano.h"
#include "TDA_VECTOR.h"



///
typedef void(*Acciones)(Pixeles*, const float, const int);
//para el Header
void EscribirHeaderEnImagNueva(HeaderBmp *, FILE*, unsigned char *, const int);

/////////////EFECTOS
void CambiarColorDeImagen(Pixeles**, FILE*, AdicDataBmp*,
                             int const, const float,
                                const int, const int, Acciones);

void cambiarTonalidad(Pixeles*, const float, const int);
void transformarAGris (Pixeles *, const float, const int);
void aumentarContraste (Pixeles * , const float , const int);
void reducirContraste (Pixeles *, const float, const int);
bool ActualizarDatosHeaderRecorar(HeaderBmp*, AdicDataBmp *, int);
void ImpactarMarizimagenRecortar(Pixeles **, HeaderBmp * ,unsigned char * , int , FILE* );

/////////////////CODIGO

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

bool ActualizarDatosHeaderRecorar(HeaderBmp* Header, AdicDataBmp * Data, int porcentaje)
{
    Header->palto = (int)( Header->palto * ( ((float)porcentaje)/ ((float)100) ) );
    Header->pancho = (int)( Header->pancho * ( ((float)porcentaje)/ ((float)100) ) );

    Data->padding = CalcularPadding(Header->pancho);
    if (!VerificarYGenerarVectorDeDatosPadding(Data))
    {
        puts("ERROR DE ASIGNACION DE MEMORIA EN FUNCION: ActualizarDatosHeaderRecorar");
        return false;
    }
    //Recibimos una copia de header y una copia de RestoDataHeader, de lo cual usaremos
    //PaddingAdd(vector de n bytes de padding) y padding

    Header->tamImag = ((Header->palto) * (Header->pancho)) + (Data->padding * (Header->palto));
    Header->tamano = Header ->tamImag + Header->inicioDatos;
    return true;
}



void CambiarColorDeImagen(Pixeles** Matriz, FILE* imagenFinal, AdicDataBmp* PaddingInfo,
                             int const color, const float porcentaje,
                                const int alto, const int ancho, Acciones accion)
{
    int i, j;
    Pixeles  aux;

    for(i=0; i<(alto); i++)
    {
        for(j=0;j<(ancho); j++)
        {
            aux = Matriz[i][j];
            accion(&aux,porcentaje,color);
            fwrite(&aux, sizeof(Pixeles), 1, imagenFinal);
        }
        if(PaddingInfo->padding!= 0)
            fwrite(PaddingInfo->PaddingAdd, PaddingInfo->padding, 1, imagenFinal);
    }
}


bool imagenTransformada(VecEffectList * Datos, TDAVectList* vecImagen,
        Pixeles ** Matriz, AdicDataBmp * RestoDataImage ,
        HeaderBmp * Header , FILE* ImagenFinal)
{
    float valor =0;

    AdicDataBmp CopiaAdicData;
    HeaderBmp CopiaHeader;



    if (strcmp(Datos->NameEffect, "--tonalidad-azul=")==0)
    {
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        valor = (float) (((float)(Datos->ProcentajeAAgregar)/(float)100) + (float)1) ;
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage,
        BLUE, valor,
        Header->palto, Header->pancho, cambiarTonalidad);
        return true;
    }
    if (strcmp(Datos->NameEffect, "--tonalidad-verde=")==0)
    {
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        valor = (float) (((float)(Datos->ProcentajeAAgregar)/(float)100) + (float)1) ;
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage,
        GREEN, valor,
        Header->palto, Header->pancho, cambiarTonalidad);

        return true;
    }
    if (strcmp(Datos->NameEffect, "--tonalidad-roja=")==0)
    {
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        valor = (float) (((float)(Datos->ProcentajeAAgregar)/(float)100) + (float)1) ;
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage,
        RED, valor,
        Header->palto, Header->pancho, cambiarTonalidad);
        return true;
    }
    if (strcmp(Datos->NameEffect, "--escala-de-grises")==0)
    {
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage, 0, 0,
        Header->palto, Header->pancho, transformarAGris);
        return true;
    }
    if (strcmp(Datos->NameEffect, "--reducir-contraste=")==0)
    {
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        valor = (float)((float)(Datos->ProcentajeAAgregar)/(float)100);
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage, 0,valor ,
        Header->palto, Header->pancho, reducirContraste);
        return true;
    }

    if (strcmp(Datos->NameEffect, "--aumentar-contraste=")==0) {
       rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(Header, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        valor = (float) (((float)(Datos->ProcentajeAAgregar)/(float)100) + (float)1) ;
        CambiarColorDeImagen(Matriz, ImagenFinal, RestoDataImage, 0, valor,
        Header->palto, Header->pancho, aumentarContraste);
        return true;

    }

    if (strcmp(Datos->NameEffect, "--recortar=")==0)
        {

        CopiaHeader = *Header;

        CopiaAdicData.CabeceraDIBext = NULL;
        CopiaAdicData.PaddingAdd = NULL;
        CopiaAdicData.padding = 0;

        //CopiaAdicData->CabeceraDIBext esto no se usa, ya que copia el resto de datos 138-54 que
        //no difieren con la imagen original. siguen estando.

        //Copiamos las estructuras de datos ya que sino estariamos editando la iamgen original,
        //siendo que si el primer efecto es este, los siguientes trabajarian con una imagen recortada.
        if(!ActualizarDatosHeaderRecorar(&CopiaHeader, &CopiaAdicData,Datos->ProcentajeAAgregar))
        {
            puts("FUNCION RECORTAR TUVO UN ERROR EN MEMORIA, SE OMITIRA ESTA FUNCION");
            return true;
        }
        rewind(ImagenFinal);
        EscribirHeaderEnImagNueva(&CopiaHeader, ImagenFinal, RestoDataImage->CabeceraDIBext, TamHeaderB);
        ImpactarMarizimagenRecortar(Matriz,&CopiaHeader , CopiaAdicData.PaddingAdd,
                            CopiaAdicData.padding, ImagenFinal);

        free(CopiaAdicData.PaddingAdd);  //liberamos el vector padding.
        //En caso que sea null (no hay padding) la buena practica de inicializarlo como null
        //le permite al free no fallar.
        return true;
    }







    return true;
}


void ImpactarMarizimagenRecortar(Pixeles **MatrizImagen, HeaderBmp * Header,
                          unsigned char * PaddingPunt, int padding, FILE* imagenNueva)
{
    int i, j;

    for(i=0; i<(Header->palto); i++)
    {
        for(j=0;j<(Header->pancho); j++)
        {
            fwrite(&MatrizImagen[i][j], sizeof(Pixeles), 1, imagenNueva);
        }

        if(padding!= 0)
            fwrite(PaddingPunt, padding, 1, imagenNueva);
    }

}

void EscribirHeaderEnImagNueva(HeaderBmp * Header, FILE* imagen,
                                unsigned char * restoHeader, const int tamHeader)
{
    fwrite(Header->bm, sizeof(Header->bm), 1, imagen);
    fwrite(&Header->tamano,sizeof(Header->tamano),1, imagen);
    fwrite(&Header->reservado1,sizeof(Header->reservado1),1, imagen);
    fwrite(&Header->reservado2,sizeof(Header->reservado2),1, imagen);
    fwrite(&Header->inicioDatos,sizeof(Header->inicioDatos),1 , imagen);
    fwrite(&Header->TamCabecera,sizeof(Header->TamCabecera),1, imagen);
    fwrite(&Header->pancho,sizeof(Header->pancho),1, imagen);
    fwrite(&Header->palto,sizeof(Header->palto),1, imagen);
    fwrite(&Header->numeroPlanos,sizeof(Header->numeroPlanos),1, imagen);
    fwrite(&Header->tamPuntos,sizeof(Header->tamPuntos),1, imagen);
    fwrite(&Header->tipoCompresion,sizeof(Header->tipoCompresion),1, imagen);
    fwrite(&Header->tamImag,sizeof(Header->tamImag),1, imagen);
    fwrite(&Header->pxmh,sizeof(Header->pxmh),1, imagen);
    fwrite(&Header->pxmv,sizeof(Header->pxmv),1, imagen);
    fwrite(&Header->coloresUsados, sizeof(Header->coloresUsados),1, imagen);
    fwrite(&Header->coloresImportantes,sizeof(Header->coloresImportantes),1, imagen);

    if(Header->inicioDatos > tamHeader) //SIGNIFICA QUE SI ES 138 EL INICIO Y EL TAM ES 54, hay datos adicionales
    {
        fwrite(restoHeader, Header->inicioDatos - tamHeader,1, imagen);
    }
}





/*

"--espejar-horizontal"
"--espejar-vertical"
"--recortar="
"--achicar="
"--rotar-derecha"
"--rotar-izquierda"
"--concatenar-horizontal"
"--concatenar-vertical"
"--comodin"


int imagenTransformada(char* param, const int valor)
{
    int numeroColor;
    t_pixel (*nombreFuncionConUnArgumento)(t_pixel *)=NULL;
    t_pixel (*nombreFuncionConDosArgumentos)(t_pixel *, int)=NULL;
    char directorioArchivo[100];
    // L�gica para asignar la funci�n adecuada al puntero basado en el color
    if (strcmp(param, "azul")==0) {
        nombreFuncionConDosArgumentos = cambiarTonalidad;
        strcpy(directorioArchivo ,"./Ejemplos de imagenes procesadas/alumno_tonalidad-azul.bmp");
        numeroColor=BLUE;
    }
    if (strcmp(param, "verde")==0) {
        nombreFuncionConDosArgumentos = cambiarTonalidad;
        strcpy(directorioArchivo, "./Ejemplos de imagenes procesadas/alumno_tonalidad-verde.bmp");
        numeroColor=GREEN;
    }
    if (strcmp(param, "rojo")==0) {
        nombreFuncionConDosArgumentos = cambiarTonalidad;
        strcpy(directorioArchivo, "./Ejemplos de imagenes procesadas/alumno_tonalidad-roja.bmp");
        numeroColor=RED;
    }
    if (strcmp(param, "gris")==0) {
        nombreFuncionConUnArgumento = transformarAGris;
        strcpy(directorioArchivo,"./Ejemplos de imagenes procesadas/alumno_escala-de-grises.bmp");
    }
    if (strcmp(param, "negativo")==0) {
        nombreFuncionConUnArgumento = transformarANegativo;
        strcpy(directorioArchivo,"./Ejemplos de imagenes procesadas/alumno_escala-de-grises.bmp");
    }
    if (strcmp(param, "disminuirContraste")==0) {
        nombreFuncionConUnArgumento = reducirContraste;
        strcpy(directorioArchivo,"./Ejemplos de imagenes procesadas/alumno_contraste-disminuido.bmp");
    }
    if (strcmp(param, "aumentarContraste")==0) {
        nombreFuncionConUnArgumento = aumentarContraste;
        strcpy(directorioArchivo,"./Ejemplos de imagenes procesadas/alumno_contraste-aumentado.bmp");
    }

    FILE *archivoOriginal;
    FILE *archivoSaliente;
    t_metadata metadata;
    unsigned char encabezado[tamanoEncabezado];

    //Leo el archivo y asigno el header al encabezado y el alto y ancho a la metadata
    LeerArchivo(&archivoOriginal, &metadata, (unsigned char*) &encabezado);

    EscribirEncabezadoArchivoSaliente(&archivoSaliente, encabezado, directorioArchivo);

    t_pixel pixel,pixelTransformado;

    int tamano_fila_original = ((3 * metadata.ancho + 3) / 4) * 4;

    for (int i = 0; i < metadata.alto; i++) {
        for (int j = 0; j < metadata.ancho; j++) {
            fseek(archivoOriginal, 138 + i * tamano_fila_original + j * 3, SEEK_SET);
            fread(&pixel, sizeof(t_pixel), 1, archivoOriginal);
            fseek(archivoSaliente, 138 + i * tamano_fila_original + j * 3, SEEK_SET);
            if(nombreFuncionConUnArgumento)
                pixelTransformado = nombreFuncionConUnArgumento(&pixel);
            if(nombreFuncionConDosArgumentos)
                pixelTransformado = nombreFuncionConDosArgumentos(&pixel, numeroColor);
            fwrite(&pixelTransformado, sizeof(t_pixel), 1, archivoSaliente);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoSaliente);

    printf("\nImagen transformada correctamente");

    return TODO_OK;
}


int rotarDerecha()
{
    FILE *archivoOriginal = fopen("./Ejemplos de imagenes procesadas/unlam.bmp", "rb");
    FILE *archivoSaliente = fopen("./Ejemplos de imagenes procesadas/rotaalumno_rotar-derechadoDerecha.bmp", "wb");


    if (!archivoOriginal || !archivoSaliente) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    unsigned char encabezado[54];
    fread(encabezado, sizeof(unsigned char), 54, archivoOriginal);
    fwrite(encabezado, sizeof(unsigned char), 54, archivoSaliente);

    unsigned int ancho, alto;
    fseek(archivoOriginal, 18, SEEK_SET);
    fread(&ancho, sizeof(unsigned int), 1, archivoOriginal);
    fread(&alto, sizeof(unsigned int), 1, archivoOriginal);

    printf("\nAncho: %d, Alto: %d", ancho, alto);

    fseek(archivoSaliente, 18, SEEK_SET);
    fwrite(&alto, sizeof(unsigned int), 1, archivoSaliente);
    fwrite(&ancho, sizeof(unsigned int), 1, archivoSaliente);

    int tamano_fila_original = ((3 * ancho + 3) / 4) * 4;
    int tamano_fila_rotada = ((3 * alto + 3) / 4) * 4;

    printf("\nTamano fila original: %d", tamano_fila_original);
    printf("\nTamano fila rotada: %d", tamano_fila_rotada);

    t_pixel pixel;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fseek(archivoOriginal, 138 + i * tamano_fila_original + j * 3, SEEK_SET);
            fread(&pixel, sizeof(t_pixel), 1, archivoOriginal);

            fseek(archivoSaliente, 138 + (ancho - j - 1) * tamano_fila_rotada + i * 3, SEEK_SET);

            fwrite(&pixel, sizeof(t_pixel), 1, archivoSaliente);

        }
    }

    fclose(archivoOriginal);
    fclose(archivoSaliente);

    printf("\nImagen rotada a la derecha 90�");

    return TODO_OK;
}

int rotarIzquierda()
{
    FILE *archivoOriginal = fopen("./Ejemplos de imagenes procesadas/unlam.bmp", "rb");
    FILE *archivoSaliente = fopen("./Ejemplos de imagenes procesadas/alumno_rotar-izquierda.bmp", "wb");

    if (!archivoOriginal || !archivoSaliente) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    unsigned char encabezado[54];
    fread(encabezado, sizeof(unsigned char), 54, archivoOriginal);
    fwrite(encabezado, sizeof(unsigned char), 54, archivoSaliente);

    unsigned int ancho, alto;
    fseek(archivoOriginal, 18, SEEK_SET);
    fread(&ancho, sizeof(unsigned int), 1, archivoOriginal);
    fread(&alto, sizeof(unsigned int), 1, archivoOriginal);

    printf("\nAncho: %d, Alto: %d", ancho, alto);

    // Escribimos el nuevo ancho y alto en la nueva imagen
    fseek(archivoSaliente, 18, SEEK_SET);
    fwrite(&alto, sizeof(unsigned int), 1, archivoSaliente);
    fwrite(&ancho, sizeof(unsigned int), 1, archivoSaliente);

    int tamano_fila_original = ((3 * ancho + 3) / 4) * 4;
    int tamano_fila_rotada = ((3 * alto + 3) / 4) * 4;


    t_pixel pixel;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            fseek(archivoOriginal, 138 + i * tamano_fila_original + j * 3, SEEK_SET);
            fread(&pixel, sizeof(t_pixel), 1, archivoOriginal);

            fseek(archivoSaliente, 138 + j * tamano_fila_rotada + (alto - i - 1) * 3, SEEK_SET);
            fwrite(&pixel, sizeof(t_pixel), 1, archivoSaliente);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoSaliente);

    printf("\nImagen rotada a la izquierda 90�");

    return TODO_OK;
}

int recortarMitad()
{
    FILE *archivoOriginal = fopen("./Ejemplos de imagenes procesadas/unlam.bmp", "rb");
    FILE *archivoSaliente = fopen("./Ejemplos de imagenes procesadas/alumno_recortado-mitad.bmp", "wb");

    if (!archivoOriginal || !archivoSaliente) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    unsigned char encabezado[54];
    fread(encabezado, sizeof(unsigned char), 54, archivoOriginal);
    fwrite(encabezado, sizeof(unsigned char), 54, archivoSaliente);

    unsigned int ancho, alto;
    fseek(archivoOriginal, 18, SEEK_SET);
    fread(&ancho, sizeof(unsigned int), 1, archivoOriginal);
    fread(&alto, sizeof(unsigned int), 1, archivoOriginal);

    int nuevo_ancho = ancho / 2;
    int nuevo_alto = alto;

    fseek(archivoSaliente, 18, SEEK_SET);
    fwrite(&nuevo_ancho, sizeof(int), 1, archivoSaliente);
    fwrite(&nuevo_alto, sizeof(int), 1, archivoSaliente);

    int tamano_fila_original = ((3 * ancho + 3) / 4) * 4;
    int tamano_fila_recortada = ((3 * nuevo_ancho + 3) / 4) * 4;

    printf("\nAncho original: %d, Alto original: %d", ancho, alto);
    printf("\nNuevo ancho: %d, Nuevo alto: %d", nuevo_ancho, nuevo_alto);

    t_pixel pixel;

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho / 2; j++) {
            fseek(archivoOriginal, 138 + i * tamano_fila_original + j * 3, SEEK_SET);
            fread(&pixel, sizeof(t_pixel), 1, archivoOriginal);

            fseek(archivoSaliente, 138 + i * tamano_fila_recortada + j * 3, SEEK_SET);
            fwrite(&pixel, sizeof(t_pixel), 1, archivoSaliente);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoSaliente);

    printf("\nImagen recortada por la mitad en el ancho correctamente");

    return TODO_OK;
}

int recortar()
{
    FILE *archivoOriginal = fopen("./Ejemplos de imagenes procesadas/unlam.bmp", "rb");
    FILE *archivoSaliente = fopen("./Ejemplos de imagenes procesadas/alumno_recortado.bmp", "wb");

 if (!archivoOriginal || !archivoSaliente) {
        printf("Error al abrir los archivos.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    unsigned char encabezado[54];
    fread(encabezado, sizeof(unsigned char), 54, archivoOriginal);
    fwrite(encabezado, sizeof(unsigned char), 54, archivoSaliente);

    unsigned int ancho, alto;
    fseek(archivoOriginal, 18, SEEK_SET);
    fread(&ancho, sizeof(unsigned int), 1, archivoOriginal);
    fread(&alto, sizeof(unsigned int), 1, archivoOriginal);

    int nuevo_ancho = ancho / 2;
    int nuevo_alto = alto / 2;

    fseek(archivoSaliente, 18, SEEK_SET);
    fwrite(&nuevo_ancho, sizeof(int), 1, archivoSaliente);
    fwrite(&nuevo_alto, sizeof(int), 1, archivoSaliente);

    int tamano_fila_original = ((3 * ancho + 3) / 4) * 4;

    fseek(archivoSaliente, 138, SEEK_SET);

        for (int i = 0; i < alto / 2; i++) {
        fseek(archivoOriginal, 138 + i * tamano_fila_original, SEEK_SET);

        for (int j = 0; j < ancho / 2; j++) {
            t_pixel pixel;
            fread(&pixel, sizeof(t_pixel), 1, archivoOriginal);
            fwrite(&pixel, sizeof(t_pixel), 1, archivoSaliente);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoSaliente);

    printf("\nImagen recortada correctamente...");

    return TODO_OK;
}

int solucion(int argc, char* argv[])
{

    Aqu� deben hacer el c�digo que solucione lo solicitado.
    Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h

  int resultado;

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--rotar-izquierda") == 0) {
                resultado = rotarIzquierda();
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--rotar-derecha") == 0) {
                resultado = rotarDerecha();
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--recortar") == 0) {
                resultado = recortar();
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--tonalidad-azul") == 0) {
                resultado = imagenTransformada("azul");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--tonalidad-verde") == 0) {
                resultado = imagenTransformada("verde");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--tonalidad-roja") == 0) {
                resultado = imagenTransformada("rojo");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--escala-de-grises") == 0) {
                resultado = imagenTransformada("gris");
                if (resultado != TODO_OK) {
                    break;
                }
            }
             else if (strcmp(argv[i], "--negativo") == 0) {
                resultado = imagenTransformada("negativo");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--aumentar-contraste") == 0) {
                resultado = imagenTransformada("aumentarContraste");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--reducir-contraste") == 0) {
                resultado = imagenTransformada("disminuirContraste");
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else if (strcmp(argv[i], "--comodin") == 0) {
                resultado = recortarMitad();
                if (resultado != TODO_OK) {
                    break;
                }
            }
            else {
                printf("\nArgumento no valido: %s\n", argv[i]);
                resultado = ERROR_ARGUMENTO;
                break;
            }
        }


    return resultado;
}
*/
