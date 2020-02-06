# Un grafo no dirigido es completo cuando todos los vertices estan unidos
# entre si y tiene todas las aristas que puede tener (es decir: A = (V - 1)^2 / 2)
# 
# Se dice que un grafo es "altamente conectado" cuando todos los vertices tienen
# al menos un 70% de aristas respecto del maximo posible. Escribir una funcion
# que reciba un grafo y devuelve true o false de acuerdo a si es altamente
# conectado.
# 
# Justificar brevemente el orden del algoritmo para una implementacion
# con matriz de adyacencias


def es_grafo_altamente_conectado(grafo):

	max_aristas = (grafo.cantidad_vertices() - 1)
	cant_necesarias_aristas = max_aristas * 0.7
	cant_aristas = {}

	for v in grafo:
		cant_aristas[v] = len(grafo.adyacentes(v))
		if cant_aristas[v] < cant_necesarias_aristas:
			return False

	return True

# Ver la cantidad de vertices es O(V)
# Recorrer todos los vertices del grafo es O(V)
# Obtener todos los vecinos de un vertice es O(V), para todo el grafo seria O(V^2)
# En total seria: O(V) + O(V) + O(V^2) = O(V^2 + 2V) = O(V + V^2) = O(V^2) (que es lo
# que ocupa en memoria el grafo)
