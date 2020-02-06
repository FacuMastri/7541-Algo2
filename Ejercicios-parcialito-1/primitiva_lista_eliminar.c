/* 

Dada una lista enlazada, implementar una primitiva (lado Alan) que elimine todas las ocurrencias
del dato pasado por parametro y devuelva True si encontró al menos 1, o False si no encontro ninguno.

*/

// Elimina todas las ocurrencias del valor dentro de una lista. Devuelve
// True si encontró al menos 1 ocurrencia, False en caso contrario.
// Pre: la lista fue creada.
// Post: todas las ocurrencias del valor dentro de la lista fueron eliminadas.
bool lista_eliminar(lista_t* lista, void* valor) {

	bool encontro = false;
	nodo_t* anterior = NULL;
	nodo_t* actual = lista->primero;

	while (actual) {
		// Esto si lo puedo hacer, puedo comparar direcciones de memoria desde los punteros sin castear.
		if (actual->dato == valor) { // Si encontré el valor buscado, debo modificar las referencias.
			nodo_t* siguiente = actual->proximo;
			if (!anterior) { // Caso donde el primer nodo es donde tenga el valor a buscar.
				lista->primero = siguiente;
			} else { // Caso donde no sea el primer nodo.
				anterior->proximo = siguiente;
			}
			encontro = true;
			free(actual); // Destruyo el nodo, NO el dato ya que si hago eso estoy destruyendo una direccion de memoria que puede estar almacenada en otro nodo. Además, estaría rompiendo el dato al usuario.
			actual = siguiente;
		} else { // Caso donde no haya encontrado el valor buscado, sigo iterando normalmente.
			anterior = actual;
			actual = actual->proximo;
		}
	}

	return encontro;
}