/* 

Implementar el TDA Mamushka teniendo en cuenta que uan Mamushka puede tener otra Mamushka dentro de si misma.
Las primitivas deben ser:

-- mamushka_t* mamushka_crear(size_t tam, color_t color): Crea una mamushka con un tamaño y color definido.

-- color_t mamushka_obtener_color(mamushka_t* mamushka): Obtiene el color de la Mamushka.

-- bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar): Intenta guardar la segunda mamushka en 
la primera. Si la primera ya tiene una mamushka guardada, entonces debe intentar guardar la mamushka a_guardar dentro
de la mamushka que ya esta guardada. La operacion falla (y devuelve false) si en algun momento se intenta guardar una
mamushka en otra de menor o igual tamanio.

-- mamushka_t* mamushka_obtener_guardad(mamushka_t*): Devuelve la mamushka guardada. NULL en caso de no tener ninguna guardada.

-- void mamushka_destruir(mamushka_t*): Destruye la mamushka (y todas las que se encuentran dentro).

Definir la estructura (struct) del TDA, y escribir estas 5 primitivas. Indicar el orden de cada una de ellas.

*/

typedef struct mamushka {

	struct mamushka* mamushka_interna;
	size_t tamanio;
	color_t color;
} mamushka_t;


// Crea una mamushka;
// Pre: recibe el tamanio y el color definidos.
// Post: devuelve una nueva mamushka.
mamushka_t* mamushka_crear(size_t tam, color_t color) {

	mamushka_t* mamushka = malloc(sizeof(mamushka_t));
	if (!mamushka) {
		return NULL;
	}

	mamushka->mamushka_interna = NULL;
	mamushka->tamanio = tam;
	mamushka->color = color;

	return mamushka;
}

// Obtiene el color de la mamushka.
// Pre: la mamushka fue creada.
// Post: devuelve el color de la mamushka.
color_t mamushka_obtener_color(mamushka_t* mamushka) {

	return mamushka->color;
}

// Intenta guardar una mamushka dentro de otra.
// Pre: las mamushkas fueron creadas.
// Post: devuelve true o false según si se pudo guardar la mamushka o no.
bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar) {

	mamushka_t* actual = contenedora;
	bool guardado;

	while (actual) {
		if (actual->tamanio <= a_guardar->tamanio) {
			guardado = false;
			break;
		}
		if (!actual->mamushka_interna) {
			actual->mamushka_interna = a_guardar;
			guardado = true;
			break;
		} else {
			actual = actual->mamushka_interna;
		}
	}

	return guardado;
}

// Otra opcion de manera recursiva.
bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar) {

	if (contenedora->tamanio <= a_guardar->tamanio) {
		return false;
	}

	if (contenedora->mamushka_interna) {
		return mamushka_guardar(contenedora->mamushka_interna, a_guardar);
	}
	contenedora->mamushka_interna = a_guardar;

	return true;
}

// Devuelve la mamushka interna.
// Pre: la mamushka fue creada.
// Post: devuelve una mamushka.
mamushka_t* mamushka_obtener_guardada(mamushka_t* mamushka) {

	if (!mamushka->mamushka_interna) {
		return NULL
	}

	return mamushka->mamushka_interna;
}

// Destruye la mamushka con sus mamushkas internas.
// Pre: la mamushka fue creada.
void mamushka_destruir(mamushka_t* mamushka) {

	if (!mamushka->mamushka_interna) {
		return;
	}

	mamushka_destruir(mamushka->mamushka_interna);
	free(mamushka);
}

// Otra opcion moviendo las referencias de los punteros.
void mamushka_destruir(mamushka_t* mamushka) {

	mamushka_t* anterior = NULL;
	mamushka_t* actual = mamushka;

	while (actual) {
		anterior = actual;
		actual = actual->mamushka_interna;
		free(anterior);
	}
}

/* Orden de primitivas:
 * Todas O(1) salvo destruir y guardar que son O(n) siendo n la cantidad de mamushkas que tenga que recorrer para destruir/guardar.
 */