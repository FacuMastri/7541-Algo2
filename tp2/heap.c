#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>

#define CAPACIDAD_INICIAL 1024
#define FACTOR_REDIMENSION 2
#define FACTOR_CAPACIDAD 4

/* Definición del struct heap */

struct heap {

	void** datos;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t comparar_dato;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

/**
 * Redimensiona un heap.
 * @param  heap: el heap fue creado
 * @param  nueva_capacidad
 * @return true o false según si se pudo redimensionar o no. Si se
 * logró dimensionar, el heap tendrá una nueva capacidad.
 */
bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad) {

	void** datos_aux = realloc(heap->datos, nueva_capacidad * sizeof(void*));

	if (!datos_aux) {
		return false;
	}
	heap->datos = datos_aux;
	heap->capacidad = nueva_capacidad;

	return true;
}

/**
 * Función de swap para punteros genericos.
 * @param un_dato
 * @param otro_dato
 */
void swap(void** un_dato, void** otro_dato) {

	void* aux = *un_dato;
	*un_dato = *otro_dato;
	*otro_dato = aux;
}

/**
 * Obtiene la posicion del padre de un hijo.
 * @param  pos_hijo
 * @return la posicion del padre.
 */
size_t heap_obtener_pos_padre(size_t pos_hijo) {

	return (pos_hijo - 1) / 2;
}

/**
 * Obtiene la posicion del hijo derecho de un padre.
 * @param  pos_padre
 * @return la posicion del hijo derecho.
 */
size_t heap_obtener_pos_hijo_der(size_t pos_padre) {

	return 2 * pos_padre + 2;
}

/**
 * Obtiene la posicion del hijo izquierdo de un padre.
 * @param  pos_padre
 * @return la posicion del hijo izquierdo.
 */
size_t heap_obtener_pos_hijo_izq(size_t pos_padre) {

	return 2 * pos_padre + 1;
}

/**
 * Funcion de upheap. Mueve el dato previamente insertado hacia la
 * ubicacion correcta dentro del heap.
 * @param datos: arreglo de punteros genericos.
 * @param pos_hijo      
 * @param comparar_dato: funcion de comparacion de datos.
 */
void heap_upheap(void** datos, size_t pos_hijo, cmp_func_t comparar_dato) {

	if (pos_hijo == 0) {
		return;
	}

	size_t pos_padre = heap_obtener_pos_padre(pos_hijo);

	if (comparar_dato(datos[pos_hijo], datos[pos_padre]) < 0) {
		return;
	}

	swap(&datos[pos_hijo], &datos[pos_padre]);
	heap_upheap(datos, pos_padre, comparar_dato);
}

/**
 * Funcion de downheap. Permite mantener la propiedad del heap
 * moviendo cada elemento hacia la ubicacion correcta.
 * @param datos: arreglo de punteros genericos.
 * @param pos_padre
 * @param cantidad: cantidad de elementos en datos.
 * @param comparar_dato: funcion de comparacion de datos.
 */
void heap_downheap(void** datos, size_t pos_padre, size_t cantidad, cmp_func_t comparar_dato) {

	if (pos_padre >= cantidad) {
		return;
	}

	size_t pos_hijo_izquierdo = heap_obtener_pos_hijo_izq(pos_padre);
	size_t pos_hijo_derecho = heap_obtener_pos_hijo_der(pos_padre);
	size_t pos_max = pos_padre;

	if (pos_hijo_izquierdo < cantidad && comparar_dato(datos[pos_hijo_izquierdo], datos[pos_max]) > 0) {
		pos_max = pos_hijo_izquierdo;
	}
	if (pos_hijo_derecho < cantidad && comparar_dato(datos[pos_hijo_derecho], datos[pos_max]) > 0) {
		pos_max = pos_hijo_derecho;
	}
	if (pos_padre != pos_max) {
		swap(&datos[pos_padre], &datos[pos_max]);
		heap_downheap(datos, pos_max, cantidad, comparar_dato);
	}
}

/**
 * Funcion de heapify. Dado un arreglo de punteros genericos permite
 * generarle la condicion de heap empezando desde las hojas.
 * @param datos: arreglo de punteros genericos.
 * @param cantidad: cantidad de elementos en datos.
 * @param comparar_dato: funcion de comparacion de datos.
 */
void heap_heapify(void** datos, size_t cantidad, cmp_func_t comparar_dato) {

	for (size_t i = cantidad; i > 0; i--) {
		heap_downheap(datos, i - 1, cantidad, comparar_dato);
	}
}

/* *****************************************************************
 *                    		HEAP SORT
 * *****************************************************************/

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {

	heap_heapify(elementos, cant, cmp);

	for (; cant > 0;) {
		swap(&elementos[0], &elementos[cant - 1]);
		cant--;
		heap_downheap(elementos, 0, cant, cmp);
	}
}

/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {

	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) {
		return NULL;
	}

	void** datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));
	if (!datos) {
		free(heap);
		return NULL;
	}

	heap->capacidad = CAPACIDAD_INICIAL;
	heap->cantidad = 0;
	heap->datos = datos;
	heap->comparar_dato = cmp;

	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {

	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) {
		return NULL;
	}

	heap->datos = malloc(sizeof(void*) * n);
	if (!heap->datos) {
		free(heap);
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		heap->datos[i] = arreglo[i];
	}

	heap_heapify(heap->datos, n, cmp);

	heap->comparar_dato = cmp;
	heap->cantidad = n;
	heap->capacidad = n;

	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {

	if (destruir_elemento) {
		for (size_t i = 0; i < heap->cantidad; i++) {
			destruir_elemento(heap->datos[i]);
		}
	}
	
	free(heap->datos);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap) {

	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {

	return heap_cantidad(heap) == 0;
}

bool heap_encolar(heap_t *heap, void *elem) {

	if (heap->cantidad == heap->capacidad) {
		if (!heap_redimensionar(heap, heap->capacidad * FACTOR_REDIMENSION))
			return false;
	}

	heap->datos[heap->cantidad] = elem;
	heap_upheap(heap->datos, heap->cantidad, heap->comparar_dato);
	heap->cantidad++;

	return true;
}

void *heap_ver_max(const heap_t *heap) {

	if (heap_esta_vacio(heap)) {
		return NULL;
	}

	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap) {

	if (heap_esta_vacio(heap)) {
		return NULL;
	}

	void* dato = heap_ver_max(heap);
	swap(&heap->datos[0], &heap->datos[heap->cantidad - 1]);
	heap->cantidad--;

	if (heap->cantidad == (heap->capacidad / FACTOR_CAPACIDAD)) {
		heap_redimensionar(heap, heap->capacidad / FACTOR_REDIMENSION);
	}

	heap_downheap(heap->datos, 0, heap->cantidad, heap->comparar_dato);

	return dato;
}