/* 

Implementar la primitiva de la lista lista_t* lista_map(const lista t*, void* (*f)(void*))
que dada una lista enlazada devuelva una nueva lista. Esta nueva lista debe contener al re-
sultado de aplicar la función f pasada por parámetro a cada uno de los elementos de la lista
original sin usar iteradores.

Indicar el orden de la solución propuesta.

*/


// Dada una lista enlazada, devuelve una nueva lista que contiene los resultados
// de aplicar la funcion f a cada uno de los elementos de la lista original.
// Pre: la lista fue creada.
// Post: devuelve una nueva lista.
lista_t* lista_map(const lista_t* lista, void* (*f)(void*)) {

	lista_t* nueva_lista = lista_crear();
	nodo_t* actual = lista->primero;

	while (actual) {
		void* elemento = actual->dato;
		elemento = f(elemento);
		lista_insertar_ultimo(nueva_lista, elemento)
		actual = actual->siguiente;
	}

	return nueva_lista;
}

/* Orden de la solucion propuesta:
 * Debo recorrer toda la lista original --> O(n)
 * Aplicar funcion pasado por parametro es O(f) siendo f la funcion pasada por parametro.
 * Insertar cada elemento luego de aplicado la funcion es O(n).

 Total: O(n) x O(f) + O(n) = 2O(n) x O(f) = 2O(n x f) = O(n x O(f)), donde f es la funcion pasada por parametro.

 */