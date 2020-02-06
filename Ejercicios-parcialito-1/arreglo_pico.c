/* 

Se tiene un arreglo en forma de "pico". Esto quiere decir, que inicialmente es estrictamente creciente
hasta una determinada posicion, y a partir de alli es estrictamente decreciente (suponer que el arreglo tiene al menos 3 elementos)

Por ejemplo: [1 2 3 1 0 -2] tiene pico en la posicion 2.

a) Implementar en C un algoritmo de Division y Conquista, de orden O(logn) siendo n el tamaño del arreglo que
permita encontrar la posicion del arreglo en la que se encuentra dicho pico: size_t posicion_pico(int* arreglo, size_t inicio, size_t fin)

b) Utilizando el Teorema Maestro, justificar el orden del algoritmo.

*/

// Devuelve la posicion del arreglo en donde se encuentra el "pico".
// Pre: el arreglo tiene forma de "pico".
size_t posicion_pico(int* arreglo, size_t inicio, size_t fin) {

	size_t medio = (inicio + fin) / 2;

	// Si mi anterior es menor, y el que me sigue es menor --> es el pico.
	if (arreglo[medio - 1] < arreglo[medio] && arreglo[medio + 1] < arreglo[medio]) {
		return medio;
	}

	// Si mi anterior es mayor --> el pico se encuentra del lado izquierdo.
	if (arreglo[medio - 1] > arreglo[medio]) {
		return posicion_pico(arreglo, inicio, medio - 1);
	// Si mi siguiente es mayor --> el pico se encuentra del lado derecho.
	} else if (arreglo[medio + 1] > arreglo[medio]) {
		return posicion_pico(arreglo, medio + 1, fin);
	}
}


