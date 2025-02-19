/**********************************************************************************************************************
******************************* Complete sus datos ********************************************************************
***********************************************************************************************************************
* Apellido, Nombres: VALENTIN MASSA
*
* DNI:44510875
*
***********************************************************************************************************************
 * Corrección
***************

***********************************************************************************************************************
 * Nota:
**********************************************************************************************************************/
/*
#include "../Matriz/Matriz.h"
#include "../Vector/Vector.h"
#include "../SolucionMatrizDepositos/SolucionMatrizDepositos.h"
#include "../Comun/Comun.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#define ARG_STOCKS 1
#define ARG_MOVIMIENTOS 2

#define TamMaxVec 10
#define FactorIcr 0.6
#define TAMBuffer 300

#define EsESpacio(a)(a == ' '?1:0) // al final no se uso ya que el trozado era fijo

//declaracion a punteor funcion
typedef void(*Inicializar)(void*, const void*);
typedef void(*Mostrar)(const void*);
typedef void(*Actualizar)(void*, const void*);

//MATRIZ GENERICO
void matrizDestruir_alu(void** mat, int fil);
void** matrizCrear_alu(int fil, int col, size_t tamElem);
int InsertarElementoEnPosJPosIMAtrizCuadrada(void**Matriz, void* elem, int i, int j, int ColFilMax, size_t tamData, Actualizar act);

//TDA
int vectorCrear_alu(Vector* vec, size_t tamElem);
int vectorCrearDeArchivo_alu(Vector* v, size_t tamElem, const char* nomArch, Inicializar inic);
void InicializarReg_alu(void* dato1,const void* dato2);
int CargarElementoEnTDA_alu(Vector* v, void* RegAux);
int RedimensionarTDA_alu(Vector* vec);
void vectorDestruir_alu(Vector* vec);
void MostrarTDA_alu(Vector* vec, Mostrar muestra);
int BuscarPosEnTDA(Vector* vec, const void* elem, Cmp cmp);
int ObetenerCeDeTda_ALU(Vector* vec);
int ObetenerTamDataDeTda_ALU(Vector* vec);

//TDA_IT
void vectorItCrear_alu(VectorIterador* it, Vector* vector);
void* vectorItSiguiente_alu(VectorIterador* it);

//funciones mias
void MostrarRegistro_alu(const void* dato);
int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos);
int TrozarCadena_Alu(char* buffer, Movimiento* mov);
void ActualizarRegistro_Alu(void* dato1, const void* dato2);
int CompararElementos_Alu(const void* dato1, const void* dato2);
int CargarMovimientosTxt_alu(Vector* vec, void** matriz, const char* nombreStocks);
void MostraMatrizCuadradaNoGenerica(void** matriz, int MaxColFIl);
int CalcularTotalSegunFila(void** matriz, int ColMAx, int Fila );
int CalcularTotalSegunColumna(void** matriz, int FilaMAx, int col );
int ActualizarDepositos(Vector* vec, void** matriz, const char* nombreStocks);


int main(int argc, char* argv[])
{
	generarStocks(argv[ARG_STOCKS]);
	generarMovimientos(argv[ARG_MOVIMIENTOS]);

	puts("Stocks antes de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

/*********************************************************************************************************************/
	actualizarDepositos_ALU(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/************* Descomente la función de arriba y comente la de abajo para ejecutar su código. ************************/
	//actualizarDepositos(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/*********************************************************************************************************************/

	puts("\nStocks despues de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

	return 0;
}


int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos)
{
	Vector vec;
	void** matriz;

	vectorCrear_alu(&vec, sizeof(CodigoDeposito));
	vectorCrearDeArchivo_alu(&vec, sizeof(Stock), nombreStocks, InicializarReg_alu);

    matriz = matrizCrear_alu(ObetenerCeDeTda_ALU(&vec) , ObetenerCeDeTda_ALU(&vec) , sizeof(int));

    if(matriz == NULL)
    {
        vectorDestruir_alu(&vec);
        return 0;
    }

	if(!CargarMovimientosTxt_alu(&vec, matriz, nombreMovimientos))
    {
        matrizDestruir_alu(matriz, ObetenerCeDeTda_ALU(&vec));
        vectorDestruir_alu(&vec);
        return 0;
    }


    if(!ActualizarDepositos(&vec, matriz, nombreStocks))
        {
            matrizDestruir_alu(matriz, ObetenerCeDeTda_ALU(&vec));
            vectorDestruir_alu(&vec);
            return 0;
        }

    matrizDestruir_alu(matriz, ObetenerCeDeTda_ALU(&vec));
	vectorDestruir_alu(&vec);

	return TODO_OK;
}

