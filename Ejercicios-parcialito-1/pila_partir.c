/* 

Escribir una función que reciba una pila y un parámetro n con la cantidad de elementos
en la pila y la “parta” en dos: La que es recibida por parámetro contendrá la primera mitad
(elementos de 0 a n/2 - 1), y la pila devuelta por la función tendrá los elementos de n/2 a n-1,
manteniendo el orden de la pila original. (Se pueden usar las estructuras auxiliares que crean
convenientes) 

*/

// Dada una pila y su cantidad de elementos, parte la pila por la mitad y devuelve
// una nueva pila con la segunda mitad manteniendo el orden de la pila original.
// Pre: la pila original fue creada, y la cantidad de elementos es mayor a 0.
// Post: se devuelve una segunda pila con la mitad de los elementos de la primera.
pila_t* pila_partir(pila_t* pila_original, size_t cantidad_elementos) {

	pila_t* pila_aux = pila_crear();
	pila_t* segunda_pila = pila_crear();

	// Desapilo los elementos y los apilo en una pila auxiliar para mantener el orden original.
	for (size_t i = cantidad_elementos - 1; i >= (cantidad_elementos / 2); i --) {
		void* dato_aux = pila_desapilar(pila_original);
		pila_apilar(pila_aux, dato_aux);
	}

	// Desapilo de la pila auxiliar y los apilo en la pila a devolver.
	while (!pila_esta_vacia(pila_aux)) {
		void* dato_aux = pila_desapilar(pila_aux);
		pila_apilar(segunda_pila, dato_aux);
	}

	// Despues la tengo que destruir, ya que es auxiliar.
	pila_destruir(pila_aux); 

	return segunda_pila;
}