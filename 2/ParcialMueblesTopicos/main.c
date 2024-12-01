/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************
* Corrección

****************************************************************************************
* Nota:
***************************************************************************************/
//solo tocar el boton de debug/continue. Ya esta compilado y se rompe la ruta.


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Vector/Vector.h"
#include "C:\Users\Valee\Desktop\TODO_VALEN\facultad\topicos de programacion\cursada 2c2024\ejercicios 2024\PARCIALES2024_RESUELTOS\ParcialMueblesTopicos_entregable\ParcialMueblesTopicos_entregable\SolucionParcialMueblesTopicos\SolucionMuebles.h"


#define Tam_Bufffer 300
#define IdxName "Depositos.idx"

#define MAL 0
#define BIEN 1

typedef void(*Mostrar)(void*);

int cmpInd_ALU(const void*, const void*);
int cmpTransfLista_ALU(const void* , const void* );

void actualizarDepositos_ALU(const char*, const char*);
int ActualizarDepositosConIdx_trans_Dep(Vector *, Vector*, const char*);
void actualizarTransf_ALU(void*, const void*);

int CargarTransferenciasEnVector_ALU(Vector *, char*);
void* BuscarElemEnIndice_ALU(Vector* , void* , Cmp );
void desencriptarTransferencias_ALU(const char*);
void DesencriptarLinea_ALU(char* buffer);
void InvertirParteCadena_Alu(char* inicioOrig, int cant_1, char* InicioDest);

int TrozartLineaTransferencia_ALU(char *, Transferencia*);
void InvertirParteDeCadena(char*, char*, int);
void vectorCargarDeArchivo_ALU(char*, Vector*, size_t);

void Mostrar_TDA(Vector *, Mostrar);
void MostrarTransTDA(void* );
void MostrarIndiceTDA(void* );

void vectorItCrear_ALU(VectorIterador *, Vector*);
void* vectorItSiguiente_ALU(VectorIterador * vecIterador);
void* vectorItInicio_ALU(VectorIterador * vecIterador);

int main()
{
	generarArchivos(true, true);

	mostrarArchivoTransferencias("Transferencias.txt");

	puts("");
	puts("Depositos antes de actualizar:");
	mostrarArchivoDepositos("Depositos.dat");

	actualizarDepositos("Transferencias.txt", "Depositos.dat");
	//actualizarDepositos_ALU("Transferencias.txt", "Depositos.dat");

	puts("");
	puts("Depositos despues de actualizar:");
	mostrarArchivoDepositos("Depositos.dat");

	return 0;
}


void actualizarDepositos_ALU(const char* archTransferencias, const char* archDepositos)
{
    Vector vIdx;
    Vector vTransferencias;


    desencriptarTransferencias_ALU(archTransferencias);
    vectorCrear(&vIdx, sizeof(Indice));
    vectorCrear(&vTransferencias, sizeof(Transferencia));

    CargarTransferenciasEnVector_ALU(&vTransferencias, (char*)archTransferencias);

    puts("transferencias");
    Mostrar_TDA(&vTransferencias, MostrarTransTDA);
    puts("fin trans");

    vectorCargarDeArchivo_ALU(IdxName, &vIdx, sizeof(Indice));

    /*
    puts("Indice");
    Mostrar_TDA(&vIdx, MostrarIndiceTDA);
    puts("fin indice");
    */
    ActualizarDepositosConIdx_trans_Dep(&vIdx, &vTransferencias, archDepositos);

    vectorDestruir(&vIdx);
    vectorDestruir(&vTransferencias);

}

void desencriptarTransferencias_ALU(const char *archTransferencias)
{
    char buffer[Tam_Bufffer];


    FILE* arch = fopen(archTransferencias, "rt");
    FILE* Ffinal = fopen("Nuevo.txt", "wt");

    while( fgets(buffer, Tam_Bufffer, arch) != NULL )
    {
        DesencriptarLinea_ALU(buffer);
        fprintf(Ffinal, "%s\n", buffer);
    }
    fclose(arch);
    fclose(Ffinal);

    remove(archTransferencias);
    rename("Nuevo.txt", archTransferencias);
}
void DesencriptarLinea_ALU(char* buffer)
{
    char Destino[Tam_Bufffer];

    char *pointer, *PointerDest;
    int cant_1, cant_2;

    pointer = strrchr(buffer, '\n');
    *pointer = '\0';

    //L. Encriptada: 5|32|6SILLA_PE4|IBIRIT8/0
    //L. Desencriptada: 56|23|SILLA_PETIRIBI|48


    strcpy(Destino, buffer);

    pointer = strchr(buffer, '\0');
    pointer--;
    sscanf(pointer, "%1d", &cant_2);
    sscanf(buffer, "%1d", &cant_1);

    PointerDest = strchr(Destino, '\0');
    PointerDest --;
    PointerDest -= cant_2;

    InvertirParteCadena_Alu(pointer, cant_2, PointerDest);

    pointer = buffer;
    pointer ++;
    pointer += cant_1;

    PointerDest= Destino;
    PointerDest++;

    InvertirParteCadena_Alu(pointer, cant_1, PointerDest);

    strcpy(buffer, Destino);
}

