#include "SOLUCION.h"

#define EsEspacio(a)(a == ' '?1:0)

typedef struct
{
    void** matriz;
    int filas;
    int CeFilas;
    size_t tamElem;
    int columnas;

    int maxFilas;
    float factorIncr;
}
Matriz;

typedef struct
{
    int fila1;
    int fila2;
}
IdxM;

typedef struct
{
    void* vec;
    int ce;
    int MaxTam;
    float FactorInc;
    size_t Tamdata;
}
TDAvec;

typedef struct
{
    TDAvec * TdaVec;
    void* act;
    void* fin;
    size_t tamData;
}
VectorIt;

typedef void(*Mostrar)(const void*);
typedef void(*ImprimirEnTxt)(const void*, FILE*);
typedef int(*Trozar)(char* buffer, void*dato);

void MostrarmatrizFloat(const void* dato);
void MostrarElementoIndice(const void* dato);

void ImprimirEnTxtMatrizFloat(const void* dato, FILE* farch);

int trozarLineaIdx(char* buffer,  void* aux);


void MostrarMatriz(Matriz *mat, Mostrar muestra);
void InicializarMatriz(Matriz* mat,void** matriz,int filas,int columnas,int CeFilas,size_t tamElem);
int CrearMatrizDinamica(Matriz* mat, size_t Tamelem, int Filas, int columnas);
int CargarValorEnFilaNColJ(Matriz * mat,int filaN, int ColJ, void* elem);
int RedimencionarMatriz(Matriz* mat);
int ObtenermaxCol(Matriz* mat);
int AumentarFila(Matriz* mat);
void DestruirMatriz(Matriz * mat);
void* ObtenerDatoFilaNcolumnaJMatriz(Matriz* mat, int fila, int col);
void PermutarDatos(void* dato1, void* dato2, size_t tam);
int CrearTxtConMatriz(Matriz* mat, char* Fname, ImprimirEnTxt impresion);


int CrearTDA(TDAvec * vec, size_t tam);
int CargarTDAdesdeTxt(char*, TDAvec*, Trozar);
void* UltimaPosVaciaEnVecTDA(TDAvec* vec);
int CargarElementoEnTDA(TDAvec* vec, void* aux);
void MostrarTDA(TDAvec * vec, Mostrar muestra);
int RedimensionarTDA(TDAvec * vec);
void DestruirTDA(TDAvec *vec);


void InicializarVecIt(TDAvec* vec, VectorIt* vecIt);
void* ProximoElementoVecIt(VectorIt* vecIt);
void InicializarVecItSentidoContrario(TDAvec* vec, VectorIt* vecIt);
void* ProximoElementoVecSentidoContrarioIt(VectorIt* vecIt);
int PermutarUnregistroDeFilaDeMismaColumnmaMatriz(Matriz *DatosMatriz, int columna, void* aux);

int CargarMatrizDinamicaConArchivoTxt(Matriz * mat, FILE* FarchPerm);
int TrozaryGuardarLinea(char* buffer, int fila, Matriz * mat);
int DesenfuscarTDA_ALU(Matriz * DatosMatriz, TDAvec* vecIdx, int columna);


int restaurarColumnaALU(char *TABLAPERMUTADA, char* TABLARESTAURADA, int NUMEROCAMPO)
{
    Matriz DatosMatriz;
    TDAvec vecIdx;

    DatosMatriz.maxFilas = MaxFilas;
    DatosMatriz.factorIncr = FactorIncremento;

    FILE* FarchPerm = fopen(TABLAPERMUTADA, "rt");

    if(!FarchPerm)
    {
        return ERR;
    }

    CrearMatrizDinamica(&DatosMatriz, sizeof(float), Filasmin, ColMax);
    CargarMatrizDinamicaConArchivoTxt(&DatosMatriz, FarchPerm);
    fclose(FarchPerm);
    MostrarMatriz(&DatosMatriz, MostrarmatrizFloat);


    CrearTDA(&vecIdx, sizeof(IdxM));
    CargarTDAdesdeTxt(PermIdx, &vecIdx, trozarLineaIdx);
    MostrarTDA(&vecIdx, MostrarElementoIndice);

    DesenfuscarTDA_ALU(&DatosMatriz, &vecIdx, NUMEROCAMPO);

    puts("Matriz despues de desenfuscar:");
    MostrarMatriz(&DatosMatriz, MostrarmatrizFloat);
    DestruirTDA(&vecIdx);

    CrearTxtConMatriz(&DatosMatriz, TABLARESTAURADA, ImprimirEnTxtMatrizFloat);


    DestruirMatriz(&DatosMatriz);


    return OK;

}

