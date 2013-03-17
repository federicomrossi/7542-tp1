/* ******************************************************************
 * ******************************************************************
 *        PROCESADOR DE INTERRUPCIONES Y CALCULADOR DE MULTAS
 * ******************************************************************
 * ******************************************************************
 * 
 * Libreria de funciones que procesan interrupciones de servicio
 * eléctrico y calculan multas para aplicar a los clientes.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusión de filtros y tolerancias
#include "filtros.h"
#include "tolerancias.h"



/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/


// Función que realiza la apertura de un archivo.
// PRE: 'archivo' es el nombre (y extensión) del archivo a abrir.
// POST: se devuelve el puntero al archivo.
FILE* archivo_abrir(char *archivo) {
	FILE *fp;

	// Apertura del archivo para lectura
	fp = fopen(archivo, "r");

	// Verificación de errores producidos
	if (fp == NULL) {
		printf("ERROR: No ha sido posible abrir el archivo %s.\n", archivo);
		// Se retorna 0 en todos los casos, a pesar de existir error.
		exit(0);
	}

	return fp;
}

// Cierra el stream de un archivo.
// PRE: 'fp' es un puntero al archivo
void archivo_cerrar(FILE* fp) {
	fclose(fp);
}

// Función que calcula la multa a aplicar a un cliente.
// PRE: 'consumo_tipico', entero que representa el consumo tipico para ese 
// cliente; 'factor_de_multa', entero que expresa el factor de multa a 
// aplicar; 'minutos_multables', entero que expresa la cantidad de minutos a 
// multar. 
// POST: devuelve un entero que representa el monto de la multa a aplicar.
int calculador_multa(int consumo_tipico, int factor_de_multa, 
	int minutos_multables) {
	return (consumo_tipico * factor_de_multa * minutos_multables);
}

// Función que envía a la salida estandar el número de cliente y el monto de
// la multa a aplicarle, con el formato CLIENTE:MULTA.
// PRE: 'num_cliente', número de cliente; 'multa', monto entero de la multa
// del cliente.
void enviar_a_salida_estandar(int num_cliente, int multa) {
	printf("%d:%d\n", num_cliente, multa);
}

// Función que dado los parámetros a especificar, genera la multa
// correspondiente y la envia a la salida estandar.
// PRE: 'x_p', factor de multa a aplicar; 'cliente', número del cliente a
// quien se va a aplicar la multa; 'consumo_tipico', consumo típico registrado
// por el cliente; 'minutos_acumulados', minutos acumulados de interrupciones;
// 'flag_tolerancia_superada', sensor booleano que expresa si se ha superado
// alguna tolerancia.
void generar_multa(int x_p, int cliente, int consumo_tipico, 
	int minutos_acumulados, bool flag_tolerancia_superada) {
	int minutos_multables;

	if (!flag_tolerancia_superada)
		// Si no se ha superado ninguna de las tolerancias, anulamos los 
		// minutos acumulados 
		minutos_multables = 0;
	else
		minutos_multables = minutos_acumulados;

	// Enviamos cliente y su multa correspondiente a la salida estandar
	enviar_a_salida_estandar(cliente, 
		calculador_multa(consumo_tipico, x_p, minutos_multables));
}

// Función que se encarga de evaluar las tolerancias sobre las interrupciones
// de un cliente.
// PRE: 'x_m', cantidad máxima de minutos para la cual se considera momentanea
// una interrupción; 'x_f', cantidad máxima de interrupciones tolerables;
// 'x_d', cantidad máxima de minutos acumulados tolerables; 
// 'duracion_interrupcion', duración en minutos de la interrupción a procesar
// del cliente; cant_interrupciones, entero que especifica la cantidad de
// interrupciones registradas hasta el momento para el cliente; 
// 'minutos_acumulados', puntero a variable que almacena los minutos acumulados
// de interrupciones; 'flag_tolerancia_superada', puntero a variable booleana
// que expresa si se ha superado alguna tolerancia.
// POST: el flag de tolerancia superada se seteara en true si alguna
// tolerancia o todas a la vez son superadas; 'minutos_acumulados' adoptará un
// nuevo valor de minutos de acuerdo a la tolerancia superada. En caso de
// superarse todas a la vez, se considera aquella que registre mas cantidad de
// minutos acumulados.
void evaluar_tolerancias(int x_m, int x_f, int x_d, int duracion_interrupcion,
	int cant_interrupciones, int *minutos_acumulados, 
	bool *flag_tolerancia_superada) {
	// Se supera la tolerancia por frecuencia primero
	if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
		(tolerancia_interrupcion_por_duracion_acumulada(x_d,
		 *minutos_acumulados))) {
		*flag_tolerancia_superada = true;
		*minutos_acumulados = 0;
		*minutos_acumulados += duracion_interrupcion;
	}
	// Se supera la tolerancia por duración acumulada primero
	else if ((tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones))
			&& (!tolerancia_interrupcion_por_duracion_acumulada(x_d, 
			*minutos_acumulados))) {
		*flag_tolerancia_superada = true;
		*minutos_acumulados -= x_d;
	}
	// Se superan las tolerancias por frecuencia y por duración acumulada al 
	// mismo tiempo
	else if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)
) && (!tolerancia_interrupcion_por_duracion_acumulada(x_d,
		*minutos_acumulados))) {
		*flag_tolerancia_superada = true;
		*minutos_acumulados = 0;
		*minutos_acumulados += duracion_interrupcion;
	}
}

// Función que se encarga de aplicar filtros y tolerancias a las interrupciones
// de los clientes.
// PRE: 'x_m', cantidad máxima de minutos para la cual se considera momentanea 
// una interrupción; 'x_f', cantidad máxima de interrupciones tolerables; 
// 'x_d', cantidad máxima de minutos acumulados tolerables; 
// 'duracion_interrupcion', duración en minutos de la interrupción a procesar
// del cliente; 'cant_interrupciones', puntero a variable entera que posea la
// cantidad de interrupciones registradas hasta el momento para el cliente;
// 'minutos_acumulados', puntero a variable que almacena los minutos acumulados
// de interrupciones; 'flag_tolerancia_superada', puntero a variable booleana
// que expresa si se ha superado alguna tolerancia.
// POST: 'cant_interrupciones' es incrementado si no son aplicables los
// filtros; 'minutos_acumulados' es actualizado de acuerdo a los filtros y
// tolerancias.
void aplicar_filtros_y_tolerancias(int x_m, int x_f, int x_d, 
	int duracion_interrupcion, int *cant_interrupciones, 
	int *minutos_acumulados, bool *flag_tolerancia_superada) {
	// Filtramos las interrupciones momentaneas
	if(!filtro_es_interrupcion_momentanea(x_m, duracion_interrupcion)) {
		++(*cant_interrupciones);
		*minutos_acumulados += duracion_interrupcion;

		// Evaluamos si se superon las tolerancias solo cuando no se ha
		// sensado ninguna aún
		if (!(*flag_tolerancia_superada)) {
			evaluar_tolerancias(x_m, x_f, x_d, duracion_interrupcion,
				*cant_interrupciones, minutos_acumulados, 
				flag_tolerancia_superada);
		}
	}
}





/* ******************************************************************
 *                     FUNCIONES DE LA LIBRERIA
 * *****************************************************************/


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
void procesar_interrupciones(int x_m, int x_f, int x_d, int x_p, char *file) {
	// Variables para el tratamiento del archivo
	FILE *fp;
	char buffer[100];
	// Variables auxiliares para interrupción
	int cliente;
	int consumo_tipico = 0;
	int duracion_interrupcion;
	// Variables auxiliares de procesamiento
	int cliente_tmp = 0;
	int cant_interrupciones = 0;
	int minutos_acumulados = 0;
	// Flag para detección de tolerancias superadas
	bool flag_tolerancia_superada = false;


	// Apertura del archivo para lectura
	fp = archivo_abrir(file);

	// Procesamos linea por linea del archivo
	while(fgets(buffer, 100, fp)) {
		// Tomamos el número de cliente de la interrupción
		cliente = atoi(strtok(buffer, ":"));

		// Evaluamos si ha cambiado el cliente
		if ((cliente != cliente_tmp) && (cliente_tmp !=0)) {	
			// Generamos la multa para el cliente
			generar_multa(x_p, cliente_tmp, consumo_tipico,
				minutos_acumulados,	flag_tolerancia_superada);

			// Establecemos el nuevo cliente como actual
			cliente_tmp = cliente;

			// Re-inicializamos variables de procesamiento
			flag_tolerancia_superada = false;
			cant_interrupciones = 0;
			minutos_acumulados = 0;
		}
		// Sensamos al cliente de la primer interrupción
		else if (cliente_tmp == 0)
			cliente_tmp = cliente;

		// Procesamos info de interrupción del cliente
		consumo_tipico = atoi(strtok(NULL, ":"));
		duracion_interrupcion = atoi(strtok(NULL, ":"));
		
		// Aplicamos filtros y evaluamos tolerancias
		aplicar_filtros_y_tolerancias(x_m, x_f, x_d, duracion_interrupcion,
			&cant_interrupciones, &minutos_acumulados, 
			&flag_tolerancia_superada);
	}

	// Si no se han procesado interrupciones, no hacemos nada.
	if (cliente_tmp == 0) return;

	// Generamos la multa para el último cliente correspondiente a la última
	// interrupción almacenada en el archivo.
	generar_multa(x_p, cliente_tmp, consumo_tipico, minutos_acumulados, 
		flag_tolerancia_superada);
	
	// Cerramos el archivo
	archivo_cerrar(fp);
}
