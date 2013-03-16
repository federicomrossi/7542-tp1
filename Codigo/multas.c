#include "multas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtros.h"


/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

int calculador_multa(int consumo_tipico, int x_p, int minutos_multables)
{
	return (consumo_tipico * x_p * minutos_multables);
}



/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char **argv)
{
 	// Toma de parámetros
 	int x_m = atoi(argv[1]);
 	int x_f = atoi(argv[2]);
 	int x_d = atoi(argv[3]);
 	int x_p = atoi(argv[4]);
 	char *archivo = argv[5];

 	FILE *fp;
 	char buffer[100];
 	int cliente, cliente_tmp = 0;
 	int consumo_tipico = 0; 
	int duracion_interrupcion;
	int cant_interrupciones = 0;
	int minutos_multables = 0;

	// Flags para deteccion de tolerancias superadas
	_Bool flag_tol_frecuencia = 0;
	_Bool flag_tol_duracion_acumulada = 0;

 	// Apertura del archivo para lectura
 	fp = fopen(archivo, "r");

 	// Verificación de errores producidos
 	if (fp == NULL)
 	{
 		printf("Error al abrir archivo.");
 		// Se retorna 0 en todos los casos, a pesar de existir error.
 		exit(0);
 	}

 	// inicializamos variables de procesamiento
 	cant_interrupciones = 0;
 	minutos_multables = 0;


 	while(fgets(buffer, 50, fp))
 	{
 		cliente = atoi(strtok(buffer, ":"));

		// Evaluamos si ha cambiado el cliente
		if((cliente != cliente_tmp) && (cliente_tmp !=0))
		{
			// Calculamos multa correspondiente al cliente (cliente_tmp)
			printf("Cliente: %d\n", cliente_tmp);
			printf("Interrupciones: %d\n", cant_interrupciones);
			printf("Acumulado: %d\n", minutos_multables);
			printf("MULTA: %d\n\n", calculador_multa(consumo_tipico, x_p, minutos_multables));

			// Establecemos el nuevo cliente como actual
			cliente_tmp = cliente;

			// Re-inicializamos variables de procesamiento
			flag_tol_frecuencia = 0;
			flag_tol_duracion_acumulada = 0;
		 	cant_interrupciones = 0;
		 	minutos_multables = 0;
		}

		// Sensa al primer cliente de la primer interrupcion
		if(cliente_tmp == 0)
			cliente_tmp = cliente;


		// Procesamos interrupcion del cliente
		consumo_tipico = atoi(strtok(NULL, ":"));
 		duracion_interrupcion = atoi(strtok(NULL, ":"));
		
		// Filtramos las interrupciones momentaneas
		if(!filtro_es_interrupcion_momentanea(x_m, duracion_interrupcion))
		{
			cant_interrupciones++;
			minutos_multables += duracion_interrupcion;

			if ((flag_tol_frecuencia) || (flag_tol_duracion_acumulada))
				continue;

			// Se supera la tolerancia por frecuencia primero
			if ((!filtro_tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(filtro_tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_multables)))
			{
				flag_tol_frecuencia = 1;
				minutos_multables = 0;
				minutos_multables += duracion_interrupcion;
				printf("Se supero TOLERANCIA POR FRECUENCIA\n");
			}
			// Se supera la tolerancia por duración acumulada primero
			else if ((filtro_tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(!filtro_tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_multables)))
			{
				flag_tol_duracion_acumulada = 1;
				minutos_multables -= x_d;
				printf("Se supero TOLERANCIA POR DURACION ACUMULADA\n");
			}
			// Se superan las tolerancias por frecuencia y por duración
			// acumulada al mismo tiempo
			else if ((!filtro_tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones)) &&
				(!filtro_tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_multables)))
			{
				flag_tol_frecuencia = 1;
				flag_tol_duracion_acumulada = 1;
				minutos_multables = 0;
				minutos_multables += duracion_interrupcion;
				printf("Se superaron AMBAS TOLERANCIAS A LA VEZ\n");
			}
		}
 	}

 	// Si el archivo está vacío, retornamos.
 	if(consumo_tipico == 0) exit(0);

 	// Procesamos al último cliente del archivo

	
	// Calculamos multa correspondiente al cliente (cliente_tmp)
	printf("Cliente: %d\n", cliente_tmp);
	printf("Interrupciones: %d\n", cant_interrupciones);
	printf("Acumulado: %d\n", minutos_multables);
	printf("MULTA: %d\n\n", calculador_multa(consumo_tipico, x_p, minutos_multables));

	
	// Cerramos el archivo
	fclose(fp);

    return 0;
}
