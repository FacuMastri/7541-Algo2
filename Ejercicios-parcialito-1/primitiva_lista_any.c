/*
Dada una lista enlazada definida con las siguientes estructuras:

typedef struct nodo_lista {
	struct nodo_lista* prox;
	void* dato;
} nodo_lista_t

typedef struct lista {
	nodo_lista_t* prim
} lista_t:

Implementar en C la primitiva bool lista_any(const lista_t* lista, bool(*f) (void*))
que devuelve True solo si la funcion f pasada por parametro devuelve True para alguno
de los elementos de la lista

Indicar el orden de la funcion implementada
*/

bool lista_any(const lista_t* lista, bool (*f) (void*)) {

	nodo_lista_t* actual = lista->prim;

	while (actual) {
		if (f(actual->dato)) {
			return true;
		}
		actual = actual->prox
	}

	return false;
}

// Orden de la funcion implementada: O(n) siendo n la cantidad de elementos que posea
// la lista ya que, en el peor caso, debo recorrerla toda para que la funcion f pasada por
// parametro devuelva True para algun elemento de la lista. El resto de las operaciones aplicadas
// cuestan O(1)