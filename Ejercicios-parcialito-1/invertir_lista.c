/*

Escribir una primitiva que invierta el contenido de una Lista Enlazada sin usar ninguna
estructura auxiliar.

*/

// Invierte el contenido de una Lista Enlazada.
// Pre: la lista fue creada.
void invertir_lista(lista_t* lista) {

	nodo_lista_t* anterior = NULL;
	nodo_lista_t* actual = lista->primero;
	nodo_lista_t* siguiente = NULL;

	while (actual) {
		// Almaceno el siguiente nodo.
		siguiente = actual->siguiente; 
		// Aca es donde se da vuelta el linkeo. El siguiente de mi
		// actual apunta al anterior
		actual->siguiente = anterior;
		// Avanzo anterior y actual un paso.
		anterior = actual;
		actual = siguiente;
	}
}