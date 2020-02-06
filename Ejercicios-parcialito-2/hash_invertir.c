/*

Sabiendo que se tiene un hash en que los valores son cadenas, implementar la función hash_t*
hash_invertir(const hash_t*); que devuelva un nuevo hash cuyas claves sean los valores del original
y sus valores asociados sean listas con las claves que tenían dichos valores en el primero. Indicar la
complejidad de la función.

*/

hash_t* hash_invertir(const hash_t* hash_orig) {

	// Creo un iterador de hash para ir recorriendolo
    hash_iter_t* iterador_hash = hash_iter_crear(hash_orig);
    if (!iterador_hash) {
    	return NULL;
    } 

    // Creo el nuevo hash a devolver.
    hash_t* hash_invertido = hash_crear(NULL);
    if (!hash_invertido) {
        return NULL;
    }

    // Recorro el hash con el iterador hasta el final.
    while (!hash_iter_al_final(iterador_hash)) {
        const char* clave_actual = hash_iter_ver_actual(hash_orig); // Obtengo la clave del campo de hash donde estoy parado.
        const char* valor = hash_obtener(hash_orig, clave_actual); // Obtengo el valor de la clave obtenida anteriormente.
        bool ok = hash_guardar(hash_invertido, valor, clave_actual); // Guardo en el nuevo hash el par clave, valor anterior.
        if (!ok) {
            return NULL;
        }
        hash_iter_avanzar(iterador_hash);
    }

    hash_iter_destruir(iterador_hash);

    return hash_invertido;
}

// Complejidad de la funcion: O(n) siendo 'n' la cantidad de campos en el hash.