void InvertirParteCadena_Alu(char* inicioOrig, int cant_1, char* InicioDest)
{
    char* FinOrigen = inicioOrig - cant_1;
    char* iteradorOrig, *IteradorDest;

    for( iteradorOrig = inicioOrig - 1, IteradorDest = InicioDest ; iteradorOrig >= FinOrigen; iteradorOrig --, IteradorDest ++)
    {
        *IteradorDest = *iteradorOrig;
    }
}

void vectorCargarDeArchivo_ALU(char* name, Vector *vIdx, size_t Tam)
{
    FILE* arch = fopen(name, "rb");
    void* punt = malloc(Tam);

    while(fread(punt, Tam,1, arch) == 1)
    {
        vectorInsertarAlFinal(vIdx, punt);
    }
    free(punt);
}

void Mostrar_TDA(Vector *vec, Mostrar MostrarRegistro)
{
    void*inicio,*fin;
    fin = vec->vec + (vec->tamElem * vec->ce);


    for(inicio = vec->vec; inicio<fin; inicio += vec->tamElem)
    {
        MostrarRegistro(inicio);
    }

}

void MostrarIndiceTDA(void* Elemidx)
{
    Indice* aux = (Indice*)Elemidx;
    printf("%d %s %ld\n", aux->nroDep, aux->codProd, aux->nroReg);
}

void MostrarTransTDA(void* Elemidx)
{
    Transferencia* aux = (Transferencia*)Elemidx;
    printf("%d %d %s %d \n", aux->depOrigen, aux->depDestino, aux->codProd, aux->cantidad);
}

int ActualizarDepositosConIdx_trans_Dep(Vector *vIdx, Vector* vTransferencias, const char* archDepositos)
{
    TransferenciaElem trans_Elemento_1;
    TransferenciaElem trans_Elemento_2;
    Indice *PosOri;
    Indice *posDest;

    void* elementoIterado;
    Transferencia* auxiliarTransferencia;
    Deposito Dep_registro;
    VectorIterador vecIterador;

    FILE*  arch= fopen(archDepositos, "r+b");
    if(!arch)
        return MAL;

    vectorItCrear_ALU(&vecIterador, vTransferencias);

    elementoIterado= vectorItPrimero(&vecIterador);

    while( elementoIterado != NULL)
    {
        auxiliarTransferencia = (Transferencia*)elementoIterado;

        trans_Elemento_1.cantidad = auxiliarTransferencia->cantidad;
        trans_Elemento_1.nroDep = auxiliarTransferencia->depOrigen;
        strcpy(trans_Elemento_1.codProd, auxiliarTransferencia->codProd);

        trans_Elemento_2.cantidad = auxiliarTransferencia->cantidad;
        trans_Elemento_2.nroDep = auxiliarTransferencia->depDestino;
        strcpy(trans_Elemento_2.codProd, auxiliarTransferencia->codProd);

        PosOri = BuscarElemEnIndice_ALU(vIdx, &trans_Elemento_1, cmpInd_ALU);
        posDest = BuscarElemEnIndice_ALU(vIdx, &trans_Elemento_2, cmpInd_ALU);


        fseek(arch, PosOri->nroReg * (long)sizeof(Dep_registro) * 1L, SEEK_SET);
        fread(&Dep_registro, (long)sizeof(Dep_registro), 1, arch);

        Dep_registro.stock -= trans_Elemento_1.cantidad;

        fseek(arch, PosOri->nroReg * (long)sizeof(Dep_registro) * 1L, SEEK_SET);
        fflush(arch);
        fwrite(&Dep_registro, (long)sizeof(Dep_registro), 1, arch);
        //
        fflush(arch);
        fseek(arch, posDest->nroReg * (long)sizeof(Dep_registro) * 1L, SEEK_SET);
        fread(&Dep_registro, (long)sizeof(Dep_registro), 1, arch);

        Dep_registro.stock += trans_Elemento_1.cantidad;

        fseek(arch, posDest->nroReg * (long)sizeof(Dep_registro) * 1L, SEEK_SET);
        fflush(arch);
        fwrite(&Dep_registro, (long)sizeof(Dep_registro), 1, arch);

        elementoIterado = vectorItSiguiente_ALU(&vecIterador);
    }
    fclose(arch);
    return BIEN;
}

