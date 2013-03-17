#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtros.h"
#include "tolerancias.h"


/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/


int calculador_multa(int consumo_tipico, int x_p, int minutos_multables)
{
	return (consumo_tipico * x_p * minutos_multables);
}


void enviar_a_salida_estandar(int num_cliente, int multa)
{
	printf("%d:%d\n", num_cliente, multa);
}


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




/* ******************************************************************
 *                           PRIMITIVAS
 * *****************************************************************/

void procesar_interrupciones(int x_m, int x_f, int x_d, int x_p, char *archivo)
{
	FILE *fp;
 	char buffer[100];

 	int cliente;
 	int consumo_tipico = 0; 
	int duracion_interrupcion;
	// Variables auxiliares de procesamiento
	int cliente_tmp = 0;
	int cant_interrupciones = 0;
	int minutos_acumulados = 0;
	// Flags para detección de tolerancias superadas
	_Bool flag_tol_frecuencia = 0;
	_Bool flag_tol_duracion_acumulada = 0;


 	// Apertura del archivo para lectura
 	fp = archivo_abrir(archivo);


 	while(fgets(buffer, 100, fp))
 	{
 		cliente = atoi(strtok(buffer, ":"));

		// Evaluamos si ha cambiado el cliente
		if((cliente != cliente_tmp) && (cliente_tmp !=0))
		{	
			if((!flag_tol_frecuencia) && (!flag_tol_duracion_acumulada))
				minutos_acumulados = 0;

			// Enviamos cliente y su multa correspondiente a la salida estandar
			enviar_a_salida_estandar(cliente_tmp, calculador_multa(consumo_tipico, x_p, minutos_acumulados));

			// Establecemos el nuevo cliente como actual
			cliente_tmp = cliente;

			// Re-inicializamos variables de procesamiento
			flag_tol_frecuencia = 0;
			flag_tol_duracion_acumulada = 0;
		 	cant_interrupciones = 0;
		 	minutos_acumulados = 0;
		}

		// Sensamos al cliente de la primer interrupción
		if(cliente_tmp == 0)
			cliente_tmp = cliente;


		// Procesamos interrupcion del cliente
		consumo_tipico = atoi(strtok(NULL, ":"));
 		duracion_interrupcion = atoi(strtok(NULL, ":"));
		
		// Filtramos las interrupciones momentaneas
		if(!filtro_es_interrupcion_momentanea(x_m, duracion_interrupcion))
		{
			cant_interrupciones++;
			minutos_acumulados += duracion_interrupcion;

			if ((flag_tol_frecuencia) || (flag_tol_duracion_acumulada))
				continue;

			// Se supera la tolerancia por frecuencia primero
			if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_acumulados)))
			{
				flag_tol_frecuencia = 1;
				minutos_acumulados = 0;
				minutos_acumulados += duracion_interrupcion;
			}
			// Se supera la tolerancia por duración acumulada primero
			else if ((tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(!tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_acumulados)))
			{
				flag_tol_duracion_acumulada = 1;
				minutos_acumulados -= x_d;
			}
			// Se superan las tolerancias por frecuencia y por duración acumulada al mismo tiempo
			else if ((!tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(!tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_acumulados)))
			{
				flag_tol_frecuencia = 1;
				flag_tol_duracion_acumulada = 1;
				minutos_acumulados = 0;
				minutos_acumulados += duracion_interrupcion;
			}
		}
 	}

 	// Si el archivo está vacío, no hacemos nada.
 	if(consumo_tipico == 0) return;

 	// Procesamos al último cliente del archivo
	if((!flag_tol_frecuencia) && (!flag_tol_duracion_acumulada))
		minutos_acumulados = 0;

 	// Enviamos cliente y su multa correspondiente a la salida estandar
	enviar_a_salida_estandar(cliente_tmp, calculador_multa(consumo_tipico, x_p, minutos_acumulados));

	
	// Cerramos el archivo
	archivo_cerrar(fp);
}