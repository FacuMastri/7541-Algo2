# Un árbol no dirigido es un grafo no dirigido que cumple con las siguientes propiedades:
# 
# a) |E| = |V| - 1
# b) Es Acíclico
# c) Es Conexo
# 
# Por teorema, si un grafo cumple dos de estas propiedades, será árbol (y por consiguiente, cumplirá la tercera).
# Haciendo uso de esto (y únicamente de esto), se pide implementar una función que reciba un grafo implementado
# con lista de adyacencias y determine si se trata o no de un árbol.
# 


# Necesito saber dos cosas: si el grafo es aciclico (no tiene ciclo) y si
# el grafo es conexo, para eso voy a modularizar un poco.


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

# Uso recorrido DFS
def grafo_es_arbol(grafo):

	visitados = {}
	padres = {}

	# Marco todos los vertices en principio
	# como no visitados ya que los voy a ir 
	# actualizando
	for v in grafo:
		visitados[v] = False

	for v in grafo:
		if v not in visitados:
			if tiene_ciclo_recursivo(grafo, v, visitados, padres):
				return False

	# Chequeo el diccionario de Visitados, si
	# hay alguno todavia con False, entonces no es conexo
	for v in visitados:
		if not visitados[v]:
			return False

	return True

	



