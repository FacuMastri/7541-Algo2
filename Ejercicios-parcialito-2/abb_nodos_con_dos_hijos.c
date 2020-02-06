/*

Dado un árbol binario, escriba una función recursiva que cuente la cantidad de nodos que tienen exacta-
mente dos hijos directos. ¿qué orden de complejidad tiene la función implementada?

 */

size_t contar_nodos_con_dos_hijos(ab_t* arbol) {

	// Condicion base.
	// El nodo no tiene datos, entonces es una hoja --> NO tiene hijos.
	if (!arbol->dato) {
		return 0;
	}

	// Si un nodo tiene ambos hijos (derecho e izquierdo), sumo 1 (ya que ese nodo tiene 2 hijos) y hago recursividad con ambos hijos.
	if (arbol->izq && arbol->der) {
		return 1 + contar_nodos_con_dos_hijos(arbol->izq) + contar_nodos_con_dos_hijos(arbol->der);

	// Llamo recursivamente para ambos lados del nodo, si resulta que el nodo no tiene o hijo derecho o izquierdo va a 
	// devolver 0 por la condicion base.
	} else {
		return contar_nodos_con_dos_hijos(arbol->izq) + contar_nodos_con_dos_hijos(arbol->der);
	}
}

// Orden de complejidad: O(n) siendo 'n' la cantidad de nodos en el arbol. Tengo que recorrer necesariamente
// todo el arbol para verificar si tienen o no dos hijos los nodos.