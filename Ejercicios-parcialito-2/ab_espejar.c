/*
Implementar una primitiva void ab_espejar(ab_t* ab) que dado un árbol binario, devuelva el mismo
árbol espejado. Indicar y justificar el orden.
 */

ab_t* ab_espejar(ab_t* ab) {

	if (!ab) {
		return;
	}

	ab_t* arbol_espejado = crear_arbol(ab->raiz);
	if (!arbol_espejado) {
		return;
	}

	arbol_espejado->derecho = arbol_espejar(ab->izquierdo);
	arbol_espejado->izquierdo = arbol_espejar(ab->derecho);

	return arbol_espejado;
}