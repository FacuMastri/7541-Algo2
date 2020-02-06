/*

La diferencia simetrica entre dos conjuntos A y B es un conjunto que contiene todos los
elementos que se encuentran en A y no en B, y viceversa.

Implementar una funcion hash_t* diferencia_simetrica_hashes(const hash_t* h1, const hash_t* h2) que
devuelva un nuevo hash con la diferencia simetrica entre los dos recibidos por parametro. La diferencia tiene
que ser calculada teniendo en cuenta las claves, y los datos asociados a las claves deben ser los mismos que 
estaban en cada uno de los hashes originales.

Ejemplo:
h1 = { "perro": "guau", "gato": "miau", "vaca", "mu"}
h2 = { "perro": "woof", "zorro": "ding-ding"}
diferencia_simetrica_hashes(h1, h2) => {"gato": "miau", "vaca": "mu", "zorro": "ding-ding"}

Indicar y justificar el orden de la funcion implementada.

*/

hash_t* diferencia_simetrica_hashes(const hash_t* h1, const hash_t* h2) {

	// Creo el hash a devolver.
	hash_t* resultado = hash_crear(NULL);
	if (!resultado) {
		return NULL;
	}

	// Creo los iteradores de los dos hashes recibidos.
	hash_iter_t* iter_h1 = hash_iter_crear(h1);
	if (!iter_h1) {
		return NULL;
	}
	hash_iter_t* iter_h2 = hash_iter_crear(h2);
	if (!iter_h2) {
		return NULL;
	}

	// Comparo simetricamente mientras el iterador NO este al final.
	while (!hash_iter_al_final(iter_h1) && !hash_iter_al_final(iter_h2)) {
		char* clave_h1 = hash_iter_ver_actual(iter_h1);
		char* clave_h2 = hash_iter_ver_actual(iter_h2);
		if (strcmp(clave_h1, clave_h2) != 0) {
			hash_guardar(resultado, clave_h1, hash_obtener(h1, clave_h1));
			hash_guardar(resultado, clave_h2, hash_obtener(h2, clave_h2));
		}
		hash_iter_avanzar(iter_h1);
		hash_iter_avanzar(iter_h2);
	}

	// Si termino el iterador 2, sigo con el 1.
	while (!hash_iter_al_final(iter_h1)) {
		char* clave = hash_iter_ver_actual(iter_h1);
		hash_guardar(resultado, clave, hash_obtener(h1, clave));
		hash_iter_avanzar(iter_h1);
	}

	// Si termino el iterador 1, sigo con el 2.
	while (!hash_iter_al_final(iter_h2)) {
		char* clave = hash_iter_ver_actual(iter_h2);
		hash_guardar(resultado, clave, hash_obtener(h2, clave));
		hash_iter_avanzar(iter_h2);
	}

	hash_iter_destruir(iter_h1);
	hash_iter_destruir(iter_h2);

	return resultado;
}

// Orden de la funcion implementada: O(n + k) siendo 'n' la cantidad de campos del primer hash
// y siendo 'k' la diferencia entre la cantidad de campos del segundo hash con el primero.