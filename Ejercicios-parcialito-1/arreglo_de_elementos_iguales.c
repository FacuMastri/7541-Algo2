/*

Implementar un algoritmo que, por division y conquista, determine si un arreglo de enteros
tiene todos sus elementos iguales. Determinar el orden del algoritmo, justificando con el Teorema Maestro.

*/

bool arreglo_tiene_elementos_iguales(int arr[], size_t cantidad) {

	if (cantidad == 2) {
		return arr[0] == arr[1];
	}

	if (arreglo_tiene_elementos_iguales(arr, cantidad/2) && arreglo_tiene_elementos_iguales(arr + cantidad/2, cantidad/2)) {
		return arr[0] == arr[cantidad / 2]
	}

	return false;
}