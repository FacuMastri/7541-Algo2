#include "cola.h"
#include <stdlib.h>

/* Definición del struct cola y nodo proporcionado por la cátedra.
 */

typedef struct nodo {

	void* dato;
	struct nodo* siguiente;
} cola_nodo_t;

struct cola {

	cola_nodo_t* primero;
	cola_nodo_t* ultimo;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Crea un nodo.
// Post: devuelve un nodo con su dato almacenado.
 cola_nodo_t* nodo_crear(void* valor) {

 	cola_nodo_t* nuevo_nodo = malloc(sizeof(cola_nodo_t));

 	if (nuevo_nodo == NULL) {
 		return NULL;
 	}

 	nuevo_nodo->dato = valor;
 	nuevo_nodo->siguiente = NULL;

 	return nuevo_nodo;
 }

// Destruye un nodo.
// Pre: el nodo fue creado.
// Post: la memoria del nodo fue liberada.
 void nodo_destruir(cola_nodo_t* nodo) {
 	free(nodo);
 }

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {

	cola_t* cola = malloc(sizeof(cola_t));

	if (cola == NULL) {
		return NULL;
	}

	cola->primero = NULL;
	cola->ultimo = NULL;

	return cola;
}

bool cola_esta_vacia(const cola_t *cola) {

	return (cola->primero == NULL && cola->ultimo == NULL);
}

bool cola_encolar(cola_t *cola, void* valor) {

	cola_nodo_t* nuevo_nodo = nodo_crear(valor);

	if (nuevo_nodo == NULL) {
		return false;
	}

	if (cola_esta_vacia(cola)) {
		cola->primero = nuevo_nodo;
	} else {
		cola->ultimo->siguiente = nuevo_nodo;
	}
	cola->ultimo = nuevo_nodo;

	return true;
}

void* cola_ver_primero(const cola_t *cola) {

	if (cola_esta_vacia(cola)) {
		return NULL;
	} else {
		return cola->primero->dato;
	}
}

void* cola_desencolar(cola_t *cola) {

	if (cola_esta_vacia(cola)) {
		return NULL;
	}

	void* dato_aux = cola_ver_primero(cola);
	cola_nodo_t* nodo_aux = cola->primero;
	cola->primero = cola->primero->siguiente;
	if (!cola->primero) {
		cola->ultimo = NULL;
	}
	nodo_destruir(nodo_aux);

	return dato_aux;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {

	while(!cola_esta_vacia(cola)) {
		void* dato = cola_desencolar(cola);
		if(destruir_dato) {
			destruir_dato(dato);
		}
	}
	free(cola);
}