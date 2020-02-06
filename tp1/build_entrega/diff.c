#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Abre dos archivos.
// Pre: recibe dos archivos y sus respectivos nombres.
// Post: si no se pudo abrir algunos de ellos ya sea porque no existen o 
// no se tiene permiso de lectura, devolverá false.
bool abrir_archivos(FILE** archivo1, char* nombre_archivo1, FILE** archivo2, char* nombre_archivo2) {

	*archivo1 = fopen(nombre_archivo1, "r");

	if (*archivo1) {
		*archivo2 = fopen(nombre_archivo2, "r");
		if (!*archivo2) {
			fclose(*archivo1);
			fprintf(stderr, "%s\n", "Archivo erroneo");
			return false;
		}
		return true;
	}
	fprintf(stderr, "%s\n", "Archivo erroneo");

	return false;
}

// Cierra dos archivos.
void cerrar_archivos(FILE** archivo1, FILE** archivo2) {

	fclose(*archivo1);
	fclose(*archivo2);
}

// Imprime dos líneas, con formato, y el número de línea.
// Pre: recibe dos strings y un número de línea.
void imprimir_lineas(char* linea1, char* linea2, int numero_linea) {

	fprintf(stdout, "%s %d\n", "Diferencia en linea", numero_linea);
	fprintf(stdout, "< %s", linea1);
	fprintf(stdout, "%s\n", "---");
	fprintf(stdout, "> %s", linea2);
}

/* *****************************************************************
 *                    FUNCIONES A IMPLEMENTAR
 * *****************************************************************/

// Dado dos nombres de archivos, muestra las líneas diferentes.
// entre uno y otro archivo.
// Pre: recibe el nombre de los dos archivos a comparar.
// Post: devuelve 1 en caso de error, 0 si se realizó correctamente.
int diff(char* nombre_archivo1, char* nombre_archivo2) {

	if (strcmp(nombre_archivo1, nombre_archivo2) == 0) {
		return 0;
	}

	FILE* archivo1; 
	FILE* archivo2;

	if (!abrir_archivos(&archivo1, nombre_archivo1, &archivo2, nombre_archivo2)) {
		return 1;
	}

	char* linea_archivo1 = NULL;
	char* linea_archivo2 = NULL;
	size_t cantidad_linea_archivo1 = 0, cantidad_linea_archivo2 = 0;
	int numero_de_linea = 1;

	getline(&linea_archivo1, &cantidad_linea_archivo1, archivo1);
	getline(&linea_archivo2, &cantidad_linea_archivo2, archivo2);

	while (!feof(archivo1) && !feof(archivo2)) {
		if (strcmp(linea_archivo1, linea_archivo2) != 0) {
			imprimir_lineas(linea_archivo1, linea_archivo2, numero_de_linea);
		}
		numero_de_linea ++;
		getline(&linea_archivo1, &cantidad_linea_archivo1, archivo1);
		getline(&linea_archivo2, &cantidad_linea_archivo2, archivo2);
	}

	while (!feof(archivo1)) {
		imprimir_lineas(linea_archivo1, "\n", numero_de_linea);
		numero_de_linea ++;
		getline(&linea_archivo1, &cantidad_linea_archivo1, archivo1);
	}


	while (!feof(archivo2)) {
		imprimir_lineas("\n", linea_archivo2, numero_de_linea);
		numero_de_linea ++;
		getline(&linea_archivo2, &cantidad_linea_archivo2, archivo2);
	}

	free(linea_archivo1);
	free(linea_archivo2);
	cerrar_archivos(&archivo1, &archivo2);

	return 0;
}

int main (int argc, char* argv[]) {

	if (argc != 3) {
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}
	
	char* nombre_archivo1 = argv[1];
	char* nombre_archivo2 = argv[2];

	return diff(nombre_archivo1, nombre_archivo2);
}