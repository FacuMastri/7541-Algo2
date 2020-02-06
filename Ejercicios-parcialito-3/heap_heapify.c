/*

a) Muestre una implementación de la funcion heapify, que crea un heap sobre un arreglo, utilizando la función downheap (no hace falta que muestre la implementacion de downheap).

b) ¿Qué diferencias tiene con la implementación de heapify utilizando la función upheap?.

*/

void heapify(void* arr[], size_t cantidad) {

	for (int i = cantidad; i > 0; i--) {
		downheap(arr, i - 1, cantidad);
	}
}

// b) Implementando heapify con downheap se obtiene una complejidad temporal de
// O (n) ya que hacer downheap de las hojas cuesta O(0), hacer downheap de la raiz
// cuesta O(logn) y hacer downheap de algun elemento del medio cuesta O(h) siendo h la 
// altura (desde la raiz) donde se encuentre ese elemento.
// En el caso de hacer heapify con upheap, la complejidad pasaria a ser O(nlogn) debido
// a que el numero de swaps aumenta con la profundidad del elemento, por ejemplo, si estoy
// en una hoja, tendria que swapear todo hasta la raiz en el peor caso y asi sucesivamente.
// De esta manera, se puede ver que el unico elemento que se beneficiaria de upheap es la raiz mientras
// que usando downheap, se benefician las hojas que son, aproximadamente, la mitad de los elementos del heap.