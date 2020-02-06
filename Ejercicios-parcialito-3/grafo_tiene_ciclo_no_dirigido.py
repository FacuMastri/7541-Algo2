# Escribir una función bool tiene_ciclo(grafo) que dado un grafo no dirigido devuelva
# true o false de acuerdo a si tiene al menos un ciclo o no.

# ¿Cuál es el orden del algoritmo? ¿Por qué?

# Uso recorrido DFS
def tiene_ciclo(grafo):

	visitados = {}
	padres = {}

	for v in grafo:
		if v not in visitados:
			if tiene_ciclo_recursivo(grafo, v, visitados, padres):
				return True

	return False

# Uso recorrido DFS
def tiene_ciclo_recursivo(grafo, v, visitados, padres):

	# Marco como visitado al vertice actual (v).
	visitados[v] = True

	# Veo recursivamente todos los adyacentes de ese
	# vertice v actual.
	for w in grafo.adyacentes(v):
		# Si no esta visitado, entonces entro recursivamente.
		if w not in visitados:
			padres[w] = v
			if tiene_ciclo_recursivo(grafo, w, visitados, padres):
				return True
		# Si el adyacente está visitado y no es el padre
		# del vertice v actual, entonces hay un ciclo.
		elif w != padres[v]:
			return True

	return False

# El orden de algoritmo es O (V + E), ya que se recorre por cada vertice todos sus adyacentes.
# Se usa un recorrido DFS. Este orden se obtiene si la forma de representacion del grafo es una
# lista de adyacencias o diccionario de diccionario.