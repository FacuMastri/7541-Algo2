# Escribir una función bool es_conexo(grafo) que dado un grafo no dirigido
# devuelva true o false de acuerdo a si es conexo o no.

# ¿Cuál es el orden del algoritmo? ¿Por qué?


# Puedo usar tanto DFS como BFS, voy a usar BFS
def es_conexo(grafo):

	visitados = {}

	q = cola_crear()
	# Agarro un origen cualquiera ya que es un grafo 
	# no dirigido.
	origen = grafo.obtener_vertice_aleatorio()
	visitados[origen] = True
	q.encolar(origen)

	# Recorro todo el grafo con BFS y voy
	# marcando los visitados
	while not q.esta_vacia():
		v = q.desencolar()
		for w in grafo.adyacentes(v):
			if w not in visitados:
				visitados[w] = True
				q.encolar(w)

	# Chequeo si el diccionario de visitados tiene la misma cantidad
	# de vertices que el grafo total, si es asi entonces recorrí todo el grafo
	# y es conexo, si no --> no es conexo
	return len(visitados) == len(grafo)

# El orden del algoritmo es O(V + E), ya que por cada vertice V visito o utilizo
# todas sus aristas E. Este orden se aplica si se utiliza como forma de representacion
# del grafo es una lista de adyacencias.
