/*
Implementar la funcion void** pila_multipop(pila_t* pila, size_t n) que
devuelve un arreglo de tamaño n con los primeros n elementos de la pila
(completando con NULL si la cantidad de elementos de la pila es menor a n)

El arreglo a devolver debe tener en las primeras posiciones a los ultimos
elementos apilados, y debe eliminarlos de la pila.

Indicar el orden de la funcion implementada
*/

void** pila_multipop(pila_t* pila, size_t n) {

	void** array = malloc(sizeof(void*) * n);
	if (!array) {
		return NULL;
	}

	for (size_t i = 0; i < n; i++) {
		if (pila_esta_vacia(pila)) {
			array[i] = NULL;
		} else {
			void* dato = pila_desapilar(pila);
			array[i] = dato;
		}
	}

	return array;
}

// El orden de la funcion implementada es O(n) siendo n la cantidad de elementos
// pasados por parametros, ya que sin importar si la pila contiene n elementos, debo
// realizar operaciones de costo O(1) n veces