int CrearTxtConMatriz(Matriz* mat, char* Fname, ImprimirEnTxt impresion)
{
    void* aux;
    FILE* FarchRestaurada = fopen (Fname, "wt");
    int i, j;

    for(i = 0; i< mat->CeFilas; i++)
    {

        for(j=0; j < mat->columnas; j++)
        {
            if( (aux = ObtenerDatoFilaNcolumnaJMatriz(mat, i, j)) == NULL)
            {
                fclose(FarchRestaurada);
                return ERR;
            }
            impresion(aux, FarchRestaurada);
        }
        fseek(FarchRestaurada, -1L, SEEK_CUR);
        fprintf(FarchRestaurada, "\n");
    }
    fclose(FarchRestaurada);
    return OK;

}

void ImprimirEnTxtMatrizFloat(const void* dato, FILE* farch)
{
    float*aux = (float*)dato;

    if(*aux != 0)
        fprintf(farch, "%.2f|", *aux);
}

int DesenfuscarTDA_ALU(Matriz * DatosMatriz, TDAvec* vecIdx, int columna)
{
    VectorIt vecIt;
    InicializarVecItSentidoContrario(vecIdx,&vecIt);
    void* aux;


    while( (aux = ProximoElementoVecSentidoContrarioIt(&vecIt)) != NULL )
    {
        if(!PermutarUnregistroDeFilaDeMismaColumnmaMatriz(DatosMatriz, columna, aux))
            return ERR;
    }
    return OK;
}


int PermutarUnregistroDeFilaDeMismaColumnmaMatriz(Matriz *DatosMatriz, int columna, void* aux)
{
    IdxM * indice = (IdxM*) aux;
    void* dato1, *dato2;


    dato1 = ObtenerDatoFilaNcolumnaJMatriz(DatosMatriz, indice->fila1, columna);
    dato2 = ObtenerDatoFilaNcolumnaJMatriz(DatosMatriz, indice->fila2, columna);
    if(!dato1 || !dato2)
        return ERR;
    PermutarDatos(dato1, dato2, DatosMatriz->tamElem);

    return OK;
}

void* ObtenerDatoFilaNcolumnaJMatriz(Matriz* mat, int fila, int col)
{
    if(fila < 0 || col< 0)
        return NULL;
    if(fila >= mat->CeFilas || col >= mat->columnas)
        return ERR;

    return ( *(mat->matriz + fila) + (col * mat->tamElem));

}

void PermutarDatos(void* dato1, void* dato2, size_t tam)
{
    void* aux = malloc(tam);

    memcpy(aux, dato1, tam);
    memcpy(dato1, dato2, tam);
    memcpy(dato2, aux, tam);

    free(aux);

}

int CargarTDAdesdeTxt(char* Nperm, TDAvec* vec, Trozar trozarLinea)
{
    char buffer[Tambuffer];

    FILE* FarchPermIdx = fopen(Nperm, "rt");
    if(!FarchPermIdx)
        return ERR;

    void* aux = malloc(vec->Tamdata);

    while( fgets(buffer, Tambuffer, FarchPermIdx)!= NULL )
    {
        if(!trozarLinea(buffer,  aux))
            return ERR;

        if(!CargarElementoEnTDA(vec, aux))
            return ERR;
    }

    free(aux);
    fclose(FarchPermIdx);
    return OK;
}

void DestruirTDA(TDAvec *vec)
 {
     free(vec->vec);
 }

void MostrarTDA(TDAvec * vec, Mostrar muestra)
{
    VectorIt vecIt;
    void* aux;

    InicializarVecIt(vec, &vecIt);
    puts("Vector TDA");
    while( (aux = ProximoElementoVecIt(&vecIt)) != NULL )
    {
        muestra(aux);
    }
}

