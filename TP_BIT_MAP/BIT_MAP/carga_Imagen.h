#ifndef funciones_massa_H_INCLUDED
#define funciones_massa_H_INCLUDED

#include <stdbool.h>
//errores
#define TODO_OK 0
#define ERR_APERTURA -1
#define ERR_MATRIZ_CREACION -2
#define ERR_FORMATO -3
#define ERR_ASIG_MEM -4
#define ERR_VEC_LLENO -5
#define ERR_ARG_NULL -6
#define ERR_ARG_EMPTY -7
#define ERR_WITHOUT_IMAGE -8
#define ERR_WITHOUT_EFFECT -9


//MAIN
//DEFINES
//con respecto a bmp
#define TipoBmpB 'B'
#define TipoBmpM 'M'
#define SizeTipoBmp 2
#define TamHeaderB 54
#define ExtensionBmp ".bmp"
#define TamIncludingpointbmp 5

//demas
#define TamMaxVecEffectDefault 15
#define MaxImages 2
#define AperturaBin "rb"
#define NuevoArchExtBin "wb"

//tamanios
#define maxTamImage 100
#define maxTamEffect 24 //"--concatenar-horizontal", con un tama�o de 24 bytes (incluyendo el terminador nulo)


////ARGV

typedef struct
{
    char NameEffect[maxTamEffect];
}VecEffectDefault;

typedef struct
{
   char NameImage[maxTamImage];
}VecImag;

typedef struct
{
   char NameEffect[maxTamEffect];
   int ProcentajeAAgregar;
}VecEffectList;

//IMAGENES
//
typedef struct
    {
        unsigned char bm[2]; //(2 Bytes) BM (Tipo de archivo)
        unsigned int tamano; //(4 Bytes) Tama�o del archivo en bytes
        unsigned short reservado1; //(4 Bytes) Reservado
        unsigned short reservado2;
        unsigned int inicioDatos; //(4 Bytes) offset, distancia en bytes entre la img y los p�xeles
        unsigned int TamCabecera;//(4 Bytes) Tama�o de Metadatos (tama�o de esta estructura = 40)
        unsigned int pancho; //(4 Bytes) Alto (numero de pixeles verticales)
        unsigned int palto; //(4 Bytes) Ancho (numero de p�xeles horizontales)
        unsigned short numeroPlanos; //(2 Bytes) Numero de planos de color
        unsigned short tamPuntos;//(2 Bytes) Profundidad de color (debe ser 24 para nuestro caso)
        unsigned int tipoCompresion;//(4 Bytes)
        unsigned int tamImag;//(4 Bytes) Tama�o de la estructura Imagen (Paleta)
        unsigned int pxmh; //(4 Bytes) P�xeles por metro horizontal
        unsigned int pxmv; //(4 Bytes) P�xeles por metro vertical
        unsigned int coloresUsados;//(4 Bytes) Cantidad de colores usados
        unsigned int coloresImportantes; //(4 Bytes) Cantidad de colores importantes
    }HeaderBmp;

typedef struct
{
    unsigned int padding;
    unsigned char * CabeceraDIBext; // puntero al resto de datos de la cabecera extendida
    unsigned char * PaddingAdd; //puntero a un array de n bits(inicializado en cero(negro) para el padding
}AdicDataBmp; //aca tenemos datos adicionales de la bmp, como el padding,
                //el puntero a su vector de padding y al de datos restante

typedef struct
{
    unsigned char pixel[3];
}Pixeles;


typedef struct
{
    void* vec;
    int ce;
    int maxElem;
    size_t sizeE;
}TDAVectList;

//definiciones

typedef int(*Cmp)(const void*,const void*);
//typedef bool(*action)(TDAVectList*, void*);

void initializesListStructToDefault(TDAVectList *);
bool CreateTdaVectorList(size_t, size_t, TDAVectList*);
bool LoadElementsInList_NoRepit(TDAVectList*, void*, Cmp);
bool LoadElementsInList(TDAVectList*, void*);
void FreeListMemory(TDAVectList *);
void* getElementofTDAlist(TDAVectList *, int);
int getMAxElementOfTda(TDAVectList *);
int getCeOfTda(TDAVectList *);
int getSizeOfTda(TDAVectList *);
//ARGV

int ResultOfArgvOperations(char* [], int , TDAVectList*, TDAVectList*,VecEffectDefault* , int);


void RoutineMemoryLiberation(TDAVectList*, TDAVectList* ,AdicDataBmp*, Pixeles **, int, int);
////

//general
int LoadImageInMemory(HeaderBmp *,AdicDataBmp *, FILE*, Pixeles***);

//

void GenerarNuevaImagen(Pixeles **, HeaderBmp * , AdicDataBmp* , FILE*);
//liberar memoria de struct DATA
void VerificarYLiberarMemoriaData(AdicDataBmp *data);

//funciones

void CargarVectorOperaciones(VecEffectDefault*);
FILE* AbrirImagen(char*, char*);
void EliminarmatrizDIN_Pixeles(Pixeles**, const int, const int);
///////////

void LoadAuxWithData(VecEffectList *, TDAVectList *, const int);
void LoadAuxWithDataImg(VecImag *, TDAVectList *, const int);
void CrearNombreDeArchivo(char*, char*, char*);
Pixeles** CrearmatrizDIN_Pixel(const int, const int);


//FUNCIONES DE AYUDA GENERAL
int CalcularPadding(int);
bool VerificarYGenerarVectorDeDatosPadding(AdicDataBmp *);

#endif // funciones_massa_H_INCLUDED
