#ifndef FILTROS_H
#define FILTROS_H

/* ******************************************************************
 *                FILTROS PARA APLICACIÓN DE MULTAS
 * *****************************************************************/
/* 
 * Los filtros deben poseer una post-condición común, la cual se
 * limita a devolver 0 si no debe aplicarse el filtro, o 1 en caso 
 * contrario; es decir, debe devolverse un valor de tipo _Bool.
 */



// INTERRUPCIÓN MOMENTANEA (x_m)
// Aquella interrupción que tenga una duración menor o igual a x_m 
// minutos, se considera momentanea y no será tomada en cuenta.
// PRE: x_m, cantidad entera de minutos; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool filtro_es_interrupcion_momentanea(int x_m, int interrupcion);

// TOLERANCIA DE INTERRUPCIONES POR FRECUENCIA (x_f)
// Establece una tolerancia máxima de número de interrupciones antes de
// comenzar a penalizar, siendo este máximo indicado como x_f.
// PRE: x_f, frecuencia representada como una cantidad entera; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool filtro_tolerancia_interrupcion_por_frecuencia(int x_f, int interrupcion);

// TOLERANCIA DE INTERRUPCIONES POR DURACIÓN ACUMULADA (x_d)
// Establece una tolerancia máxima de duración acumulada de interrupciones
// antes de comenzar a penalizar, siendo este máximo indicado como x_d,
// en minutos.
// PRE: x_d, cantidad entera de minutos de tolerancia máxima; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool filtro_tolerancia_interrupcion_por_duracion_acumulada(int x_d, int interrupcion);


#endif // FILTROS_H