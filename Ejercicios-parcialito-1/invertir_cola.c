/* 
 
a) Implementar la función void invertir cola(cola t* cola), que invierte el orden
de sus elementos
.
b) Indicar el orden de complejidad de la función implementada.

*/

// Invierte el orden de los elementos de una cola.
// Pre: la cola fue creada.
// Post: la cola tiene el orden de los elementos invertidos.
void invertir_cola(cola_t* cola) {

	pila_t* pila_aux = pila_crear();

	while (!cola_esta_vacia(cola)) {
		void* dato_aux = cola_desencolar(cola);
		pila_apilar(pila_aux, dato_aux);
	}

	while (!pila_esta_vacia(pila_aux)) {
		void* dato_aux = pila_desapilar(pila_aux);
		cola_encolar(cola, dato_aux);
	}

	pila_destruir(pila_aux);
}

/* Desencolar todos los elementos y apilarlos en una pila --> O(n) donde n es la cantidad de elementos de la cola.
 * Desapilar todos los elementos y encolarlos de vuelta en la cola --> O(n) donde n es la cantidad de elementos de la pila.
 * Total: O(n) + O(n) = O(n + n) = O(2n) = 2O(n) = O(n).
 */