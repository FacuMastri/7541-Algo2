/*

Implementar una primitiva para el ABB, que reciba el ABB y devuelva una lista con las claves del mismo
ordenadas tal que si insertáramos las claves en un ABB vacío (con la misma función de comparación),
dicho ABB tendría la misma estructura que el árbol original. ¿Qué tipo de recorrido utilizaste?

Indicar el orden de la primitiva. Justificar.

*/

void recur_claves_ordenadas(abb_t* arbol, lista_t* lista) {

	// Condicion base de la recursion. CASI SIEMPRE ES LA MISMA.
	if (!arbol) {
		return NULL;
	}

	// Hago la llamada de forma de pre-order ya que me permite
	// reconstruir el arbol de la misma forma.
	// Pre-order: Accion-->Llamo para izquierda-->Llamo para derecha.
	lista_insertar_ultimo(arbol->clave, lista); // 
	recur_claves_ordenadas(arbol->izquierda lista);
	recur_claves_ordenadas(arbol->derecha, lista);
}

lista_t* abb_claves_ordenadas(abb_t* arbol) {

	lista_t* claves_ordenadas = lista_crear();
	if (!claves_ordenadas) {
		return NULL;
	}

	recur_claves_ordenadas(arbol, claves_ordenadas);

	return claves_ordenadas;
}

// El tipo de recorrido utilizado es pre-order.
// Orden de la primitiva: O(n) siendo 'n' la cantidad de nodos en el arbol
// ya que siempre tengo que recorrer todo el arbol para conseguir todas las claves.