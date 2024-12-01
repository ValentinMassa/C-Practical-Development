#include "EXAMEN.h"
#include "MATRICES.h"


FILE* AbrirArchivo(char*, char *);

int CargarMatrizEnMemoria(SMatriz *, FILE*);


int RestaurarColumna_Solucion(char* TABLAPERMUTADA,char* TABLARESTAURADA, int NUMEROCAMPO)
{
    FILE* TablaPerm, *TablaRes, *Idx ;
    SMatriz Matriz;



    TablaRes = AbrirArchivo(TABLARESTAURADA, "wt");

    if(!CrearMatrizGenerica(&Matriz, FILAS, MAXCAMPOS, sizeof(float), FactAumento))
        return 0;

    TablaPerm = AbrirArchivo(TABLAPERMUTADA, "rt");
    if(!TablaPerm)
        return 0;

    CargarMatrizEnMemoria(&Matriz, TablaPerm);
    fclose(TablaPerm);

    Idx = AbrirArchivo(PermutacionesTxt,"rt");
    if(!Idx)
        return 0;

    PermutarColumna(Idx, &Matriz);



}

int PermutarColumna(FILE* Idx, SMatriz * matriz)
{
    float vector[matriz->ceFil];
    CargarVector(vector,matriz->ceFil, Idx);



}

int CargarVector(float * vec, int ttamMax, FILE* idx)
{
    char buffer[TamBuffer];
    float valor1, valor2;

    while(fgets(buffer, TamBuffer, idx, valor1, valor2) != NULL)
    {
        TrozarLineaIdx(buffer, &valor1, &valor2);

    }


}

int TrozarLineaIdx(char* buffer, float* valor1, float* valor2)
{
    char* pointer = strrchr(bufffer, '\n');

    if(!pointer)
        return 0;
    *pointer = '\0';

    pointer = strchr(bufffer, '\0');

    while(!ESespacio(*pointer))
        pointer--;
    sscanf(pointer + 1, "%f", valor2);
    *(pointer + 1) = '\0';

    while(ESespacio(*pointer))
        pointer--;
    while(!ESespacio(*pointer))
        pointer--;
    sscanf(pointer + 1, "%f", valor2);
    return 1;
}



int CargarMatrizEnMemoria(SMatriz * matriz, FILE* permutada)
{
    char buffer[TamBuffer];

    while(fgets(buffer,TamBuffer,permutada))
    {
        if(matriz->ceFil == matriz->filas && !AumentaFILASMatriz(matriz))
            return 0;

        if(!TrozarYGuardarLinea(matriz, buffer, Contfila))
            return 0;

        matriz->ceFil++;
    }
    return 1;
}
int TrozarYGuardarLinea(SMatriz *matriz, char* buffer, int Contfila)
{
    char* pointer;
    float ** mat;
    float auxiliar[MAXCAMPOS];
    int ce, cont;

    pointer = strrchr(buffer, '\n');

    if(!pointer)
        return 0;
    *pointer = '\0';

    ce=0;

    while(( pointer = strrchr(buffer, '|')) != NULL && ce < matriz->col)
    {
        sscanf(pointer + 1, "%f", (auxiliar + ce) );
        *pointer = '\0';
        ce ++;
    }
    if(ce == matriz->col)
        return 0;
    //ponemos los datos del vector en la matriz

    mat = (float**)matriz->matriz;
    cont = 0;

    while(ce > 0)
    {
        mat[Contfila][cont] = *(auxiliar +(ce-1));
        cont ++;
        ce --;
    }
    return 1;
}

FILE* AbrirArchivo(char* name, char * ap_mode)
{
    FILE* arch = fopen(name, ap_mode);
    if(!arch)
        return NULL;

    return arch;
}




int AumentaFILASMatriz(SMatriz * matriz)
{
    int FilasFinal = (int)((float)matriz->col * (matriz->faactorAumento +1));

    void** nuevoPunt = (void**)realloc(matriz->matriz, (FilasFinal * matriz->tamData));
    if(!nuevoPunt)
        return 0;

    void** end = nuevoPunt + FilasFinal;
    void** inicio;
    for(inicio = matriz->matriz + matriz->filas; inicio<end; inicio ++)
    {
        *inicio = malloc(matriz->tamData * matriz->col);
        for(void** end = inicio - 1; end >= matriz->matriz; end--)
            {
                free(*end);
            }
        free(nuevoPunt);

        PonerValoresEnSmatriz(matriz, NULL, 0,0,0,0,0);
        return 0;

    }
    PonerValoresEnSmatriz(matriz, nuevoPunt, matriz->ceFil, FilasFinal, matriz->col,
                          matriz->tamData, matriz->faactorAumento);
    return 1;
}



