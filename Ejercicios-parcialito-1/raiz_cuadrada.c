/* Implementar en C una función que dado un número, encuentre por División y Conquista la parte entera de su raíz cuadrada, en tiempo O(logn). 
 * Demostrar, utilizando el Teorema Maestro, el orden de dicho algoritmo.
 * Ejemplos:
 *   - raiz(10) ---> 3
 *   - raiz(11) ---> 3
 *   - raiz(25) ---> 5
 */

// Dado un número, encuentra la parte entera de su raíz cuadrada.
// Pre: recibe un numero entero positivo (size_t), dos valores (size_t) entre los cuales
// se esta seguro que esta la parte de la raiz cuadrada del numero buscado.
// Post: devuelve la parte entera de la raiz cuadrada del primer numero recibido.
size_t calcular_raiz_cuadrada(size_t num, size_t inicio, size_t fin) {

	// Debo aplicar un algoritmo similar al de Busqueda Binaria --> O(logn);
	size_t medio = (inicio + fin) / 2;
	size_t cuadrado = medio * medio;

	if (num == cuadrado) {
		return medio;
	}

	if (num > cuadrado) {
		size_t cuadrado_sig = (medio + 1) * (medio + 1);
		if (cuadrado_sig > num) {
			return medio;
		} else {
			return calcular_raiz_cuadrada(num, medio + 1, fin);
		}
	}

	if (num < cuadrado) {
		return calcular_raiz_cuadrada(num, inicio, medio - 1);

	}
}

// Dado un número, encuentra la parte entera de su raíz cuadrada.
// Pre: recibe un numero entero positivo (size_t).
// Post: devuelve la parte entera de la raiz cuadrada.
size_t calcular_raiz_cuadrada_wrapper(size_t num) {
	return calcular_raiz_cuadrada(num, 0, num);
}


/* Ejemplo: raiz(6,0,6) --> raiz(6,0,2) --> raiz(6,2,2) = 2; */

/* Orden del algoritmo: T(n) = aT(n/b) + T(n^c) = 1.T(n/2) + T(1) */

