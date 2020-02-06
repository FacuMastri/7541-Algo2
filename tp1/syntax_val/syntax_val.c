#define _POSIX_C_SOURCE 200809L
#define PARENTESIS_APERTURA '('
#define PARENTESIS_CLAUSURA ')'
#define LLAVE_APERTURA '{'
#define LLAVE_CLAUSURA '}'
#define CORCHETE_APERTURA '['
#define CORCHETE_CLAUSURA ']'
#define COMILLA_SIMPLE '\''

#include "pila.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Dado dos caracteres, verifica si ambos son los correspondientes
// de apertura y clausura de paréntesis, llaves o corchetes.
// Pre: recibe dos caracteres.
// Post: devuelve true o false según corresponda.
bool es_par_coincidente(char caracter1, char caracter2) {

	if (caracter1 == PARENTESIS_APERTURA && caracter2 == PARENTESIS_CLAUSURA) {
		return true;
	} else if (caracter1 == LLAVE_APERTURA && caracter2 == LLAVE_CLAUSURA) {
		return true;
	} else if (caracter1 == CORCHETE_APERTURA && caracter2 == CORCHETE_CLAUSURA) {
		return true;
	} else {
		return false;
	}
}

// Verifica si un caracter es el correspondiente de apertura
// de un paréntesis, una llave o  un corchete.
// Pre: recibe un caracter.
// Post: devuelve true o false según corresponda.
bool es_caracter_de_apertura(char caracter) {

	return caracter == LLAVE_APERTURA || caracter == PARENTESIS_APERTURA || caracter == CORCHETE_APERTURA;
}

// Verifica si un caracter es el correspondiente de clausura
// de un paréntesis, una llave o  un corchete.
// Pre: recibe un caracter.
// Post: devuelve true o false según corresponda.
bool es_caracter_de_clausura(char caracter) {

	return caracter == LLAVE_CLAUSURA || caracter == PARENTESIS_CLAUSURA || caracter == CORCHETE_CLAUSURA;
}

/* *****************************************************************
 *                    FUNCIONES A IMPLEMENTAR
 * *****************************************************************/

// Realiza validaciones a lineas que contengan secuencias de paréntesis,
// llaves o corchetes. En caso de encontrarse encerradas dentro de comillas
// simples las cadenas, no se consideran para determinar si la secuencia
// se encuentra balanceada.
int syntax_validation() {

	pila_t* pila = pila_crear();
	char* linea = NULL;
	size_t cantidad = 0;
	ssize_t leidos;

	while ((leidos = getline(&linea, &cantidad, stdin)) > 0) {
		bool hay_error = false;
		bool hay_comilla = false;
		for (size_t i = 0; linea[i]; i++) {
			if (!hay_comilla && linea[i] == COMILLA_SIMPLE) {
				hay_comilla = true;
			} else if (hay_comilla && linea[i] == COMILLA_SIMPLE) {
				hay_comilla = false;
			} else if (!hay_comilla && es_caracter_de_apertura(linea[i])) {
				pila_apilar(pila, &linea[i]);
			} else if (!hay_comilla && es_caracter_de_clausura(linea[i])) {
				if (pila_esta_vacia(pila) || !es_par_coincidente(*(char*) pila_desapilar(pila), linea[i])) {
					hay_error = true;
					break;
				}
			}
		}
		if (hay_error || hay_comilla || !pila_esta_vacia(pila)) {
			fprintf(stdout, "%s\n", "ERROR");
			while (!pila_esta_vacia(pila)) { // Desapilo para la siguiente iteración.
				pila_desapilar(pila);
			}
		} else {
			fprintf(stdout, "%s\n", "OK");
		}
	}
	free(linea);
	pila_destruir(pila);

	return 0;
}

int main() {

	return syntax_validation();
}