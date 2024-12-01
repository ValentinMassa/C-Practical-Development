#include <stdio.h>
#include <stdlib.h>
#include "SOLUCION.h"

#define EXAMEN

#define TABLAORIGINAL       "tabla.txt"
#define TABLAPERMUTADA      "tablaPermutada.txt"
#define TABLARESTAURADA     "tablaRecuperada.txt"
#define NUMEROCAMPO         6 ///Campo a permutar


#ifdef EXAMEN
   #define restaurarColumna restaurarColumnaALU
#endif // EXAMEN


int main()
{

    //Quite la creacion automatica del lote de prueba
    //para probar con sus propios lotes
    crearLotePrueba(TABLAORIGINAL);
    ///Respetar siempre los prototipos entregados
    if(!permutarColumna(TABLAORIGINAL, TABLAPERMUTADA, NUMEROCAMPO)){
        puts("La tabla no pudo ser permutada, verifique archivos y cantidad de campos");

    }else{
        if(!restaurarColumna(TABLAPERMUTADA, TABLARESTAURADA, NUMEROCAMPO)){
            puts("La tabla no pudo ser restaurada, verifique archivos y cantidad de campos");
        }

    }

    return 0;
}
