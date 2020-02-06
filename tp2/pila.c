#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {

    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

#define CAPACIDAD_INICIAL 50
#define FACTOR_REDIMENSION 2
#define FACTOR_CAPACIDAD 4

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Devuelve True o False según si se pudo redimensionar o no la pila.
// Pre: la pila fue creada.
// Post: la pila posee una nueva capacidad.
bool pila_redimensionar(pila_t* pila, size_t nueva_capacidad) {

	void** datos_aux = realloc(pila->datos, nueva_capacidad * sizeof(void*));

	if (datos_aux == NULL) {
		return false;
	}
	pila->datos = datos_aux;
	pila->capacidad = nueva_capacidad;

	return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void) {

	pila_t* pila = malloc(sizeof(pila_t));

	if (pila == NULL) {
		return NULL;
	}
	pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));

	if (pila->datos == NULL) {
		free(pila);
		return NULL;
	}
	pila->capacidad = CAPACIDAD_INICIAL;
	pila->cantidad = 0;

	return pila;
}

void pila_destruir(pila_t *pila) {

	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {

	return (pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, void* valor) {

	if (pila == NULL) {
		return false;
	}

	if (pila->cantidad == pila->capacidad) {
		if (!pila_redimensionar(pila, pila->capacidad * FACTOR_REDIMENSION)) {
			return false;
		}
	}

	pila->datos[pila->cantidad ++] = valor;
	return true;
}

void* pila_ver_tope(const pila_t *pila) {

	if (pila == NULL || pila_esta_vacia(pila)) {
		return NULL;
	}

	return pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila) {

	if (pila == NULL || pila_esta_vacia(pila)) {
		return NULL;
	}

	if (pila->cantidad == (pila->capacidad / FACTOR_CAPACIDAD)) {
		pila_redimensionar(pila, pila->capacidad / FACTOR_REDIMENSION);
	}

	void* dato_aux = pila_ver_tope(pila);
	pila->cantidad --;

	return dato_aux;
}