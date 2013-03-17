/* ******************************************************************
 * 					 PROGRAMA CALCULADOR DE MULTAS
 * ******************************************************************
 * 
 * Facultad de Ingeniería - UBA
 * 75.42 Taller de Programación I
 * Trabajo Práctico N°1
 * 
 * ALUMNO: Federico Martín Rossi
 * PADRÓN: 92086
 * EMAIL: federicomrossi@gmail.com
 *
 * ******************************************************************
 *
 * Programa que se encarga de procesar un archivo con el listado de
 * interrupciones de servicio eléctrico y calcula la multa que debe
 * ser aplicada a cada cliente, enviandose estas a la salida
 * estandar del sistema con el formato [número_cliente]:[multa].
 *
 * FORMA DE USO
 * ============
 * 
 * El programa se ejecuta del siguiente modo:
 *
 *		# ./tp [x_m] [x_f] [x_d] [x_p] [archivo]
 *
 * donde,
 *
 *		x_m: cantidad máxima de minutos para la cual se considera 
 *			 momentanea una interrupción;
 *		x_f: tolerancia de interrupciones por frecuencia;
 *		x_d: tolerancia de interrupciones por duración acumulada;
 *		x_p: factor de multa;
 *		archivo: nombre de archivo (incluyendo su extensión) donde 
 *				 se registran las interrupciones y el cliente al 
 *				 que pertenece cada una de estas;
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multas.h"


/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char **argv) {
	// Toma de parámetros
	int x_m = atoi(argv[1]);
	int x_f = atoi(argv[2]);
	int x_d = atoi(argv[3]);
	int x_p = atoi(argv[4]);
	char *archivo = argv[5];

	procesar_interrupciones(x_m, x_f, x_d, x_p, archivo);

	return 0;
}
