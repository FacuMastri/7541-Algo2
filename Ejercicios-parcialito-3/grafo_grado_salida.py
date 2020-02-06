

# El grado de salida de un vértice perteneciente a un grafo se define como la cantidad de
# aristas que salen de él. Implementar una primitiva que dado un grafo G y el vértice V calcule
# el grado de salida de ese vértice para un grafo implementado con:

# a) Matriz de Adyacencias

# b) Lista de Adyacencias

# Representacion en una matriz de adyacencias.
def grafo_grado_salida_matriz(grafo, v):

	grado_salida = 0

	for a in range(grafo.aristas()):
		if grafo.representacion()[a][v] == 1:
			grado_salida += 1

	return grado_salida

# Representacion en una lista de adyacencias.
def grafo_grado_salida_lista(grafo, v):

	iter = lista_crear_iter(grafo.representacion()[v])
	grado_salida = 0

	while not lista_iter_al_final(iter):
		grado_salida += 1
		lista_iter_avanzar(iter)

	lista_iter_destruir(iter)

	return grado_salida







