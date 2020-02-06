/* Implementar en C el TDA ComposiciónFunciones que emula la composición de funciones (i.e. f(g(h(x))).
 * Se debe definir la estructura del TDA, y las siguientes primitivas:

 * -----composicion_t* composicion_crear()
 * -----void composicion_destruir(composicion_t*)
 * -----bool composicion_agregar_funcion(composicion_t*, double (*f)(double))
 * -----double composicion_aplicar(composicion_t*, double)

 * Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto
 * orden de aplicación. Por ejemplo: para emular f(g(x)), se debe hacer:
 * 1) composicion_agregar_funcion(composicion, f);
 * 2) composicion_agregar_funcion(composicion, g);
 * 3) composicion_aplicar(composicion, x);

 * Indicar el orden de las primitivas.

*/

typedef struct composicion {

	pila_t* funciones; // Se va a tratar de una pila de funciones.

} composicion_t;

// Crea una composicion de funciones.
// Post: devuelve una composicion vacía de funciones.
composicion_t* composicion_crear() {

	composicion_t* composicion = malloc(sizeof(composicion_t));
	if (!composicion) {
		return NULL;
	}

	composicion->funciones = pila_crear();
	if (!composicion->funciones) {
		free(composicion);
		return NULL;
	}

	return composicion;
}

// Destruye la composicion.
// Pre: la composicion fue creada.
// Post: se eliminaron todos los elementos de la composicion.
void composicion_destruir(composicion_t* composicion) {

	pila_destruir(composicion->funciones);
	free(composicion);
}

// Agrega una funcion a la composicion.
// Pre: la composicion fue creada.
// Post: la composicion contiene una funcion mas.
bool composicion_agregar_funcion(composicion_t* composicion, double (*f) (double)) {

	// Si es NULL, no lo apilo.
	if (!f) {
		return false;
	} else {
		return pila_apilar(composicion->funciones, f);
	}
}

// Aplica la composicion de funciones dado el valor.
// Pre: la composicion fue creada.
// Post: Devuelve un valor tipo double luego de aplicada la composicion.
typedef double (*funcion_t)(double); // LO NECESITO PARA CASTEAR EL VOID* QUE SALE DE LA PILA.

double composicion_aplicar(composicion_t* composicion, double valor) {

	double resultado = valor;

	while (!pila_esta_vacia(composicion->funciones)) {
		funcion_t funcion = (funcion_t) pila_desapilar(composicion->funciones);
		resultado = funcion(resultado);
	}

	return resultado;
}

/* Orden de las primitivas:

Todas O(1) salvo composicion_aplicar() que es O(n x O(f)) ya que vamos desapilando las n funciones que tenemos 
almacenadas y aplicandolas.
*/


