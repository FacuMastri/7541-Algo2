# Un grupo de estudiantes de computacion ha decidido jugar un partido de paintball.
# Para que sea mas divertido, decidieron que cada uno deberia jugar contra sus mas intimos amigos.
# Es por eso que armaron un grafo no dirigido, sin peso, en el que cada vertice
# es un jugador, y cada arista (u,v) representa que u es mejor amigo de v y viceversa.
# Considerar que las relaciones de "mejor amistad" son simetricas.
# 
# Escribir un algoritmo que devuelva true o false de acuerdo a si es posible
# crear dos equipos en donde no haya dos mejores amigos del mismo lado (mas alla
# de si los equipos quedan con la misma cantidad de jugadores o no).
# 
# Cual es el orden del algoritmo? Que tipo de recorrido utiliza?

def hay_equipos_visitar(grafo, v, visitados, grupo):

	visitados[v] = True

	for w in grafo.adyacentes(v):
		if w in visitados:
			if grupo[w] == grupo[v]:
				return False
		else:
			grupo[w] = 1 - grupo[v]
			if not hay_equipos_visitar(grafo, w, visitados, grupo):
				return False

	return True

def hay_equipos(grafo):

	grupo = {}
	visitados = {}

	for v in grafo:
		if v not in visitados:
			grupo[v] = 0
			if not hay_equipos_visitar(grafo, v, visitados, grupo):
				return False

	return True

# El orden del algoritmo es O(V + E) donde V es la cantidad de vertices
# y E la cantidad de aristas. Se usa un recorrido DFS, es decir, por cada
# vertice se va visitando cada una de sus propias aristas. Este orden se obtiene
# siempre que la representacion del grafo sea una lista de adyacencias o un
# diccionario de diccionario.