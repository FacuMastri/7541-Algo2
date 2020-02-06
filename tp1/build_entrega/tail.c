#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cola.h"

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Imprime el contenido almacenado en una cola.
// Pre: la cola fue creada.
// Post: la cola queda vacía.
void imprimir_lineas(cola_t* lineas_a_imprimir) {

	while (!cola_esta_vacia(lineas_a_imprimir)) {
		char* a_imprimir = cola_desencolar(lineas_a_imprimir);
		printf("%s", a_imprimir);
		free(a_imprimir);
	}
}

/* *****************************************************************
 *                    FUNCIONES A IMPLEMENTAR
 * *****************************************************************/

// Imprime las últimas lineas de entrada estandar.
// Pre: recibe la cantidad de líneas a leer.
int tail(size_t cant_lineas) {

	if (cant_lineas == 0) {
		return 0;
	}

	cola_t* lineas_a_imprimir = cola_crear();
	int lineas_leidas = 0;

	char* linea = NULL;
	size_t cantidad = 0;
	ssize_t leidos;

	while ((leidos = getline(&linea, &cantidad, stdin)) > 0) {
		if (lineas_leidas >= cant_lineas) {
			char* a_destruir = cola_desencolar(lineas_a_imprimir);
			free(a_destruir);
		}
		char* linea_aux = strdup(linea);
		cola_encolar(lineas_a_imprimir, linea_aux);
		lineas_leidas ++;
	}
	imprimir_lineas(lineas_a_imprimir);
	free(linea);
	cola_destruir(lineas_a_imprimir, NULL);

	return 0;
}

int main (int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	} 

	for (size_t i = 0; argv[1][i]; i++) {
		if (!isdigit(argv[1][i])) {
			fprintf(stderr, "%s\n", "Tipo de parametro incorrecto");
			return 1;
		}
	}
	size_t cant_lineas = atoi(argv[1]);

	return tail(cant_lineas);
}