#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FUNCNES_DESARROLLO_MASSA.h"

//////////////
#include <math.h>
#define pi 3.14159

float aRadianes(float grados) {
    return grados/180 * pi;
}
float calcularDistancia(float lat1, float long1, float lat2, float long2) {
    double dist;
    dist = sin(aRadianes(lat1)) * sin(aRadianes(lat2)) + cos(aRadianes(lat1)) * cos(aRadianes(lat2)) * cos(aRadianes(long1 - long2));
    dist = acos(dist);
    dist = 6371 * dist;
    return dist;
}
//////////////////////



int CompararPos(const void* dato1, const void* dato2);
int CompararRegistrosASCNombrePos(const void* reg1, const void* reg2);
int CompararRegistrosASCNombreFinal(const void* reg1, const void* reg2);

void ActualizarRegistro(void* dato1, const void* dato2);

void TrozarLineaPos(char* buffer, void* dato);

int MergearDosTxt(char* NPosA, char* NposB, char* NposAB);
void ImprimirPosEnTxr(FILE* Farch, void* dato);
int MergeGenerico(FILE* FarchA, FILE* FarchB, FILE*  FarchAB, size_t tam, Trozar TrozarLinea, Cmp comparar, Imprimir ImprimirEnarch);


int RedimensionarTDA(TdaVec * vec);
int CrearVectorTDA(TdaVec * vec, size_t tamData);
void DestruirTDA(TdaVec* vec);
int CargarTDAOrdSinDup(TdaVec * vec, void* dato, Cmp cmp1, Cmp cmp2, Accion actualizar, Accion inicializar);
int CargarElementoEnTDAord(TdaVec *vec, void *dato, Cmp cmp, Accion inicializar);
void* BuscarElementoEnTDA(TdaVec *vec, void* dato, Cmp cmp);
void* DevolverPosIdeTDA(TdaVec * vec, int i);
void MostrarTDA(TdaVec * vec, Mostrar muestra);


void CrearvectorIt(TdaVec * vec, VecIt * vecIt);
void* VectorItSiguiene(VecIt *vec);

void MostrarPunto1(void* dato);
void MostrarPunto2(void* dato);
void ObtenerPromYMostrar(TdaVec * vec);
int OperarArchivoPosiciones(TdaVec * vec, char* NposAB);
void InicializarRegistro(void* dato1, const void* dato2);

int SolucionEjercicio(char* NPosA, char* NposB, char* NposAB)
{
    TdaVec vec;

    if(!MergearDosTxt(NPosA, NposB, NposAB ))
        return 0;

    CrearVectorTDA(&vec, sizeof(RegistrosFinal));

    OperarArchivoPosiciones(&vec, NposAB);

    DestruirTDA(&vec);

    return 1;
}

int MergearDosTxt(char* NPosA, char* NposB, char* NposAB)
{
    FILE* FarchA, *FarchB, *FarchAB;

    FarchA = fopen(NPosA, "rt");
    FarchB = fopen(NposB, "rt");
    FarchAB = fopen(NposAB, "wt");
    if(!FarchA || !FarchB || !FarchAB)
    {
        fclose(FarchA);
        fclose(FarchB);
        fclose(FarchAB);
        return 0;
    }

    if(!MergeGenerico(FarchA, FarchB, FarchAB, sizeof(RegistrosPos), TrozarLineaPos, CompararPos, ImprimirPosEnTxr))
       {
            fclose(FarchA);
            fclose(FarchB);
            fclose(FarchAB);
            return 0;
       }
    return 1;
}

int OperarArchivoPosiciones(TdaVec * vec, char* NposAB)
{
    RegistrosPos reg;
    char* aux;
    char buffer[TAM_BUFFER];

    FILE*FarchAB = fopen(NposAB, "rt");
    if(!FarchAB)
        return 0;

    while( (aux = fgets(buffer, TAM_BUFFER, FarchAB)) != NULL)
    {
        TrozarLineaPos(buffer, &reg);
        CargarTDAOrdSinDup(vec, &reg, CompararRegistrosASCNombreFinal , CompararRegistrosASCNombrePos, ActualizarRegistro, InicializarRegistro);
    }
    fclose(FarchAB);

    puts("Punto 1");
    MostrarTDA(vec, MostrarPunto1);
    puts("Punto 2");
    MostrarTDA(vec, MostrarPunto2);
    puts("Punto 3");
    ObtenerPromYMostrar(vec);

    return 0;
}

void ObtenerPromYMostrar(TdaVec * vec)
{
    void* aux;
    VecIt vecHelp;
    float promedio =0;
    RegistrosFinal* reg;

    CrearvectorIt(vec, &vecHelp);


    while( (aux = VectorItSiguiene(&vecHelp)) != NULL)
    {
            reg = (RegistrosFinal*)aux;
            promedio += reg->cont;
    }
    printf("promedio km recorrido: %lf km \n", promedio/vec->ce);

}