void InicializarVecIt(TDAvec* vec, VectorIt* vecIt)
{
    vecIt->act = vec->vec;
    vecIt->TdaVec = vec;
    vecIt->tamData = vec->Tamdata;
    vecIt->fin = vec->vec + (vec->Tamdata * vec->ce);
}

void InicializarVecItSentidoContrario(TDAvec* vec, VectorIt* vecIt)
{
    vecIt->act = vec->vec + (vec->Tamdata * (vec->ce - 1));
    vecIt->TdaVec = vec;
    vecIt->tamData = vec->Tamdata;
    vecIt->fin = vec->vec;
}

void* ProximoElementoVecSentidoContrarioIt(VectorIt* vecIt)
{
    void* aux = vecIt->act;

    if(vecIt->act < vecIt->fin)
    {
        return NULL;
    }
    vecIt->act -= vecIt->tamData;

    return aux;

}

void* ProximoElementoVecIt(VectorIt* vecIt)
{
    void* aux = vecIt->act;

    if(vecIt->act == vecIt->fin)
    {
        return NULL;
    }
    vecIt->act += vecIt->tamData;

    return aux;

}
int trozarLineaIdx(char* buffer,  void* aux)
{
    IdxM * indice = (IdxM *)aux;
    char* punt;

    punt = strrchr(buffer, '\n');
    if(!punt)
        return ERR;
    *punt = '\0';

    punt--;

    while(!EsEspacio(*punt))
    {
        punt--;
    }

    sscanf(punt +1, "%d", &indice->fila2);


    while(EsEspacio(*punt))
    {
        punt--;
    }

    *(punt +1) = '\0';
    punt = buffer;

    while(EsEspacio(*punt))
    {
        punt++;
    }

    sscanf(punt, "%d", &indice->fila1);
    return OK;
}

int CargarElementoEnTDA(TDAvec* vec, void* aux)
{
    void* pos = UltimaPosVaciaEnVecTDA(vec);
    if(!aux)
        return ERR;
    memcpy(pos, aux, vec->Tamdata);

    vec->ce ++;
    return OK;
}

void* UltimaPosVaciaEnVecTDA(TDAvec* vec)
{
    if(vec->ce == vec->MaxTam)
        {
            if(!RedimensionarTDA(vec))
                return NULL;
        }
    return (vec->vec + (vec->ce*vec->Tamdata));
}

int RedimensionarTDA(TDAvec * vec)
{
    int NuevaCantReg = vec->MaxTam + (int)( (float)vec->MaxTam * vec->FactorInc);

    void* aux = realloc(vec->vec, vec->Tamdata * NuevaCantReg);

    if(!aux)
        return ERR;

    vec->MaxTam = NuevaCantReg;
    vec->vec = aux;
    return OK;
}

int CrearTDA(TDAvec * vec, size_t tam)
{
    void* aux = malloc(tamMaxVec * tam);
    if(!aux)
        return ERR;

    vec->vec = aux;
    vec->ce= 0;
    vec->FactorInc = FactorIncremento;
    vec->MaxTam = tamMaxVec;
    vec->Tamdata = tam;
    return OK;
}




void MostrarMatriz(Matriz *mat, Mostrar muestra)
{
    puts("matriz: ");

    for(void** fila = mat->matriz; fila < mat->matriz + mat->CeFilas; fila++)
    {//vamos a harcodear 7 columnas, asi se muestra bien
    //for(void* columna = *fila; columna < (*fila) + (mat->columnas * mat->tamElem); columna+= mat->tamElem)
    //donde esta el 7 deberia ir esto ^
    for(void* columna = *fila; columna < (*fila) + (7 * mat->tamElem); columna+= mat->tamElem)
        {
            muestra(columna);
            printf("|");
        }
        printf("\n");
    }
}

void MostrarElementoIndice(const void* dato)
{
    IdxM* aux = (IdxM*) dato;
    printf("%d | %d \n", aux->fila1, aux->fila2);
}

void MostrarmatrizFloat(const void* dato)
{
    float* aux = (float*) dato;
    printf("%.2f", *aux);
}

int CargarMatrizDinamicaConArchivoTxt(Matriz * mat, FILE* FarchPerm)
{
    char buffer[Tambuffer];
    int i = 0;


    while(fgets(buffer, Tambuffer, FarchPerm) != NULL)
    {
        if(!AumentarFila(mat))
            return ERR;
        if(!TrozaryGuardarLinea(buffer, i, mat))
            return ERR;

        i++;

    }
    return OK;
}


