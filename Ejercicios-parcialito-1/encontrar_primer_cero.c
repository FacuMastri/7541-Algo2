/* 
Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, “unos seguidos de ceros”). Se pide:

a) una función de orden O(logn) que encuentre el indice del primer 0. Si no hay ningún 0 (solo
hay unos), debe devolver -1.

b) demostrar con el Teorema Maestro que la función es, en efecto, O(log n).

Ejemplos:
[1, 1, 0, 0, 0] -> 2
[0, 0, 0, 0, 0] -> 0
[1, 1, 1, 1, 1] -> -1

*/

// Debo implementar una funcion tal que su orden sea O(logn) --> similar a Busqueda binaria.

// Dado un arreglo, devuelvo el indice del primer 0.
// Pre: el arreglo está ordenado (contiene unos seguidos de ceros).
// Post: devuelve el índice del primer 0, o -1 en caso que no haya ningún cero.
size_t encontrar_indice_primer_cero(int arr[], size_t inicio, size_t fin) {

	// No se encuentra, entonces devuelvo -1.
	if (inicio > fin) {
		return -1;
	}

	size_t medio = (inicio + fin) / 2;

	// Si caigo en un 0 y, o bien es el primer elemento o el anterior contiene un 1...
	if (arr[medio] == 0 && (medio == 0 || arr[medio - 1] == 1)) {
		return medio;
	// Si caigo en un 0, descarto toda la parte derecha y me quedo con la izquierda.
	} else if (arr[medio] == 0) {
		return encontrar_indice_primer_cero(arr, inicio, medio - 1);
	// Si caigo en un 1, descarto toda la parte izquierda y me quedo con la derecha.
	} else {
		return encontrar_indice_primer_cero(arr, medio + 1, fin);
	}
}