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
 	int consumo_tipico; 
	int duracion_interrupcion;
	int cant_interrupciones = 0;
	int minutos_acumulados = 0;
	int minutos_multables;

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
 	minutos_acumulados = 0;


 	while(fgets(buffer, 50, fp))
 	{
 		cliente = atoi(strtok(buffer, ":"));

		// Evaluamos si ha cambiado el cliente
		if((cliente != cliente_tmp) && (cliente_tmp !=0))
		{
			// Calculamos multa correspondiente al cliente (cliente_tmp)
			printf("cliente: %d\n", cliente_tmp);
			printf("Multa de %d\n", cliente_tmp);
			printf("Interrupciones: %d\n", cant_interrupciones);

			// Establecemos el nuevo cliente como actual
			cliente_tmp = cliente;

			// Re-inicializamos variables de procesamiento
		 	cant_interrupciones = 0;
		 	minutos_acumulados = 0;
		}

		// Sensa al primer cliente de la primer interrupcion
		if(cliente_tmp == 0)
			cliente_tmp = cliente;

		// Procesamos interrupcion del cliente
		

		cant_interrupciones++;
 	}

 	// Calculamos multa correspondiente al cliente (cliente_tmp)
	printf("cliente: %d\n", cliente_tmp);
	printf("Multa de %d\n", cliente_tmp);
	printf("Interrupciones: %d\n", cant_interrupciones);






 	// while(fgets(buffer, 50, fp))
 	// {
 	// 	// Separación de datos del registro
 	// 	cliente = atoi(strtok(buffer, ":"));

 	// 	// Detección de cambio de cliente en el archivo
 	// 	if ((cliente_tmp != cliente))
 	// 	{
 	// 		if((cliente_tmp != 0))
 	// 		{
 	// 			// MODULO RESULTADO MULTA
 	// 			if(flag_tolerancia_frecuencia)
 	// 				minutos_multables = minutos_acumulados;
 	// 			else
 	// 				minutos_multables = minutos_acumulados - x_d;

 	// 			printf("minutos multables: %d\n", minutos_multables);
 	// 			printf("consumo tipico: %d\n", consumo_tipico);
 	// 			printf("%d:%d\n", cliente_tmp, calculador_multa(consumo_tipico, x_p, minutos_multables));
 	// 			// FIN MODULO RESULTADO MULTA
 	// 		}

 	// 		// Re-inicializamos variables en cada cambio de cliente
 	// 		cliente_tmp = cliente;
 	// 		cant_interrupciones = 0;
		// 	minutos_acumulados = 0;

		// 	printf("\nCLIENTE %d\n-----------------------\n", cliente);
 	// 	}

 	// 	consumo_tipico = atoi(strtok(NULL, ":"));
 	// 	duracion_interrupcion = atoi(strtok(NULL, ":"));

 	// 	// Filtramos las interrupciones momentaneas
 	// 	if(!filtro_es_interrupcion_momentanea(x_m, duracion_interrupcion))
 	// 	{
 	// 		cant_interrupciones++;

 	// 		minutos_acumulados += duracion_interrupcion;

 	// 		if (!flag_tolerancia_frecuencia && 
 	// 			!filtro_tolerancia_interrupcion_por_frecuencia(x_f, cant_interrupciones) && 
 	// 			filtro_tolerancia_interrupcion_por_duracion_acumulada(x_d, minutos_acumulados))
 	// 		{
 	// 			flag_tolerancia_frecuencia = 1;
 	// 			minutos_acumulados = 0;
 	// 			minutos_acumulados += duracion_interrupcion;
 	// 		}
 	// 	}
 	// }
	
	// Cerramos el archivo
	fclose(fp);

    return 0;
}
