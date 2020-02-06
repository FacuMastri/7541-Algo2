/*

Definimos como quiebre en un arbol binario cuando ocurre que un hijo derecho
tiene un hijo izquierdo, o viceversa.

Implementar una primitiva para el arbol binario size_t ab_quiebres(const ab_t*) que
dado un arbol binario nos devuelva la cantidad de quiebres que tiene. La primitiva no
debe modificar el arbol. La estructura del tipo ab_t es:

typedef struct ab {
	
	struct ab* izq;
	struct ab* der;
} ab_t;

Indicar y justifcar el orden de la primitiva e indicar el tipo de recorrido implementado.

*/

size_t ab_quiebres_aux(ab_t* arbol, bool es_hijo_derecho, bool es_hijo_izquierdo) {

	// Condicion base.
	if (!arbol) {
		return 0;
	}

	// Es hijo derecho y tiene un hijo izquierdo --> sumo 1 y llamo para ambos lados.
	if (es_hijo_derecho && arbol->izq) {
		return 1 + ab_quiebres_aux(arbol->izq, false, true) + ab_quiebres_aux(arbol->der, true, false);
	}

	// Es hijo izquierdo y tiene hijo derecho --> sumo 1 y llamo para ambos lados.
	if (es_hijo_izquierdo && arbol->der) {
		return 1 + ab_quiebres_aux(arbol->izq, false, true) + ab_quiebres_aux(arbol->der, true, false);

	} else {
		return 0;
	}
}


size_t ab_quiebres(const ab_t* arbol) {

	// Condicion base.
	if (!arbol) {
		return 0;
	}

	// Si hay un hijo derecho o izquierdo, llamo para ambos lados (si hay 1 solo, me devuelve 0 de ese lado).
	if (arbol->der || arbol->izq) {
		return ab_quiebres_aux(arbol->izq, false, true) + ab_quiebres_aux(arbol->der, true, false)

	// Si no hay hijo derecho ni izquierdo devuelvo 0.
	} else {
		return 0;
	}
}

// Orden de la primitiva: O(n) siendo 'n' la cantidad de nodos en el arbol. El recorrido es pre-order
// ya que primero proceso la raiz y luego sus hijos izquierdos y derechos.
