/* ******************************************************************
 * 					 PROGRAMA CALCULADOR DE MULTAS
 * *****************************************************************/
/* 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multas.h"


/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char **argv)
{
 	// Toma de parámetros
 	int x_m = atoi(argv[1]);
 	int x_f = atoi(argv[2]);
 	int x_d = atoi(argv[3]);
 	int x_p = atoi(argv[4]);
 	char *archivo = argv[5];

	procesar_interrupciones(x_m, x_f, x_d, x_p, archivo);

    return 0;
}
