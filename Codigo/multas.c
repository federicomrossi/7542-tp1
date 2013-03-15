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

void info_spliter(char *info, char *cliente/*, char *consumo_tipico, char *duracion_interrupcion*/)
{
	printf("%s", info);
	//printf("%s", cliente);
	strcpy(cliente, "hola");
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
 	char *cliente[100];
 	//char *consumo_tipico[100]; 
	//char *duracion_interrupcion[100];

 	// Apertura del archivo para lectura
 	fp = fopen(archivo, "r");

 	// Verificación de errores producidos
 	if (fp == NULL)
 	{
 		printf("Error al abrir archivo.");
 		// Se retorna 0 en todos los casos, a pesar de existir error.
 		exit(0);
 	}

 	while(fgets(buffer, 50, fp))
 	{
 		info_spliter(buffer, *cliente/*, &consumo_tipico, &duracion_interrupcion*/);
 	}

 	printf("%s", cliente);


	// char str[] ="- This, a sample string.";
	// char * pch;
	// printf ("Splitting string \"%s\" into tokens:\n",str);
	// pch = strtok (str," ,.-");
	// while (pch != NULL)
	// {
	// 	printf ("%s\n",pch);
	// 	pch = strtok (NULL, " ,.-");
	// }
		
	
		// Cerramos el archivo
	fclose(fp);


 	printf("\n\nx_m: %d\n", x_m);
 	printf("x_f: %d\n", x_f);
 	printf("x_d: %d\n", x_d);
 	printf("x_p: %d\n", x_p);
 	printf("archivo: %s\n", archivo);

    return 0;
}
