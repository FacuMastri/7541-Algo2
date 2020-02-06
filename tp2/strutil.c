#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "strutil.h"

typedef struct string {
	char* contenido;
	size_t largo;
} string_t;

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Cuenta cantidad de ocurrencias del parámetro sep en el 
// string str.
// Pre: recibe un string y un separador entre cada substring.
// Post: devuelve la cantidad de ocurrencias del separador.
size_t contar_separadores(const char* str, char sep) {

 	size_t contador_sep = 0;
 	for (size_t i = 0; str[i]; i++) {
 		if (str[i] == sep) {
 			contador_sep ++;
 		}
 	}

 	return contador_sep;
}


// Calcula el largo total de un array de strings incluyendo los '\0'
// y el lugar ocupado por un futuro separador entre cada string.
// Pre: recibe un array de strings que puede o no estar allocado dinámicamente.
// Post: devuelve el largo total.
size_t calcular_largo_array_strings(char** strv) {

	size_t largo_total = 0;

	for (size_t i = 0; strv[i]; i++) {
		// El + 2 representa el '\0' y el separador a utilizar en join.
		largo_total += strlen(strv[i]) + 2;
	}

	return largo_total;
}

// Concatena dos strings mediante un separador.
// Pre: recibe ...
// @param str: string de destino.
// @param largo_str: largo del string de destino.
// @param src: string fuente.
// @param largo_src: largo del string fuente.
// @param sep: caracter separador entre cada string.
void strconcat(char* str, size_t largo_str, char* src, size_t largo_src, char sep) {

 	size_t nuevo_largo = largo_str + largo_src;
 	// (str + largo_str) me posiciona directamente al final de la cadena.
 	strcat(str + largo_str, src);
 	str[nuevo_largo] = sep;
 	str[nuevo_largo + 1] = '\0';
}

 /* *****************************************************************
 *                    FUNCIONES A IMPLEMENTAR
 * *****************************************************************/

char** split(const char* str, char sep) {

	if (sep == '\0') {
		return NULL;
	}

	size_t contador_sep = contar_separadores(str, sep);

	// Reservo memoria para el arreglo a devolver, sumandole 2 a contador_sep
	// para el último substring despues de la última ocurrencia del separador
	// y para el NULL del final.
	char** array = malloc(sizeof(char*) * (contador_sep + 2));

	if (!array) {
		return NULL;
	}

	size_t pos_string = 0;
	size_t pos_array = 0;
	for (size_t i = 0; i < contador_sep + 1; i++) {
		size_t cant_char = 0;
		while (str[pos_string + cant_char] && str[pos_string + cant_char] != sep) {
			cant_char ++;
		}
		// Reservo memoria para el substring con su largo + 1 para el '\0';
		char* sub_string = malloc(sizeof(char) * (cant_char + 1)); 
		if (!sub_string) {
			return NULL;
		}
		memcpy(sub_string, &str[pos_string], cant_char);
		sub_string[cant_char] = '\0';
		array[pos_array] = sub_string;
		// Agrego +1 para saltearme, en la próxima iteración, la posición donde
		// se encuentre el separador.
		pos_string += cant_char + 1; 
		pos_array ++;
	}
	array[pos_array] = NULL;

	return array;
}

char* join(char** strv, char sep) {

	if (strv == NULL || sep == '\0') {
		return NULL;
	}

	size_t capacidad_necesaria = calcular_largo_array_strings(strv);
	if (capacidad_necesaria == 0) {
		// Si la capacidad es 0, necesito pedir memoria para un
		// '\0' y así generar una cadena vacía.
		capacidad_necesaria = 1;
	}

	string_t string;
	string.contenido = malloc(capacidad_necesaria * sizeof(char));
	if (!string.contenido) {
		return NULL;
	}
	
	string.largo = 0;
	string.contenido[0] = '\0';
	for (size_t i = 0; strv[i]; i++) {
		size_t largo_substr = strlen(strv[i]);
		strconcat(string.contenido, string.largo, strv[i], largo_substr, sep);
		string.largo += largo_substr + 1; // El + 1 representa el separador.
	}
	// Reemplazo el último separador por un \0.
	if (string.largo > 0) {
		string.contenido[string.largo - 1] = '\0';
	}

	return string.contenido;
}

void free_strv(char* strv[]) {

	for (size_t i = 0; strv[i]; i++) {
		free(strv[i]);
	}
	free(strv);
}