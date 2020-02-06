from random import choice

class Grafo(object):
	'''Clase que representa un grafo. Implementado como diccionario
	de diccionarios'''

	def __init__(self, es_dirigido=False):
		'''
		Crea el grafo.
		es_dirigido: True si el grafo es dirigido, False por defecto.
		Post: el grafo fue creado.
		'''
		self.grafo = {}
		self.dirigido = es_dirigido

	def agregar_arista(self, desde, hasta, peso=1):
		'''
		Agrega una arista al grafo. Si la arista ya existiera, se actualizara
		el peso.
		desde, hasta: vertices dentro del grafo. Si no existe alguno de ellos
		se lanzara un error.
		peso: valor del peso de la arista, 1 por defecto.
		Post: el grafo contiene una arista mas.
		'''
		self.grafo[desde][hasta] = peso
		if not self.dirigido:
			self.grafo[hasta][desde] = peso

	def borrar_arista(self, desde, hasta):
		'''
		Elimina la arista que conecta a los vertices desde, hasta.
		desde, hasta: vertices dentro del grafo. Si no existe alguno de ellos
		se lanzara un error.
		Post: el grafo contiene una arista menos.
		'''
		del self.grafo[desde][hasta]
		if not self.dirigido:
			del self.grafo[hasta][desde]

	def agregar_vertice(self, vertice):
		'''
		Agrega un vertice al grafo.
		vertice: vertice a ser agregado.
		Post: el grafo contiene un vertice mas
		'''
		self.grafo[vertice] = {}

	def borrar_vertice(self, vertice):
		'''
		Borra un vertice del grafo.
		vertice: vertice a ser borrado. Si no se encuentra en el grafo
		se lanzara un error.
		Post: el grafo contiene un vertice menos.
		'''
		for v in self.grafo:
			if vertice in self.grafo[v].keys():
				del self.grafo[v][vertice]
		del self.grafo[vertice]

	def __contains__(self, vertice):
		'''
		Determina si un vertice existe en el grafo.
		vertice: vertice a ser verificado.
		Devuelve True o False segun si el vertice existe en el grafo o no
		'''
		return vertice in self.grafo

	def hay_union(self, desde, hasta):
		'''
		Determina la union entre dos vertices en el grafo.
		desde, hasta: vertices del grafo. Si algunos de ellos no
		existiera en el grafo, se lanzara un error.
		Devuelve True o False segun si la union existe o no.
		'''
		return hasta in self.grafo[desde]

	def obtener_peso_union(self, desde, hasta):
		'''
		Obtiene el peso de la union entre dos vertices.
		desde, hasta: vertices del grafo. Si no existiera alguno de ellos
		se lanzara un error.
		Devuelve el peso de la arista que conecta ambos vertices.
		'''
		return self.grafo[desde][hasta]

	def obtener_vertices(self):
		'''
		Devuelve una lista con todos los vertices del grafo.
		'''
		return list(self.grafo)

	def obtener_vertice_aleatorio(self):
		'''
		Devuelve un vertice al azar del grafo.
		'''
		return choice(list(self.grafo))

	def obtener_adyacentes(self, vertice):
		'''
		Devuelve una lista con todos los vertices adyacentes de un vertice.
		vertice: vertice del grafo. Si no existiera, se lanzara un error.
		'''
		return list(self.grafo[vertice])

	def __len__(self):
		'''
		Devuelve la cantidad de vertices del grafo.
		'''
		return len(self.grafo)

	def __iter__(self):
		'''
		Permite iterar un grafo.
		'''
		return iter(self.grafo)