/* 

Dada una pila de enteros, escribir una función que determine si es piramidal. Una pila de enteros es
piramidal si cada elemento es menor a su elemento inferior (en el sentido que va desde el tope de la pila
hacia el otro extremo). La pila no debe ser modificada al terminar la función.

Indicar el orden del algoritmo propuesto.

*/

// Determina si una pila de enteros es piramidal.
// Pre: la pila fue creada y contiene enteros.
// Post: la pila no fue modificada.
bool es_pila_piramidal(pila_t* pila_enteros) {

	bool es_piramidal = true;
	pila_t* pila_aux = pila_crear(); // Despues la tengo que destruir, ya que justamente es auxiliar.

	while (!pila_esta_vacia(pila_enteros)) {
		void* dato_aux = pila_desapilar(pila_enteros);
		pila_apilar(pila_aux, dato_aux);
		int actual = *((int*) pila_ver_tope(pila_aux));
		int siguiente = *((int*) pila_ver_tope(pila_enteros));
		if (siguiente < actual) {
			es_piramidal = false;
			break;
		}
	}

	pilas_juntar(pila_enteros, pila_aux);
	pila_destruir(pila_aux); // OJO ACA, SIEMPRE DESTRUIR LA ESTRUCTURA AUXILIAR QUE HAYA UTILIZADO.

	return es_piramidal;
}

// Dada dos pilas, se apila el contenido de una sobre la otra.
// Pre: ambas pilas fueron creadas.
// Post: el contenido de una se incluye en la otra. Una pila queda vacía.
void pilas_juntar(pila_t* pila_llegada, pila_t* pila_salida) {

	while (!pila_esta_vacia(pila_salida)) {
		void* dato_aux = pila_desapilar(pila_salida);
		pila_apilar(pila_llegada, dato_aux);
	}
}

/* Orden del algoritmo:

es_pila_piramidal: tengo n veces O(1) siendo n la cantidad de enteros que tenga la pila. En el mejor caso, seria O(1) donde
el segundo elemento ya no cumple la condicion para que sea una pila piramidal. En el peor caso, recorreria toda la pila y seria O(n).

pilas_juntar: Se aplica lo mismo que es_pila_piramidal. En el mejor caso, tendría que reapilar un solo elemento --> O(1). Si tengo que
componer toda la pila de nuevo, sería O(n).

Total: O(n) + O(n) = 2O(n) = O(n).

*/


