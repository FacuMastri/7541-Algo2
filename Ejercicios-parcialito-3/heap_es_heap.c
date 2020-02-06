/*

Implementar en lenguaje C una función recursiva con la firma bool
es_heap(int arr[], size_t n). Esta debe devolver true o false de acuerdo
a si el arreglo que recibe como parámetro cumple la propiedad de heap (de
mínimos).

Hacer el seguimiento de la función para el arreglo: [ 1, 7, 2, 8, 7, 6, 3, 3, 9, 10 ].

¿De qué orden es este algoritmo?

*/

bool es_heap(int arr[], size_t n) {

	return es_heap_recursivo(arr, 0, n);
}

bool es_heap_recursivo(int arr[], size_t pos, size_t n) {

	// Si el nodo es una hoja devuelvo true ya
	// que cumple la propiedad de heap.
	if (pos > (n - 2) / 2) {
		return true;
	}

	//  Si un padre es menor a su dos hijos y sus hijos son menores a sus propios hijos
	//  (recursivo) devuelvo true, si no false.
	if (arr[pos] <= arr[2*pos + 1] && arr[pos] <= arr[2*pos + 2] && es_heap_recursivo(arr, 2*pos + 1, n) &&
		es_heap_recursivo(arr, 2*pos + 2, n)) {
		return true;
	}

	return false;
}

// El algoritmo es de orden O(n) siendo n la cantidad de elementos en el arreglo, ya que necesito
// recorrer todo el arreglo en el peor caso. O(1) en el resto de las operaciones.