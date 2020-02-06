/* 
Implementar un algoritmo en C que reciba un arreglo de n enteros sin repetir y ordenado ascendentemente,
y determine en O(logn) si es mágico. Un arreglo es mágico si existe algún valor i (entre 0 y n − 1) tal que
arr[i] = i.

Ejemplos:

• A = [ -3, 0, 1, 3, 7, 9 ] es mágico porque A[3] = 3.
• B = [ 1, 2, 4, 6, 7, 9 ] no es mágico porque B[i] != i para todo i.

Justificar el orden del algoritmo.
*/

// Dado un arreglo de enteros, determina si ese arreglo es mágico o no.
// Pre: el arreglo debe estar ordenado ascendentemente y sin elementos repetidos.
// Post: devuelve true o false según corresponda.
bool es_array_magico(int arr[], size_t inicio, size_t fin) {

	// Si no se encuentra ninguna coincidencia, devuelvo false.
	if (inicio > fin) {
		return false;
	}

	size_t medio = (inicio + fin) / 2;

	// Si caigo en el medio, y justo coinciden entonces es magico.
	if (arr[medio] == medio) {
		return true;
	}
	// Si estoy en el medio, y sucede que el elemento del medio es mayor al indice de medio --> No puede haber un i 
	// a la derecha tal que arr[i] = i ya que los arr[i] incrementan en por lo menos 1, y i incrementa en 1. 
	if (arr[medio] > medio) {
		return es_array_magico(arr, inicio, medio - 1);
	} 

	// Si el elemento del medio es menor al indice de medio --> No puede haber un i a la izquierda
	// tal que arr[i] = i ya que los arr[i] disminuyen en por lo menos 1, y los i disminuyen en 1.
	if (arr[medio] < medio) {
		return es_array_magico(arr, medio + 1, fin)
	}

}