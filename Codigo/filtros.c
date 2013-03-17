/* ******************************************************************
 * ******************************************************************
 *                FILTROS PARA APLICACIÓN DE MULTAS
 * ******************************************************************
 * ******************************************************************
 * 
 * Definición de filtros, los cuales, dados sus respectivos parámetros
 * (entre ellos una interrupción expresada en minutos) devuelven 
 * true o false de acuerdo a si deben filtrar o no dicha interrupción
 * respectivamente.
 */


#include "filtros.h"


// INTERRUPCIÓN MOMENTANEA (x_m)
// Aquella interrupción que tenga una duración menor o igual a x_m 
// minutos, se considera momentanea y no será tomada en cuenta.
// PRE: 'x_m', cantidad entera de minutos; 'interrupcion', cantidad
// entera de minutos de la interrupción.
// POST: se devuelve true si debe filtrarse la interrupción o
// false en caso contrario.
bool filtro_es_interrupcion_momentanea(int x_m, int interrupcion) {
	return (interrupcion <= x_m);
}