int ActualizarDepositos(Vector* vec, void** matriz, const char* nombreStocks)
{
    FILE* Fstock = fopen(nombreStocks, "r+b");
    if(!Fstock)
        return 0;

    Stock stock;

    int entrada, salida;
    int i = 0;
    int ceVec = ObetenerCeDeTda_ALU(vec);

    while( fread(&stock, sizeof(stock), 1, Fstock) == 1 ) //deben terminar a la vez, uno se acrgo del otro.. pero controlamos
    {
        //como el veector lo cargue en orden segun el archivo

        salida = CalcularTotalSegunFila(matriz, ceVec , i);
        entrada = CalcularTotalSegunColumna(matriz, ceVec, i);
        stock.stock += (entrada-salida);

        fseek(Fstock, -1L * (long)sizeof(stock), SEEK_CUR);
        fflush(Fstock);
        fwrite(&stock, sizeof(stock), 1, Fstock);
        fflush(Fstock);
        i++;
    }
    fclose(Fstock);
    return 1;
}

int ObetenerTamDataDeTda_ALU(Vector* vec)
{
    return vec->tamElem;
}

int ObetenerCeDeTda_ALU(Vector* vec)
{
    return vec->ce;
}

int CalcularTotalSegunFila(void** matriz, int ColMAx, int Fila )
{
    int **mat = (int**)matriz;

    int cont =0;
    int aux;

    for(int j=0; j<ColMAx; j++)
        {
            aux = mat[Fila][j];
            cont += aux;
        }
    return cont;
}


int CalcularTotalSegunColumna(void** matriz, int FilaMAx, int col )
{
    int **mat = (int**)matriz;
    int cont =0;
    int aux;

    for(int i = 0; i<FilaMAx; i++)
        {
            aux = mat[i][col];
            cont += aux;
        }
    return cont;
}


int CargarMovimientosTxt_alu(Vector* vec, void** matriz, const char* nombreStocks)
{
    FILE* auxVec = fopen(nombreStocks, "rt");
    if(!auxVec)
        return 0;
    char buffer[TAMBuffer];
    Movimiento mov;
    CodigoDeposito cod1, cod2;
    int pos1, pos2;
    int ceVec = ObetenerCeDeTda_ALU(vec);

    while( fgets(buffer, TAMBuffer, auxVec) != NULL )
    {
        if(!TrozarCadena_Alu(buffer, &mov))
        {
            fclose(auxVec);
            return 0;
        }

        strcpy(cod1.codDeposito, mov.depOrigen);
        strcpy(cod2.codDeposito, mov.depDestino);

        pos1 = BuscarPosEnTDA(vec, &cod1, CompararElementos_Alu);
        pos2 = BuscarPosEnTDA(vec, &cod2, CompararElementos_Alu);

        if(pos1 == -1 || pos2 == -1 ) //si o si deben estar,no habla que el de movimientos tiene "novedades Nuevas"
            {
                fclose(auxVec);
                return 0;
            }

        if(!InsertarElementoEnPosJPosIMAtrizCuadrada(matriz, &mov.cantidad, pos1, pos2, ceVec, sizeof(int), ActualizarRegistro_Alu))
            {
                fclose(auxVec);
                return 0;
            }
    }
    return 1;
}

void ActualizarRegistro_Alu(void* dato1, const void* dato2)
{
    int* aux1 = (int*)dato1;
    int* aux2 = (int*)dato2;
    *aux1 += *aux2;
}


int BuscarPosEnTDA(Vector* vec, const void* elem, Cmp cmp)
{
    VectorIterador vecIt;
    vectorItCrear_alu(&vecIt, vec);
    void* aux;
    int i = 0;
    while( (aux = vectorItSiguiente_alu(&vecIt)) != NULL)
    {
        if(cmp(aux, elem)==0 )
            return i;
        i++;
    }
    return -1;
}

int CompararElementos_Alu(const void* dato1, const void* dato2)
{
    CodigoDeposito* aux1 = (CodigoDeposito*)dato1;
    CodigoDeposito* aux2 = (CodigoDeposito*)dato2;

    return strcmpi(aux1->codDeposito, aux2->codDeposito);
}

int TrozarCadena_Alu(char* buffer, Movimiento* mov)
{
    char *puntero;

    puntero = strrchr(buffer, '\n');
    if(!puntero)
        return 0;
    *puntero = '\0';

    //depOrigen: Cadena(10), depDestino: Cadena(10), cantidad: Entero(6))
    sscanf(buffer,"%10s%10s%6d", mov->depOrigen, mov->depDestino,&mov->cantidad);

    return 1;
}

