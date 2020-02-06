/* Dada una lista enlazada implementada con las siguientes estructuras:

typedef struct nodo_lista {

	struct nodo_lista* proximo;
	void* dato;

} nodo_lista_t;

typedef struct lista {

	nodo_lista_t* primero;

} lista_t;

Escribir una primitiva que reciba una lista y devuelva el elemento que esté a k posiciones del final (el
ante-k-último), recorriendo la lista una sola vez. Considerar que k es siempre menor al largo de la
lista.

Por ejemplo, si se recibe la lista [ 1, 5, 10, 3, 6, 8 ], y k = 4, debe devolver 10.

Indicar el orden de complejidad de la función.

*/

// Devuelve el elemento que este a k posiciones del final.
// Pre: la lista fue creada y la posicion es siempre menor al largo de la lista y mayor a 0.
// Post: La lista queda enlazada de la misma manera que se recibio.
void* lista_k_posiciones(lista_t* lista, size_t k) {

	// La clave del algoritmo es mover K posiciones el puntero de referencia. Luego
	// mover ambos punteros (ref y main) hasta lograr que ref llegue al final de la lista. De esta manera,
	// se obtiene la posicion K desde el final.

	// Si la lista no fue creada, o no tiene elementos en ella devuelvo NULL.
	if (!lista->primero) {
		return NULL;
	}

	// Inicio ambos punteros desde el comienzo de la lista.
	nodo_lista_t* principal = lista->primero;
	nodo_lista_t* referencia = lista->primero;

	// Muevo el puntero de referencia k posiciones desde el comienzo.
	for (size_t i = 0; i < k; i++) { 
		referencia = referencia->proximo;
	}

	// Muevo ambos punteros hasta que el de referencia llegue al final (NULL)
	while (referencia) {
		principal = principal->proximo;
		referencia = referencia->proximo;
	}

	return principal->dato;
}

// Tambien podía usar lista_largo que me devuelve el length de la lista y hacer (largo - k +1) iteraciones desde el comienzo de la lista.