void* DevolverPosIdeTDA(TdaVec * vec, int i)
{
    if(i< 0 || i >= vec->ce )
        return NULL;
    return (vec->vec + (vec->tamDato * i));
}

void MostrarTDA(TdaVec * vec, Mostrar muestra)
{
    void* aux;
    VecIt vecHelp;
    CrearvectorIt(vec, &vecHelp);

    while( (aux = VectorItSiguiene(&vecHelp)) != NULL)
    {
            muestra(aux);
    }
}

void MostrarPunto1(void* dato)
{
    RegistrosFinal * aux = (RegistrosFinal*)dato;

    printf("ID: %-10s !! TotalKm: %-.06lf km\n", aux->id, aux->cont);
}
void MostrarPunto2(void* dato)
{
    RegistrosFinal * aux = (RegistrosFinal*)dato;

    printf("ID: %-10s !! MinimolKm: %-.06lf km\n", aux->id, aux->minima);
}



void ActualizarRegistro(void* dato1, const void* dato2)
{
    RegistrosFinal * regFinal = (RegistrosFinal*) dato1;
    RegistrosPos *reg = (RegistrosPos*) dato2;

    float resultado = calcularDistancia(regFinal->lat, regFinal->longitud, reg->lat, reg->long_);

    regFinal->lat = reg->lat;
    regFinal->longitud = reg->long_;
    regFinal->cont += (double)resultado;

    if(resultado < regFinal->minima)
        regFinal->minima = resultado;
}


int CrearVectorTDA(TdaVec * vec, size_t tamData)
{
    void * punt = malloc(tamData * TamMax);
    if(!punt)
        return 0;

    vec->tamDato = tamData;
    vec->vec = punt;
    vec->ce = 0;
    vec->factorIncr = FactorIncremento;
    vec->tamMax = TamMax;
    return 1;
}

void DestruirTDA(TdaVec* vec)
{
    free(vec->vec);
    vec->ce = 0;
    vec->factorIncr = 0;
    vec->tamMax = 0;
    vec->tamDato = 0;
}

int CargarTDAOrdSinDup(TdaVec * vec, void* dato, Cmp cmp1, Cmp cmp2, Accion actualizar, Accion inicializar)
{
    if(vec->ce == vec->tamMax)
    {
        if(!RedimensionarTDA(vec))
            return 0;
    }

    void* pos = BuscarElementoEnTDA(vec, dato, cmp2);

    if(!pos)
    {
        CargarElementoEnTDAord(vec, dato, cmp1, inicializar);
        return 1;
    }
    actualizar(pos, dato);
    return 1;
}

int CargarElementoEnTDAord(TdaVec *vec, void *dato, Cmp cmp, Accion inicializar)
{
    void* aux;
    void* datoFinal = malloc(vec->tamDato);
    if(!datoFinal)
        return 0;

    inicializar(datoFinal, dato);

    if(vec->ce == 0)
    {
        memcpy(vec->vec+(vec->ce * vec->tamDato), datoFinal, vec->tamDato);
        vec->ce ++;
        free(datoFinal);
        return 1;
    }

    int resultado;
    VecIt vecHelp;
    CrearvectorIt(vec, &vecHelp);

    while( (aux = VectorItSiguiene(&vecHelp)) != NULL)
    {
        resultado = cmp(aux, datoFinal);
        if(resultado > 0)
        {
            memmove(aux + vec->tamDato, aux, (vec->vec + (vec->ce * vec->tamDato)) - aux);
            memcpy(aux, datoFinal, vec->tamDato);
            vec->ce ++;
            free(datoFinal);
            return 1;
        }
    }

    memcpy(vec->vec+(vec->ce * vec->tamDato), datoFinal, vec->tamDato);
    vec->ce ++;
    free(datoFinal);
    return 1;
}

void InicializarRegistro(void* reg1, const void* reg2)
{
    RegistrosFinal * aux1 = (RegistrosFinal*) reg1;
    RegistrosPos * aux2 = (RegistrosPos*) reg2;

    aux1->cont = 0;
    strcpy(aux1->id, aux2->id);
    aux1->lat = aux2->lat;
    aux1->longitud = aux2->long_;
    aux1->minima = 1000000;

}

void* BuscarElementoEnTDA(TdaVec *vec, void* dato, Cmp cmp)
{
    VecIt vecIthelp;
    CrearvectorIt(vec, &vecIthelp);
    void* aux;
    while( (aux = VectorItSiguiene(&vecIthelp)) != NULL)
    {
        if(cmp(aux, dato) == 0)
            return aux;
    }
    return NULL;
}


int CompararRegistrosASCNombreFinal(const void* reg1, const void* reg2)
{
    RegistrosFinal * aux1 = (RegistrosFinal*) reg1;
    RegistrosFinal * aux2 = (RegistrosFinal*) reg2;
    return(strcmp(aux1->id, aux2->id));
}

