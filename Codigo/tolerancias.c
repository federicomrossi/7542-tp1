/* ******************************************************************
 *               TOLERANCIA PARA APLICACIÓN DE MULTAS
 * *****************************************************************/
/* 
 * 
 */


#include "tolerancias.h"


// TOLERANCIA DE INTERRUPCIONES POR FRECUENCIA (x_f)
// Establece una tolerancia máxima de número de interrupciones antes de
// comenzar a penalizar, siendo este máximo indicado como x_f.
// PRE: x_f, frecuencia representada como una cantidad entera; interrupciones, cantidad entera
// de interrupciones ocurridas.
// POST: Devuelve true si la cantidad de interrupciones es tolerable.
bool tolerancia_interrupcion_por_frecuencia(int x_f, int interrupciones)
{
	return (interrupciones <= x_f);
}

// TOLERANCIA DE INTERRUPCIONES POR DURACIÓN ACUMULADA (x_d)
// Establece una tolerancia máxima de duración acumulada de interrupciones
// antes de comenzar a penalizar, siendo este máximo indicado como x_d,
// en minutos.
// PRE: x_d, cantidad entera de minutos de tolerancia máxima; minutos_acumulados, cantidad entera
// de minutos de interrupción.
// POST: Devuelve true si la duracion acumulada es tolerable.
bool tolerancia_interrupcion_por_duracion_acumulada(int x_d, int minutos_acumulados)
{
	return (minutos_acumulados <= x_d);
}