from grafo import Grafo
from heapq import heappush, heappop
from math import inf
from constantes import VERTICE, RECORRIDO, PESO, ACTUAL, PROXIMO

# *****************************************************************
#                   FUNCIONES AUXILIARES
# *****************************************************************

def _reconstruir_camino(padre, desde, hasta):
	'''
	Reconstruye el camino desde los vertices desde-hasta.
	padre: diccionario donde las claves son los vertices y los valores sus
	padres.
	desde, hasta: vertices del grafo.
	Devuelve una lista con el camino entre los dos vertices.
	'''
	recorrido = []

	while padre[hasta]:
		recorrido.append(hasta)
		hasta = padre[hasta]
	recorrido.append(hasta)
	recorrido.reverse()

	return recorrido

def _obtener_recorrido_optimo(grafo, recorrido_actual, mejor_recorrido, costo_recorrido_actual, costo_minimo):
	'''
	Calcula el costo minimo al recorrer todo el grafo segun condiciones del TSP.
	grafo: el grafo fue creado.
	recorrido_actual: lista que representa los vertices recorridos hasta el momento.
	mejor_recorrido: lista que representa el mejor camino encontrado.
	costo_recorrido_actual: costo del recorrido actual.
	costo_minimo: mejor costo minimo hasta el momento.
	Devuelve una tupla compuesta por el mejor recorrido y el costo minimo.
	'''
	if costo_recorrido_actual > costo_minimo:
		return (mejor_recorrido, costo_minimo)

	if len(recorrido_actual) == len(grafo) and costo_recorrido_actual < costo_minimo:
		if costo_recorrido_actual + grafo.obtener_peso_union(recorrido_actual[-1], recorrido_actual[0]) < costo_minimo:
			mejor_recorrido = recorrido_actual[:]
			mejor_recorrido.append(mejor_recorrido[0])
			costo_minimo = costo_recorrido_actual + grafo.obtener_peso_union(recorrido_actual[-1], recorrido_actual[0])
		return (mejor_recorrido, costo_minimo)

	for v in grafo.obtener_adyacentes(recorrido_actual[-1]):
		if v not in recorrido_actual:
			costo_recorrido_actual += grafo.obtener_peso_union(recorrido_actual[-1], v)
			recorrido_actual.append(v)
			mejor_recorrido, costo_minimo = _obtener_recorrido_optimo(grafo, recorrido_actual, mejor_recorrido, costo_recorrido_actual, costo_minimo)
			costo_recorrido_actual -= grafo.obtener_peso_union(recorrido_actual[-2], recorrido_actual[-1])
			recorrido_actual.remove(v)

	return (mejor_recorrido, costo_minimo)

def _obtener_proximo_adyacente(grafo, visitados, vertice):
	'''
	Obtiene el vertice adyacente mas cercano a uno dado que todavia
	no haya sido visitado.
	grafo: el grafo fue creado.
	visitados: diccionario donde las claves son los vertices y los valores son
	True o False según si el vertice fue visitado o no.
	vertice: vertice perteneciente al grafo.
	'''
	costo_minimo = inf
	adyacente = None
	for v in grafo.obtener_adyacentes(vertice):
		if v in visitados:
			continue
		costo = grafo.obtener_peso_union(vertice, v)
		if costo < costo_minimo:
			costo_minimo = costo
			adyacente = v

	return adyacente

def _orden_topologico_dfs(grafo, vertice, orden, visitados):
	'''
	Funcion recursiva de orden_topologico.
	grafo: el grafo fue creado.
	vertice: vertice perteneciente al grafo.
	orden: lista que representa el orden topologico.
	visitados: diccionario donde las claves son los vertices y los valores son
	True o False según si el vertice fue visitado o no.
	'''
	visitados[vertice] = True
	for v in grafo.obtener_adyacentes(vertice):
		if v not in visitados:
			_orden_topologico_dfs(grafo, v, orden, visitados)
	orden.append(vertice)