int TrozaryGuardarLinea(char* buffer, int fila, Matriz * mat)
{
        int j = 0;
        float aux;
        char* puntero;
        char* lectura;

        puntero = strrchr(buffer, '\n');
        if(!puntero)
            return ERR;

        *puntero = '\0';

        sscanf(buffer, "%f|", &aux);
        CargarValorEnFilaNColJ(mat, fila, j, &aux);
        j++;

        lectura = buffer;

        while( j < ObtenermaxCol(mat) && (puntero = strchr(lectura, '|')) != NULL  )
        {
            sscanf(puntero + 1, "%f|", &aux);
            CargarValorEnFilaNColJ(mat, fila, j, &aux);

            lectura = puntero + 1;
            j++;
        }
        return OK;
}

int ObtenermaxCol(Matriz* mat)
{
    return mat->columnas;
}

int AumentarFila(Matriz* mat)
{
    if(mat->CeFilas == mat->filas)
    {
        if(!RedimencionarMatriz(mat))
            return ERR;
    }
    mat->CeFilas ++;
    return OK;
}

int RedimencionarMatriz(Matriz* mat)
{
    int Nueva_Fila =  mat->filas + (int)((float)mat->filas * (mat->factorIncr + 1));
    if(Nueva_Fila > mat->maxFilas)
        Nueva_Fila = mat->maxFilas;
    if(Nueva_Fila == mat->CeFilas)
    {
        puts("max alcanzado");
        return ERR;
    }
    void** NuevaDir = (void**)realloc(mat->matriz, Nueva_Fila*sizeof(void*));
    if(!NuevaDir)
        return ERR;

    void** inicio;
    void** fin = NuevaDir + Nueva_Fila;

    for(inicio = NuevaDir + mat->CeFilas; inicio < fin; inicio++)
    {
        *inicio = calloc(mat->columnas, mat->tamElem);
        if(!(*inicio))
        {
            for(void** liberar = inicio -1; liberar >= mat->matriz; liberar -- )
                free(*liberar),
            free(mat->matriz);
            InicializarMatriz(mat, NULL, 0, 0,0,0);
            return ERR;
        }
    }
    mat->matriz = NuevaDir;
    mat->filas = Nueva_Fila;
    return OK;

}


int CargarValorEnFilaNColJ(Matriz * mat,int filaN, int ColJ, void* elem)
{

    if(filaN<0 || ColJ < 0)
        return ERR;

    if(filaN >= mat->CeFilas)
        return ERR;

    if(ColJ >= mat->columnas)
        return ERR;

    memcpy( *(mat->matriz + filaN) + (ColJ * mat->tamElem), elem, mat->tamElem);


    return OK;
}

int CrearMatrizDinamica(Matriz* mat, size_t Tamelem, int Filas, int columnas)
{
    void** auxiliar = (void**)malloc(sizeof(void*) * Filas);


    if(!auxiliar)
        return ERR;

    for(void** inicio = auxiliar; inicio < auxiliar + Filas; inicio ++)
    {
        *inicio = calloc(columnas, Tamelem);
        if(!(*inicio))
        {
            for(void** fin = inicio - 1; fin >= auxiliar; fin --)
                free(*fin);
            free(auxiliar);
            InicializarMatriz(mat, NULL, 0, 0,0,0);
            return ERR;
        }

    }
    InicializarMatriz(mat, auxiliar, Filas,columnas,0, Tamelem);
    return OK;
}

void InicializarMatriz(Matriz* mat,
                        void** matriz,
                        int filas, int columnas,
                        int CeFilas,
                        size_t tamElem)
    {

        mat->matriz = matriz;
        mat->CeFilas = CeFilas;
        mat->filas = filas;
        mat->tamElem = tamElem;
        mat->columnas = columnas;
    }
void DestruirMatriz(Matriz * mat)
{
    void** inicio;
    void** fin = mat->matriz + mat->filas;
    for(inicio = mat->matriz ; inicio< fin; inicio ++)
        free(*inicio);
    free(mat->matriz);
}

