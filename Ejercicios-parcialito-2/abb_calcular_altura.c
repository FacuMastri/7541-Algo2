/* Calcular altura de un arbol binario de busqueda */

size_t abb_calcular_altura(ab_t* arbol) {

	if (!arbol) {
		return 0;
	}

	return max(abb_calcular_altura(arbol->izquierdo), abb_calcular_altura(arbol->derecho)) + 1
}