int InsertarElementoEnPosJPosIMAtrizCuadrada(void**Matriz, void* elem, int i, int j, int ColFilMax, size_t tamData, Actualizar act)
{
    if(j < 0 || i<0 )
        return 0;
    if(j>=ColFilMax || i>= ColFilMax)
        return 0;

    void* aux = *(Matriz + i) + (j * tamData);
    act(aux, elem);
    return 1;

}

void** matrizCrear_alu(int fil, int col, size_t tamElem)
{
    void** matriz = malloc(fil * sizeof(void*));
    if(!matriz)
        return NULL;
    void** fin = matriz + fil;

    for(void** inicio = matriz; inicio < fin; inicio ++)
    {
        *inicio = calloc(col, tamElem);
        if(!(*inicio))
        {
            for(void** fin2 = (inicio - 1); fin2 >= matriz; fin2--)
            {
                free(*fin2);
            }
            free(matriz);
            return NULL;
        }
    }
    return matriz;

}
void matrizDestruir_alu(void** mat, int fil)
{
    void** fin = mat + fil;
    for(void** inicio = mat; inicio < fin; inicio++)
    {
        free(*inicio);
    }
    free(mat);
}


void MostraMatrizCuadradaNoGenerica(void** matriz, int MaxColFIl)
{
    int ** mat = (int**)matriz;

    int i,j;

    for(i=0;i<MaxColFIl;i++)
    {
        for(j=0; j<MaxColFIl; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        puts(" ");
    }
}


int vectorCrear_alu(Vector* vec, size_t tamElem)
{
    void* aux = malloc(tamElem * TamMaxVec);
    if(!aux)
        return 0;

    vec->vec = aux;
    vec->ce=0;
    vec->tamElem=tamElem;
    vec->cap = TamMaxVec;
    return 1;
}

int vectorCrearDeArchivo_alu(Vector* v, size_t tamElem, const char* nomArch, Inicializar inic)
{
    FILE* Faux = fopen(nomArch, "rb");

    if(!Faux)
        return 0;

    void * RegAuxLeido = malloc(tamElem);
    if(!RegAuxLeido)
    {
        fclose(Faux);
       return 0;
    }
    void * RegAuxConvertido = malloc(ObetenerTamDataDeTda_ALU(v));
    if(!RegAuxConvertido)
    {
        free(RegAuxLeido);
        fclose(Faux);
       return 0;
    }

    while(fread(RegAuxLeido, tamElem, 1, Faux) == 1)
    {
        inic(RegAuxLeido, RegAuxConvertido);
        if(!CargarElementoEnTDA_alu(v, RegAuxConvertido))
        {
            free(RegAuxLeido);
            free(RegAuxConvertido);
            fclose(Faux);
            return 0;
        }

    }
    free(RegAuxLeido);
    free(RegAuxConvertido);
    fclose(Faux);
    return 0;
}

void InicializarReg_alu(void* dato1, const void* dato2)
{
    CodigoDeposito* codDep = (CodigoDeposito*)dato2;
    Stock * Total = (Stock*)dato1;

    strcpy(codDep->codDeposito, Total->codDeposito);

}

int CargarElementoEnTDA_alu(Vector* v, void* RegAux)
{
    if(v->cap == v->ce)
    {
        if(!RedimensionarTDA_alu(v))
            return 0;
    }
    memcpy(v->vec + (v->ce * v->tamElem), RegAux, v->tamElem);
    v->ce ++;
    return 1;
}

int RedimensionarTDA_alu(Vector* vec)
{
    int NuevaCap = vec->cap + (int)((float)vec->cap * FactorIcr);
    void* aux = realloc(vec->vec, NuevaCap * vec->tamElem);
    if(!aux);

    vec->vec = aux;
    vec->cap = NuevaCap;
    return 1;
}

void vectorDestruir_alu(Vector* vec)
{
    free(vec->vec);
}

void MostrarTDA_alu(Vector* vec, Mostrar muestra)
{
    VectorIterador vecIt;
    vectorItCrear_alu(&vecIt, vec);
    void* aux;
    puts("TDA VECTOR");
    while( (aux = vectorItSiguiente_alu(&vecIt)) != NULL )
        muestra(aux);

    puts(" ");
}

void vectorItCrear_alu(VectorIterador* it, Vector* vector)
{
    it->vector = vector;
    it->act = vector->vec;
    it->tamElem = vector->tamElem;
    it->ult = vector->vec + (vector->ce * vector->tamElem);
}

void* vectorItSiguiente_alu(VectorIterador* it)
{
    if(it->act == it->ult)
        return NULL;
    void* aux = it->act;

    it->act += it->tamElem;
    return aux;
}

void MostrarRegistro_alu(const void* dato)
{
    CodigoDeposito* aux = (CodigoDeposito*)dato;

    printf("%s\n", aux->codDeposito);
}
