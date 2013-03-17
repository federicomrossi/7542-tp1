/* ******************************************************************
 *               TOLERANCIA PARA APLICACIÓN DE MULTAS
 * *****************************************************************/
/* 
 * 
 */
 

#ifndef TOLERANCIAS_H
#define TOLERANCIAS_H


// TOLERANCIA DE INTERRUPCIONES POR FRECUENCIA (x_f)
// Establece una tolerancia máxima de número de interrupciones antes de
// comenzar a penalizar, siendo este máximo indicado como x_f.
// PRE: x_f, frecuencia representada como una cantidad entera; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool tolerancia_interrupcion_por_frecuencia(int x_f, int interrupcion);

// TOLERANCIA DE INTERRUPCIONES POR DURACIÓN ACUMULADA (x_d)
// Establece una tolerancia máxima de duración acumulada de interrupciones
// antes de comenzar a penalizar, siendo este máximo indicado como x_d,
// en minutos.
// PRE: x_d, cantidad entera de minutos de tolerancia máxima; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool tolerancia_interrupcion_por_duracion_acumulada(int x_d, int interrupcion);


#endif // TOLERANCIAS_H