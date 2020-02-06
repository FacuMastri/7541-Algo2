/* 

Implementar la primitiva void** cola_multiprimeros(const cola_t* cola, size_t k) que dada una cola
y un numero k, devuelva los primeros k elementos de la cola, en el mismo orden en el que habrian salido de la cola.
En caso de que la cola tenga menos de k elementos, rellenar con NULL. La cola debe quedar en el mismo estado
que al invocarse la primitiva. 

Indicar el orden de ejecucion del algoritmo. Justificar.

*/

// Devuelve los primeros k elementos de la cola.
// Pre: la cola fue creada, k es > 0.
// Post: devuelve los primeros k elementos de la cola en un vector.
void** cola_multiprimeros(const cola_t* cola, size_t k) {

	void** primeros_k_elementos = malloc(sizeof(void*) * k);

	if (!primeros_k_elementos) {
		return NULL;
	}

	size_t i = 0;
	nodo_t* actual = cola->primero;
	while (actual) {
		primeros_k_elementos[i] = actual->dato;
		actual = actual->siguiente;
		i ++;
	}

	while (i < k) {
		primeros_k_elementos[i] = NULL;
		i ++;
	}

	return primeros_k_elementos;
}

/* Orden del algoritmo:
 * O(k) siendo k los primeros k elemtnos de la cola, sin importar si la cola tenga o no esos k elementos.
 */