void* BuscarElemEnIndice_ALU(Vector* vec, void* elem, Cmp cmp)
{
    void* fin = vec->vec + (vec->ce * vec->tamElem);
    void* inicio;

    for(inicio = vec->vec; inicio<fin; inicio+=vec->tamElem)
    {
        if(cmp(inicio, elem) == 0)
            return inicio;
    }
    return NULL;
}


int cmpInd_ALU(const void* pvInd1, const void* pvInd2)
{
    Indice * auxIdx = (Indice*)pvInd1;
    TransferenciaElem* elemTrans = (TransferenciaElem*)pvInd2;

    int valorDep, resultProd;

    valorDep = auxIdx->nroDep - elemTrans->nroDep;
    resultProd = strcmp(auxIdx->codProd, elemTrans->codProd);

    if(valorDep == 0 && resultProd == 0)
        return 0;
    return 1;
}

int CargarTransferenciasEnVector_ALU(Vector *vTransferencias, char* archTransferencias)
{

    FILE* arch = fopen(archTransferencias, "rt");
    Transferencia auxiliar;
    char buffer[Tam_Bufffer];

    while(fgets(buffer, Tam_Bufffer, arch)!=NULL)
    {
        TrozartLineaTransferencia_ALU(buffer, &auxiliar);
        vectorOrdInsertar(vTransferencias, &auxiliar, cmpTransfLista_ALU, actualizarTransf_ALU);
    }
    fclose(arch);

    return  BIEN;

}

void vectorItCrear_ALU(VectorIterador *vecIt, Vector* vec)
{
    vecIt->vector = vec;
    vecIt->act = vec->vec;
    vecIt->tamElem = vec->tamElem;
    vecIt->ult = vecIt->act + (vecIt->vector->ce * vecIt->tamElem);
}
void* vectorItSiguiente_ALU(VectorIterador * vecIterador)
{
    vecIterador->act += vecIterador->tamElem;
    if(vecIterador->ult == vecIterador->act)
        return NULL;

    return (vecIterador->act);
}

void* vectorItInicio_ALU(VectorIterador * vecIterador)
{
    return vecIterador->vector;
}

int cmpTransfLista_ALU(const void* pvTr1, const void* pvTr2)
{
    //{ depOrigen: entero, depDestino: entero, codProd: cadena(15), cantidad: entero }
    Transferencia* trans1 = (Transferencia*) pvTr1;
    Transferencia* trans2 = (Transferencia*) pvTr2;

    int valorDep1, valorDep2,  resultProd;

    valorDep1 = trans1->depOrigen - trans2->depOrigen;
    valorDep2 = trans1->depDestino - trans2->depDestino;
    resultProd = strcmp(trans1->codProd, trans2->codProd);

    if(valorDep1 == 0 && valorDep2 == 0 && resultProd == 0)
        return 0;
    return 1;
}

void actualizarTransf_ALU(void* pvTrActualizada, const void* pvTrActualizadora)
{
    Transferencia* trans1 = (Transferencia*) pvTrActualizada;
    Transferencia* trans2 = (Transferencia*) pvTrActualizadora;

    trans1->cantidad += trans2->cantidad;
}


int TrozartLineaTransferencia_ALU(char *buffer, Transferencia* auxiliar)
{
    //5 6|23|SILLA_PETIRIBI|4 8

    char* puntero = strrchr(buffer, '\n');

    if(!puntero)
        return MAL;

    *puntero = '\0';
    //5 6|23|SILLA_PETIRIBI|4 8\0\n
    ////56|23|SILLA_PETIRIBI|48\0\0

    puntero = strrchr(buffer, '|');

    sscanf(puntero+1,"%d", &auxiliar->cantidad);
    *puntero = '\0';

    puntero = strrchr(buffer, '|');

    sscanf(puntero+1,"%s", auxiliar->codProd);
    *puntero = '\0';

    puntero = strrchr(buffer, '|');

    sscanf(puntero+1,"%d", &auxiliar->depDestino);
    *puntero = '\0';

    sscanf(buffer, "%d", &auxiliar->depOrigen);
    return BIEN;

}

