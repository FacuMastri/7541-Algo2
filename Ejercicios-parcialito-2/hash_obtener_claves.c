/*

Para un hash abierto y cerrado, implementar una primitiva lista_t* hash_claves(const hash_t*), que
reciba un hash y devuelva una lista con sus claves. Aclaración: no se puede utilizar el iterador externo del
hash. Indicar y justificar el orden.

*/

// Para hash abierto.
lista_t* hash_claves(const hash_t* hash) {

	// Creo la lista a devolver.
	lista_t* claves = lista_crear();
	if (!claves) {
		return NULL;
	}

	// Voy recorriendo toda la tabla de hash (que contiene listas), y con un iterador
	// voy iterando cada lista mientras NO este al final. Luego, inserto a la lista 
	// a devolver la clave de cada campo/nodo que es el dato de cada lista.
	for (size_t i = 0; i < hash->capacidad; i++) {
		lista_t* lista_pos_tabla = hash->tabla[i];
		lista_iter_t* iterador_lista_hash = lista_iter_crear(lista_pos_tabla);
		while (!lista_iter_al_final(lista_pos_tabla)) {
			lista_insertar_ultimo(claves, ((hash_campo_t*) lista_iter_ver_actual(iterador_lista_hash))->clave);
		}
		lista_iter_destruir(iterador_lista_hash);
	}

	return claves;
}

// Complejidad de la funcion: O(n) siendo 'n' la cantidad de listas dentro del hash, 
// o la capacidad del mismo (tanto para el hash abierto como cerrado)
.
// Para hash cerrado.
lista_t* hash_claves(const hash_t* hash) {

	lista_t* claves = lista_crear();
	if (!claves) {
		return NULL;
	}

	for (size_t i = 0; i < hash->capacidad, i++) {
		hash_campo_t* campo = hash->tabla[i]->campo;
		if (campo) {
			lista_insertar_ultimo(claves, campo->clave);
		}
	}

	return claves;
}