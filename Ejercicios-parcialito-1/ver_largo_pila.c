/* 

Se pide implementar una función recursiva que calcule el largo de una pila sin utilizar
estructuras auxiliares ni acceder a su estructura interna (que no sabemos cuál es). El prototipo
de la función es:

size t largo pila(pila t *pila);

Se puede llamar a cualquier primitiva de la pila, incluyendo aquellas que la modifiquen,
pero siempre la pila debe quedar en su estado original al terminar la ejecución de la función.

*/

// Devuelve el largo de una pila.
// Pre: la pila fue creada.
// Post: la pila no sufre modificaciones al terminar la funcion.
size_t largo_pila(pila_t* pila) {

	size_t largo = 0;

	// Caso base: si la pila esta vacia, devuelvo el largo.
	if (pila_esta_vacia(pila)) {
		return largo;
	} else {
		void* elemento = pila_desapilar(pila);
		largo = largo_pila(pila);
		pila_apilar(pila, elemento);
		largo ++;
	}

	return largo;
}