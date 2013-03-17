/* ******************************************************************
 *                FILTROS PARA APLICACIÓN DE MULTAS
 * *****************************************************************/
/* 
 * 
 */


#include "filtros.h"


// INTERRUPCIÓN MOMENTANEA (x_m)
// Aquella interrupción que tenga una duración menor o igual a x_m 
// minutos, se considera momentanea y no será tomada en cuenta.
// PRE: x_m, cantidad entera de minutos; interrupcion, cantidad entera
// de minutos de interrupción.
_Bool filtro_es_interrupcion_momentanea(int x_m, int interrupcion)
{
	return (interrupcion <= x_m);
}