/* 

Escriba una función recursiva para calcular de forma eficiente la potencia de un número
con exponente entero positivo.

*/


// Debo hacer una funcion recursiva que lo haga en O(logn) --> algo similar a Busqueda binaria.

// Calcula la potencia de un numero con exponente entero positivo.
// Pre: el exponente es un entero positivo.
// Post: devuelve la potencia.
int calcular_potencia(int numero, unsigned int exponente) {

	// Caso base: cualquier numero elevado a la 0 es 1.
	if (exponente == 0) {
		return 1;
	}

	int temp = calcular_potencia(numero, exponente/2);
	// Propiedad de potencia: Si el exponente es par --> calculo la potencia con la mitad del exponente y multiplico el resultado por si mismo.
	if (exponente % 2 == 0) {
		return temp * temp;
	} else {
		return numero * temp * temp;
	}
}