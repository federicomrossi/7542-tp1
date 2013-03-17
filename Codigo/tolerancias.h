/* ******************************************************************
 * ******************************************************************
 *               TOLERANCIA PARA APLICACIÓN DE MULTAS
 * ******************************************************************
 * ******************************************************************
 * 
 * Definición de tolerancias aplicables para el cálculo de multas,
 * las cuales, entre sus parámetros deben incluir la interrupción
 * expresadas en minutos. Todas las tolerancias devuelven true si 
 * debe tolerarse la interrupción o false en su defecto.
 */
 

#ifndef TOLERANCIAS_H
#define TOLERANCIAS_H

#include <stdbool.h>
 

// TOLERANCIA DE INTERRUPCIONES POR FRECUENCIA
// Establece una tolerancia máxima de número de interrupciones antes de
// comenzar a penalizar, siendo este máximo indicado como x_f.
// PRE: 'x_f', frecuencia máxima representada como una cantidad entera; 
// 'interrupcion', cantidad entera de minutos de la interrupción.
// POST: devuelve true si no se ha superado x_f, o false en su defecto.
bool tolerancia_interrupcion_por_frecuencia(int x_f, int interrupcion);

// TOLERANCIA DE INTERRUPCIONES POR DURACIÓN ACUMULADA
// Establece una tolerancia máxima de duración acumulada de minutos de
// interrupción antes de comenzar a penalizar, siendo este máximo indicado 
// como x_d en minutos.
// PRE: 'x_d', cantidad entera de minutos de tolerancia máxima; 
// 'interrupcion', cantidad entera de minutos de la interrupción.
// POST: devuelve true si no se ha superado x_d, o false en su defecto.
bool tolerancia_interrupcion_por_duracion_acumulada(int x_d, int interrupcion);


#endif // TOLERANCIAS_H