# *****************************************************************
#                   FUNCIONES PRINCIPALES
# *****************************************************************

def camino_minimo(grafo, desde, hasta):
	'''
	Calcula el camino minimo entre los vertices desde-hasta.
	grafo: el grafo fue creado.
	desde, hasta: vertices pertenecientes al grafo.
	Devuelve una lista con los vertices correspondientes al camino minimo.
	En caso de que no exista camino entre los vertices, devuelve None.
	'''
	distancia = {}
	padre = {}
	for v in grafo:
		distancia[v] = inf
	distancia[desde] = 0
	padre[desde] = None
	heap = []
	heappush(heap, (distancia[desde], desde))

	while heap:
		vertice = heappop(heap)[VERTICE]
		if vertice == hasta:
			return _reconstruir_camino(padre, desde, hasta)
		for w in grafo.obtener_adyacentes(vertice):
			if distancia[vertice] + grafo.obtener_peso_union(vertice, w) < distancia[w]:
				padre[w] = vertice
				distancia[w] = distancia[vertice] + grafo.obtener_peso_union(vertice, w)
				heappush(heap, (distancia[w], w))
	return None

def viajante(grafo, origen):
	'''
	Resuelve de forma optima el problema del viajante.
	grafo: el grafo fue creado.
	origen: el vertice pertenece al grafo.
	Devuelve una lista con el recorrido a realizar.
	'''
	recorrido_actual = [origen]
	mejor_recorrido = []
	costo_minimo_inicial = inf
	costo_recorrido_actual = 0
	mejor_recorrido = _obtener_recorrido_optimo(grafo, recorrido_actual, mejor_recorrido, costo_recorrido_actual, costo_minimo_inicial)[RECORRIDO]

	return mejor_recorrido

def viajante_aproximado(grafo, origen):
	'''
	Resuelve de forma aproximada el TSP.
	grafo: el grafo fue creado.
	origen: vertice perteneciente al grafo.
	Devuelve una lista con el recorrido a realizar.
	'''
	visitados = {}
	visitados[origen] = True
	recorrido = [origen]
	actual = origen

	while len(visitados) != len(grafo):
		proximo = _obtener_proximo_adyacente(grafo, visitados, actual)
		recorrido.append(proximo)
		visitados[proximo] = True
		actual = proximo
	recorrido.append(origen)

	return recorrido

def orden_topologico(grafo):
	'''
	Obtiene un orden topologico de un grafo.
	grafo: el grafo fue creado y debe ser dirigido.
	Devuelve una lista con un orden topologico del grafo, None en caso
	de no existir un orden topologico.
	'''
	visitados = {}
	orden = []

	for v in grafo:
		if v not in visitados:
			_orden_topologico_dfs(grafo, v, orden, visitados)
	if not orden:
		return None
	orden.reverse()

	return orden

def arbol_tendido_minimo(grafo):
	'''
	Obtiene un arbol de tendido minimo de un arbol.
	grafo: el grafo fue creado.
	Devuelve un nuevo grafo que representa un arbol de tendido
	minimo del original.
	'''
	inicio = grafo.obtener_vertice_aleatorio()
	visitados = {}
	visitados[inicio] = True
	heap = []
	arbol = Grafo(True)

	for v in grafo.obtener_adyacentes(inicio):
		peso_arista = grafo.obtener_peso_union(inicio, v)
		heappush(heap, (peso_arista, (inicio, v)))

	for v in grafo:
		arbol.agregar_vertice(v)

	while heap:
		dato = heappop(heap)
		peso_arista = dato[PESO]
		actual = dato[VERTICE][ACTUAL]
		proximo = dato[VERTICE][PROXIMO]
		if proximo in visitados:
			continue
		arbol.agregar_arista(actual, proximo, peso_arista)
		visitados[proximo] = True
		for u in grafo.obtener_adyacentes(proximo):
			heappush(heap, (grafo.obtener_peso_union(proximo, u), (proximo, u)))

	return arbol
