/* ******************************************************************
 *        PROCESADOR DE INTERRUPCIONES Y CALCULADOR DE MULTAS
 * *****************************************************************/
/* 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filtros.h"
#include "tolerancias.h"



/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/
 

// Función que realiza la apertura de un archivo.
// PRE: archivo es el nombre (y extensión) del archivo a abrir.
// POST: se devuelve el puntero al archivo.
FILE* archivo_abrir(char *archivo)
{
	FILE *fp;

	// Apertura del archivo para lectura
 	fp = fopen(archivo, "r");

 	// Verificación de errores producidos
 	if (fp == NULL)
 	{
 		printf("ERROR: No ha sido posible abrir el archivo %s.\n", archivo);
 		// Se retorna 0 en todos los casos, a pesar de existir error.
 		exit(0);
 	}

 	return fp;
}

// Cierra el stream de un archivo.
// PRE: fp es un puntero al archivo
void archivo_cerrar(FILE* fp)
{
	fclose(fp);
}

//
int calculador_multa(int consumo_tipico, int factor_de_multa, int minutos_multables)
{
	return (consumo_tipico * factor_de_multa * minutos_multables);
}

//
void enviar_a_salida_estandar(int num_cliente, int multa)
{
	printf("%d:%d\n", num_cliente, multa);

	// // DEBUG CODE
	// FILE *f;
	// f = fopen("stdout.txt","a+");
	// fprintf (f, "%d:%d\n", num_cliente, multa);
	// fclose(f);
	// // END DEBUG CODE
}

//
void evaluar_tolerancias(int x_m, int x_f, int x_d, int duracion_interrupcion, 
	int cant_interrupciones, int *minutos_acumulados, bool *flag_tol_frecuencia, 
	bool *flag_tol_duracion_acumulada)
{
	// Se supera la tolerancia por frecuencia primero
	if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
		(tolerancia_interrupcion_por_duracion_acumulada(x_d, *minutos_acumulados)))
	{
		*flag_tol_frecuencia = true;
		*minutos_acumulados = 0;
		*minutos_acumulados += duracion_interrupcion;
	}
	// Se supera la tolerancia por duración acumulada primero
	else if ((tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
		(!tolerancia_interrupcion_por_duracion_acumulada(x_d, *minutos_acumulados)))
	{
		*flag_tol_duracion_acumulada = true;
		*minutos_acumulados -= x_d;
	}
	// Se superan las tolerancias por frecuencia y por duración acumulada al mismo tiempo
	else if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
		(!tolerancia_interrupcion_por_duracion_acumulada(x_d, *minutos_acumulados)))
	{
		*flag_tol_frecuencia = true;
		*flag_tol_duracion_acumulada = true;
		*minutos_acumulados = 0;
		*minutos_acumulados += duracion_interrupcion;
	}
}

//
void aplicar_filtros_y_tolerancias(int x_m, int x_f, int x_d, int duracion_interrupcion, 
	int *cant_interrupciones, int *minutos_acumulados, bool *flag_tol_frecuencia, 
	bool *flag_tol_duracion_acumulada)
{
	// Filtramos las interrupciones momentaneas
	if(!filtro_es_interrupcion_momentanea(x_m, duracion_interrupcion))
	{
		++*cant_interrupciones;
		*minutos_acumulados += duracion_interrupcion;

		// Evaluamos si se superon las tolerancias solo cuando no se ha
		// sensado ninguna aún
		if ((!(*flag_tol_frecuencia)) && (!(*flag_tol_duracion_acumulada)))
		{
			evaluar_tolerancias(x_m, x_f, x_d, duracion_interrupcion, 
				*cant_interrupciones, minutos_acumulados, flag_tol_frecuencia,
				flag_tol_duracion_acumulada);
		}
	}
}




/* ******************************************************************
 *                           PRIMITIVAS
 * *****************************************************************/


// 
void procesar_interrupciones(int x_m, int x_f, int x_d, int x_p, char *archivo)
{
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
	// Flags para detección de tolerancias superadas
	bool flag_tol_frecuencia = false;
	bool flag_tol_duracion_acumulada = false;


 	// Apertura del archivo para lectura
 	fp = archivo_abrir(archivo);


 	while(fgets(buffer, 100, fp))
 	{
 		// Tomamos el número de cliente de la interrupción
 		cliente = atoi(strtok(buffer, ":"));

		// Evaluamos si ha cambiado el cliente
		if((cliente != cliente_tmp) && (cliente_tmp !=0))
		{	
			if((!flag_tol_frecuencia) && (!flag_tol_duracion_acumulada))
				minutos_acumulados = 0;

			// Enviamos cliente y su multa correspondiente a la salida estandar
			enviar_a_salida_estandar(cliente_tmp, 
				calculador_multa(consumo_tipico, x_p, minutos_acumulados));

			// Establecemos el nuevo cliente como actual
			cliente_tmp = cliente;

			// Re-inicializamos variables de procesamiento
			flag_tol_frecuencia = false;
			flag_tol_duracion_acumulada = false;
		 	cant_interrupciones = 0;
		 	minutos_acumulados = 0;
		}

		// Sensamos al cliente de la primer interrupción
		if(cliente_tmp == 0)
			cliente_tmp = cliente;

		// Procesamos interrupcion del cliente
		consumo_tipico = atoi(strtok(NULL, ":"));
 		duracion_interrupcion = atoi(strtok(NULL, ":"));
		
		// Aplicamos filtros y evaluamos tolerancias
		aplicar_filtros_y_tolerancias(x_m, x_f, x_d, duracion_interrupcion,
			&cant_interrupciones, &minutos_acumulados, &flag_tol_frecuencia,
			&flag_tol_duracion_acumulada);
 	}

 	// Si no se han procesado interrupciones, no hacemos nada.
 	if(cliente_tmp == 0) return;


 	// Procesamos al último cliente correspondiente a la última interrupción
 	// almacenada en el archivo
 	//// Si no se ha superado ninguna de las tolerancias, anulamos los 
 	//// minutos acumulados
	if((!flag_tol_frecuencia) && (!flag_tol_duracion_acumulada))
		minutos_acumulados = 0;
 	//// Enviamos cliente y su multa correspondiente a la salida estandar
	enviar_a_salida_estandar(cliente_tmp, calculador_multa(consumo_tipico, x_p, minutos_acumulados));

	
	// Cerramos el archivo
	archivo_cerrar(fp);
}