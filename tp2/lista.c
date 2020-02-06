#include "lista.h"
#include <stdlib.h>

/* Definición del struct lista, nodo e iterador. */

typedef struct nodo {

	void* dato;
	struct nodo* siguiente;
} lista_nodo_t;

struct lista {

	lista_nodo_t* primero;
	lista_nodo_t* ultimo;
	size_t cantidad;
};

struct lista_iter {

	lista_t* lista;
    lista_nodo_t* anterior;
    lista_nodo_t* actual;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

// Crea un nodo.
// Post: devuelve un nodo con su dato almacenado.
 lista_nodo_t* nodo_crear(void* dato) {

 	lista_nodo_t* nuevo_nodo = malloc(sizeof(lista_nodo_t));

 	if (nuevo_nodo == NULL) {
 		return NULL;
 	}

 	nuevo_nodo->dato = dato;
 	nuevo_nodo->siguiente = NULL;

 	return nuevo_nodo;
 }

// Destruye un nodo.
// Pre: el nodo fue creado.
// Post: la memoria del nodo fue liberada.
 void nodo_destruir(lista_nodo_t* nodo) {
 	free(nodo);
 }

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA ENLAZADA
 * *****************************************************************/

lista_t* lista_crear() {

	lista_t* lista = malloc(sizeof(lista_t));

	if (!lista) {
		return NULL;
	}

	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->cantidad = 0;

	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {

	return lista->cantidad == 0 || !lista->primero || !lista->ultimo;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {

	if (!lista) {
		return false;
	}

	lista_nodo_t* nodo = nodo_crear(dato);

	if (!nodo) {
		return false;
	}

	if (lista_esta_vacia(lista)) {
		lista->ultimo = nodo;
	} else {
		nodo->siguiente = lista->primero;
	}
	lista->primero = nodo;
	lista->cantidad ++;

	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {

	lista_nodo_t* nodo = nodo_crear(dato);

	if (!nodo) {
		return false;
	}

	if (lista_esta_vacia(lista)) {
		lista->primero = nodo;
	} else {
		lista->ultimo->siguiente = nodo;
	}
	lista->ultimo = nodo;
	lista->cantidad ++;

	return true;
}

void* lista_borrar_primero(lista_t *lista) {

	if (lista_esta_vacia(lista)) {
		return NULL;
	}

	lista_nodo_t* primero = lista->primero;
	void* dato = lista->primero->dato;
	lista->primero = lista->primero->siguiente;
	nodo_destruir(primero);
	lista->cantidad --;

	if (lista_esta_vacia(lista)) {
		lista->ultimo = NULL;
	}

	return dato;
}

void* lista_ver_primero(const lista_t *lista) {

	if (lista_esta_vacia(lista)) {
		return NULL;
	}

	return lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista) {

	if (lista_esta_vacia(lista)) {
		return NULL;
	}

	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista) {

	return lista->cantidad;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {

	while (!lista_esta_vacia(lista)) {
		void* dato = lista_borrar_primero(lista);
		if (destruir_dato) {
			destruir_dato(dato);
		}
	}
	free(lista);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {

	if (!visitar || lista_esta_vacia(lista)) {
		return;
	}

	lista_nodo_t* actual = lista->primero;
	while (actual) {
		if (!visitar(actual->dato, extra)) {
			break;
		}
		actual = actual->siguiente;
	}
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t *lista) {

	lista_iter_t* iterador = malloc(sizeof(lista_iter_t));

	if (!iterador) {
		return NULL;
	}

	iterador->lista = lista;
	iterador->actual = lista->primero;
	iterador->anterior = NULL;

	return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter) {

	if (lista_iter_al_final(iter)) {
		return false;
	}

	iter->anterior = iter->actual;
	iter->actual = iter->actual->siguiente;

	return true;
}

void* lista_iter_ver_actual(const lista_iter_t *iter) {

	if (lista_iter_al_final(iter)) {
		return NULL;
	}

	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {

	return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter) {

	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {

	lista_nodo_t* nodo_a_insertar = nodo_crear(dato);

	if (!nodo_a_insertar) {
		return false;
	}
	nodo_a_insertar->siguiente = iter->actual;

	// Si estoy posicionado al final.
	if (lista_iter_al_final(iter)) {
		iter->lista->ultimo = nodo_a_insertar;
	}
	// Si estoy posicionado en cualquier otra posicion, cambio el anterior.
	if (iter->anterior) {
		iter->anterior->siguiente = nodo_a_insertar;
	// Si estoy posicionado al principio.
	} else {
		iter->lista->primero = nodo_a_insertar;
	}
	iter->actual = nodo_a_insertar;
	iter->lista->cantidad ++;

	return true;
}

void* lista_iter_borrar(lista_iter_t *iter) {

	if (lista_iter_al_final(iter)) {
		return NULL;
	}

	lista_nodo_t* nodo_a_destruir = iter->actual;
	void* dato = nodo_a_destruir->dato;
	iter->actual = nodo_a_destruir->siguiente;

	// Si estoy posicionado al principio.
	if (nodo_a_destruir == iter->lista->primero) {
		iter->lista->primero = nodo_a_destruir->siguiente;
	// Si estoy posicionado en cualquier otra posicion, cambio el anterior.
	} else {
		iter->anterior->siguiente = iter->actual;
	}
	// Si estoy posicionado al final.
	if (nodo_a_destruir == iter->lista->ultimo) {
		iter->lista->ultimo = iter->anterior;
	}

	nodo_destruir(nodo_a_destruir);
	iter->lista->cantidad --;

	return dato;
}


