int CompararRegistrosASCNombrePos(const void* reg1, const void* reg2)
{
    RegistrosFinal * aux1 = (RegistrosFinal*) reg1;
    RegistrosPos * aux2 = (RegistrosPos*) reg2;
    return(strcmp(aux1->id, aux2->id));
}

int RedimensionarTDA(TdaVec * vec)
{
    int NuevaCantMax = vec->tamMax + (int)((float)vec->tamMax * vec->factorIncr);

    void* aux = realloc(vec->vec, NuevaCantMax * vec->tamDato);
    if(!aux)
        return 0;

    vec->vec = aux;
    vec->tamMax = NuevaCantMax;
    return 0;
}

void CrearvectorIt(TdaVec * vec, VecIt * vecIt)
{
    vecIt->vec = vec;
    vecIt->act = vec->vec;
    vecIt->fin = vec->vec + (vec->ce * vec->tamDato);
    vecIt->tamDato = vec->tamDato;
}

void* VectorItSiguiene(VecIt* vec)
{
    if(vec->act == vec->fin)
        return NULL;

    void* aux = vec->act;
    vec->act += vec->tamDato;
    return aux;
}

int MergeGenerico(FILE* FarchA, FILE* FarchB, FILE*  FarchAB, size_t tam, Trozar TrozarLinea, Cmp comparar, Imprimir ImprimirEnarch)
{
    void* dato1 = malloc(tam);
    if(!dato1)
        return 0;
    void* dato2 = malloc(tam);
    if(!dato2)
        return 0;

    char *punt1,*punt2;
    char buffer1[TAM_BUFFER], buffer2[TAM_BUFFER];
    int resultado;

    punt1 = fgets(buffer1, TAM_BUFFER, FarchA);
    punt2 = fgets(buffer2, TAM_BUFFER, FarchB);
    if(!punt1 || !punt2 )
    {
        free(dato1);
        free(dato2);
        return 0;
    }

    TrozarLinea(buffer1, dato1);
    TrozarLinea(buffer2, dato2);

    while(punt1 && punt2 )
    {
        resultado = comparar(dato1, dato2);

        if(resultado>0) //escribir B
        {
            ImprimirEnarch(FarchAB, dato2);
            punt2 = fgets(buffer2, TAM_BUFFER, FarchB);
            if(punt2)
                TrozarLinea(buffer2, dato2);
        }
        if(resultado<0)// escribir A
        {
            ImprimirEnarch(FarchAB, dato1);
            punt1 = fgets(buffer1, TAM_BUFFER, FarchA);
            if(punt1)
                TrozarLinea(buffer1, dato1);
        }
        if(resultado == 0 ) //primero A desp B
        {
                ImprimirEnarch(FarchAB, dato1);
                ImprimirEnarch(FarchAB, dato2);
                punt1 = fgets(buffer1, TAM_BUFFER, FarchA);
                punt2 = fgets(buffer2, TAM_BUFFER, FarchB);
                if(punt1)
                    TrozarLinea(buffer1, dato1);
                if(punt2)
                    TrozarLinea(buffer2, dato2);
        }
    }
    while(punt1)
    {
        ImprimirEnarch(FarchAB, dato1);
        punt1 = fgets(buffer1, TAM_BUFFER, FarchA);
        if(punt1)
            TrozarLinea(buffer1, dato1);
    }
    while(punt2)
    {
        ImprimirEnarch(FarchAB, dato2);
        punt2 = fgets(buffer2, TAM_BUFFER, FarchB);
        if(punt2)
            TrozarLinea(buffer2, dato2);
    }

    fclose(FarchA);
    fclose(FarchB);
    fclose(FarchAB);
    free(dato1);
    free(dato2);

    return 1;
}

int CompararPos(const void* dato1, const void* dato2)
{
    RegistrosPos * aux1 = (RegistrosPos*) dato1;
    RegistrosPos * aux2 = (RegistrosPos*) dato2;
    return ((int)(aux1->fecha - aux2->fecha));
}

void TrozarLineaPos(char* buffer, void* dato)
{
    RegistrosPos * aux = (RegistrosPos*) dato;
    char* puntero;

    puntero = strrchr(buffer, '\n');
    *puntero = '\0';

    puntero = strrchr(buffer, ',');
    sscanf(puntero + 1, "%lf", &aux->long_);
    *puntero = '\0';

    puntero = strrchr(buffer, ',');
    sscanf(puntero + 1, "%lf", &aux->lat);
    *puntero = '\0';

    puntero = strrchr(buffer, ',');
    sscanf(puntero + 1, "%s", aux->id);
    *puntero = '\0';

    sscanf(buffer, "%lf", &aux->fecha);
}

void ImprimirPosEnTxr(FILE* Farch, void* dato)
{
    RegistrosPos * aux = (RegistrosPos*) dato;
    fprintf(Farch,"%lf,%s,%lf,%lf\n",aux->fecha, aux->id, aux->lat, aux->long_);
}


//calcularDistancia()

