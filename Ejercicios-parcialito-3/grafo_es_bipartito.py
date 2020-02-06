# Escribir una función bool es_bipartito(grafo) que dado un grafo no
# dirigido devuelva true o false de acuerdo a si es bipartito o no. 
# 
# Indicar y justificar el orden del algoritmo.
# 
# ¿Qué tipo de recorrido utiliza?

def componente_es_bipartita(grafo, v, visitados, grupo):

	visitados[v] = True

	for w in grafo.adyacentes(v):
		if w in visitados:
			if grupo[w] == grupo[v]:
				return False
		else:
			grupo[w] = 1 - grupo[v]
			if not componente_es_bipartita(grafo, w, visitados, grupo):
				return False

	return True

def es_bipartito(grafo):

	grupo = {}
	visitados = {}

	for v in grafo:
		if v not in visitados:
			grupo[v] = 0
			if not componente_es_bipartita(grafo, v, visitados, grupo):
				return False
	return True

# El orden del algoritmo es O(V + E) donde por cada vertice V se recorre
# todas sus aristas E. El resto de las operaciones es O(1) y se utiliza
# un recorrido DFS. Este orden es si se utiliza como forma de representacion
# una lista de adyacencia