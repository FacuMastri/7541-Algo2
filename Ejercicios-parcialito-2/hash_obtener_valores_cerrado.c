/*

Implementar una primitiva lista_t* hash_obtener_valores(const hash_t* hash)
para el hash cerrado que devuelva una lista de todos los valores dentro del hash.
Considerar que si un valor esta repetido dentro del hash debera aparecer repetido en la 
lista resultante.

*/

lista_t* hash_obtener_valores(const hash_t* hash) {

	lista_t* resultado = lista_crear();
	if (!lista) {
		return NULL;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i]->campo) {
			lista_insertar_primero(hash->tabla[i]->campo->valor);
		}
	}

	return resultado;
}