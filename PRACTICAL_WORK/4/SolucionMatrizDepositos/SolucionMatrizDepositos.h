#ifndef SOLUCIONMATRIZDEPOSITOS_SOLUCIONMATRIZDEPOSITOS_H
#define SOLUCIONMATRIZDEPOSITOS_SOLUCIONMATRIZDEPOSITOS_H


typedef struct
{
	char codDeposito[11];
	int stock;
}
Stock;


typedef struct
{
	char depOrigen[11];
	char depDestino[11];
	int cantidad;
}
Movimiento;


void generarStocks(const char* nombreStocks);
void generarMovimientos(const char* nombreMovimientos);
void mostrarStocks(const char* nombreStocks);
void mostrarMovimientos(const char* nombreMovimientos);
int actualizarDepositos(const char* nombreStocks, const char* nombreMovimientos);
int obtenerCantDepositos(const char* nombreStocks);
int crearVectorCodigosDepositos(const char* nombreStocks, int cantDepositos, Vector* codigosDepositos);
void inicializarMatrizEnCero(int** matMovDeps, int filas, int columnas);
int cargarMatrizMovimientosDepositos(const char* nombreMovimientos, int** matMovDeps, int cantDepositos, Vector* codigosDepositos);
int procesarMatrizMovimientosDepositosActualizandoStocks(int** matMovDeps, int cantDepositos, const Vector* codigosDepositos, const char* nombreStocks);
int codigoASubindice(const Vector* codigosDepositos, char* codigo);
int cmpCodDep(const void* codDep1, const void* codDep2);


#endif //SOLUCIONMATRIZDEPOSITOS_SOLUCIONMATRIZDEPOSITOS_H
