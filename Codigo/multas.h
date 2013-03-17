/* ******************************************************************
 * ******************************************************************
 *        PROCESADOR DE INTERRUPCIONES Y CALCULADOR DE MULTAS
 * ******************************************************************
 * ******************************************************************
 * 
 * Libreria de funciones que procesan interrupciones de servicio
 * eléctrico y calculan multas para aplicar a los clientes.
 */

#ifndef MULTAS_H
#define MULTAS_H


// Función que procesa las interrupciones del servicio ocurridas y registradas
// en un archivo, aplicando las multas pertinentes a cada cliente.
// PRE: 'x_m', cantidad máxima de minutos para la cual se considera momentanea
// una interrupción; 'x_f', cantidad máxima de interrupciones tolerables; 
// 'x_d', cantidad máxima de minutos acumulados tolerables; 'x_p', entero que
// establece el factor de multa a aplicar; 'file', nombre de archivo 
// (incluyendo su extensión) donde se registran las interrupciones y el
// cliente al que pertenece cada una de estas, dispuestos con el formato 
// [numero_cliente]:[consumo_tipico]:[duracion_interrupcion].
// POST: se envían los resultados (montos de las multas) a la salida estandar
// con el formato [numero_cliente]:[multa_calculada].
void procesar_interrupciones(int x_m, int x_f, int x_d, int x_p, char *file);


#endif
