#define _POSIX_C_SOURCE 200809L // strdup
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "hash.h"

#define CAPACIDAD_INICIAL 1024
#define FACTOR_DE_CARGA 0.20
#define FACTOR_REDIMENSION 2
#define NO_ENCONTRADO -1

/* Definición del struct hash, hash_campo e iterador. */

typedef enum { OCUPADO, VACIO, BORRADO } estado_t;

typedef struct hash_campo {

	char* clave;
	void* dato;
	estado_t estado;
} hash_campo_t;

struct hash {

	size_t cantidad;
	size_t capacidad;
	hash_destruir_dato_t destruir_dato;
	hash_campo_t* tabla;
};

struct hash_iter {

	const hash_t* hash;
	size_t indice;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

/**
 * Crea una tabla de hash.
 * @param  capacidad: capacidad de la tabla.
 * @return tabla de hash creada.
 */
hash_campo_t* hash_crear_tabla(size_t capacidad) {

	hash_campo_t* tabla = malloc(sizeof(hash_campo_t) * capacidad);
	if (!tabla) {
		return NULL;
	}

	return tabla;
}

/**
 * Inicia cada campo de la tabla de hash.
 * @param hash: el hash fue creado.
 */
void hash_iniciar_tabla(hash_t* hash) {

	for (size_t i = 0; i < hash->capacidad; i++) {
		hash->tabla[i].clave = NULL;
		hash->tabla[i].dato = NULL;
		hash->tabla[i].estado = VACIO;
	}
}

/**
 * Función de hashing.
 */
static unsigned long funcion_hashing(const char* clave) {

	unsigned long hash = 0;
	int c;

	while ((c = *clave++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

/**
 * Redimensiona un hash.
 * @param  hash: el hash fue creado.
 * @param  nueva_capacidad: nueva capacidad del hash.
 * @return True o False según si se pudo redimensionar o no.
 */
bool hash_redimensionar(hash_t* hash, size_t nueva_capacidad) {

	hash_campo_t* tabla_aux = hash->tabla;
	size_t capacidad_aux = hash->capacidad;

	hash_campo_t* nueva_tabla = hash_crear_tabla(nueva_capacidad);
	if (!nueva_tabla) {
		return false;
	}

	hash->tabla = nueva_tabla;
	hash->capacidad = nueva_capacidad;
	hash->cantidad = 0;
	hash_iniciar_tabla(hash);
	for (size_t i = 0; i < capacidad_aux; i++) {
		if (tabla_aux[i].estado == OCUPADO) {
			hash_guardar(hash, tabla_aux[i].clave, tabla_aux[i].dato);
			// Libero la clave almacenada en la tabla antigua.
			free(tabla_aux[i].clave);
		}
	}

	free(tabla_aux);
	return true;
}

/**
 * Obtiene el índice de la clave dentro de un hash, o el índice de un
 * lugar vacío.
 * @param  hash: el hash fue creado.
 * @param  clave: clave a buscar.
 * @param  buscar_ocupado: true para campo ocupado, false en caso contrario.
 * @return índice correspondiente o -1 si no fue encontrada la clave.
 */
size_t hash_obtener_indice(const hash_t* hash, const char* clave, bool buscar_ocupado) {

	size_t indice = funcion_hashing(clave);

	for (size_t i = 0; i < hash->capacidad; i++) {
		indice = (indice + i * i) % hash->capacidad;
		if (buscar_ocupado && hash->tabla[indice].estado == OCUPADO && strcmp(clave, hash->tabla[indice].clave) == 0) {
			return indice;
		}
		if (!buscar_ocupado && hash->tabla[indice].estado != OCUPADO) {
			return indice;
		}
	}

	return NO_ENCONTRADO;
}

/**
 * Completa un campo dentro de un hash.
 * @param  hash: el hash fue creado.
 * @param  clave
 * @param  dato
 * @param  indice
 */
void hash_completar_campo(hash_t* hash, const char* clave, void* dato, size_t indice) {

	char* clave_aux = strdup(clave);
	hash->tabla[indice].clave = clave_aux;
	hash->tabla[indice].dato = dato;
	hash->tabla[indice].estado = OCUPADO;
	hash->cantidad++;
}

/**
 * Libera la memoria de la clave, y destruye el dato de un campo.
 * @param clave: la clave fue allocada dinamicamente.
 * @param dato
 * @param destruir_dato
 */
void hash_destruir_campo(char* clave, void* dato, hash_destruir_dato_t destruir_dato) {

	free(clave);
	if (destruir_dato) {
		destruir_dato(dato);
	}
}

/**
 * Actualiza el dato de un campo de un hash.
 * @param hash: el hash fue creado.
 * @param dato
 * @param indice
 */
void hash_actualizar_campo(hash_t* hash, void* dato, size_t indice) {

	if (hash->destruir_dato) {
		hash->destruir_dato(hash->tabla[indice].dato);
	}
	hash->tabla[indice].dato = dato;
}

/**
 * Avanza el iterador hasta el siguiente campo.
 * @param  iter: el iterador fue creado.
 * @return True si se logró posicionar en un campo ocupado o en
 * el final del hash, False en caso contrario.
 */
bool hash_iter_actualizar_siguiente_posicion(hash_iter_t* iter) {

	for (; iter->indice <= iter->hash->capacidad; iter->indice++) {
		if (iter->indice == iter->hash->capacidad || iter->hash->tabla[iter->indice].estado == OCUPADO) {
			return true;
		}
	}

	return false;
}

/* *****************************************************************
 *                      PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {

	hash_t* hash = malloc(sizeof(hash_t));
	if (!hash) {
		return NULL;
	}

	hash->tabla = hash_crear_tabla(CAPACIDAD_INICIAL);
	if (!hash->tabla) {
		free(hash);
		return NULL;
	}

	hash->cantidad = 0;
	hash->capacidad = CAPACIDAD_INICIAL;
	hash->destruir_dato = destruir_dato;
	hash_iniciar_tabla(hash);

	return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {

	if ((float) hash->cantidad / (float) hash->capacidad >= (float) FACTOR_DE_CARGA) {
		if(!hash_redimensionar(hash, hash->capacidad * FACTOR_REDIMENSION)) {
			return false;
		}
	}

	size_t indice = funcion_hashing(clave) % hash->capacidad;

	if (hash->tabla[indice].estado != OCUPADO) {
		hash_completar_campo(hash, clave, dato, indice);
	} else if (hash->tabla[indice].estado == OCUPADO && strcmp(hash->tabla[indice].clave, clave) == 0) {
		hash_actualizar_campo(hash, dato, indice);
	} else {
		indice = hash_obtener_indice(hash, clave, false);
		hash_completar_campo(hash, clave, dato, indice);
	}

	return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {

	if (!hash_pertenece(hash, clave)) {
		return NULL;
	}

	size_t indice = hash_obtener_indice(hash, clave, true);
	void* dato_aux = hash->tabla[indice].dato;
	hash->tabla[indice].dato = NULL;
	hash->tabla[indice].estado = VACIO;
	free(hash->tabla[indice].clave);
	hash->cantidad--;

	return dato_aux;
}

void *hash_obtener(const hash_t *hash, const char *clave) {

	if (!hash_pertenece(hash, clave)) {
		return NULL;
	}

	size_t indice = hash_obtener_indice(hash, clave, true);

	return hash->tabla[indice].dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {

	if (hash_obtener_indice(hash, clave, true) == NO_ENCONTRADO) {
		return false;
	}

	return true;
}

size_t hash_cantidad(const hash_t *hash) {

	return hash->cantidad;
}

void hash_destruir(hash_t *hash) {

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i].estado == OCUPADO) {
			hash_destruir_campo(hash->tabla[i].clave, hash->tabla[i].dato, hash->destruir_dato);
		}
	}
	free(hash->tabla);
	free(hash);
}

/* *****************************************************************
 *                   PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {

	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if (!iter) {
		return NULL;
	}

	iter->hash = hash;
	iter->indice = 0;
	if (!hash_iter_actualizar_siguiente_posicion(iter)) {
		iter->indice = iter->hash->capacidad;
	}

	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {

	if (hash_iter_al_final(iter)) {
		return false;
	}

	iter->indice++;
	return hash_iter_actualizar_siguiente_posicion(iter);
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {

	if (hash_iter_al_final(iter)) {
		return NULL;
	}

	return iter->hash->tabla[iter->indice].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {

	return iter->hash->capacidad == iter->indice;
}

void hash_iter_destruir(hash_iter_t* iter) {

	free(iter);
}