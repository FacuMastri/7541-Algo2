/*

Implemente una función que reciba un arreglo con un millón de números y muestre por
pantalla el contenido de los 100 elementos mayores. Sólo se puede recorrer el arreglo de entrada
una sola vez y se puede usar cualquiera de las estructuras de datos vistas en clase.

*/

void imprimir_elementos_mayores(int arr[], size_t n) {

	heap_t* heap = heap_crear(comparar_enteros);

	// Encolo primero los 100 primeros numeros del arreglo
	for (size_t i = 0; i < 100; i++) {
		heap_encolar(heap, &arr[i]);
	}

	// Ahora, voy comparando los numeros restantes en el array
	// con el minimo del heap, si es mayor el nuevo numero al minimo
	// entonces lo desencolo y encolo el nuevo numero.
	for (size_t i = 100; i < 1000000; i++) {
		if (comparar_enteros(arr[i], *(int*) heap_ver_minimo(heap)) > 0) {
			heap_desencolar(heap);
			heap_encolar(heap, &arr[i]);
		}
	}

	while (!heap_esta_vacio(heap)) {
		int* numero = heap_desencolar(heap);
		printf("%i\n", *numero);
	}

	heap_destruir(heap);
}