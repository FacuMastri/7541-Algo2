import grafo_utilities
import csv
from grafo import Grafo
from generador_kml import GeneradorKml
from constantes import VIAJE_OPTIMO, VIAJE_APROXIMADO, CIUDAD_ORIGEN, CIUDAD_DESTINO, LATITUD, LONGITUD, CMD_IR, CMD_ITINERARIO, CMD_VIAJE

# *****************************************************************
#                   FUNCIONES AUXILIARES
# *****************************************************************

def _calcular_costo_recorrido(mapa, recorrido):
	'''
	Calcula el costo del recorrido sobre un grafo.
	mapa: el grafo fue creado.
	recorrido: lista que contiene las claves de los vertices del grafo.
	Devuelve el costo total de recorrer los vertices.
	'''
	costo = 0
	for i in range(len(recorrido) - 1):
		costo += mapa.obtener_peso_union(recorrido[i], recorrido[i + 1])

	return costo

def _imprimir_recorrido(mapa, recorrido):
	'''
	Imprime el recorrido y su costo total por salida estandar.
	mapa: el grafo fue creado.
	recorrido: lista que contiene los vertices del grafo.
	'''
	costo_total = _calcular_costo_recorrido(mapa, recorrido)
	for i in range(len(recorrido)):
		if i == len(recorrido) - 1:
			print(recorrido[i])
			break
		print(recorrido[i], '-> ', end='')
	print("Costo total: {}".format(costo_total))

def _calcular_peso_total_mst(arbol, camino_reducido):
	'''
	Calcula el peso total de un arbol de tendido minimo.
	arbol: el grafo fue creado.
	camino_reducido: lista de listas del tipo [[v_salida, v_llegada, peso]].
	Devuelve el peso total del arbol de tendido minimo.
	'''
	peso_total = 0
	for v in arbol:
		for w in arbol.obtener_adyacentes(v):
			peso_aux = arbol.obtener_peso_union(v, w)
			camino_reducido.append([v, w, peso_aux])
			peso_total += peso_aux

	return peso_total

def _cargar_vertices_grafo(un_grafo, otro_grafo):
	'''
	Agrega los vertices de un grafo hacia otro grafo.
	un_grafo, otro_grafo: los grafos fueron creados.
	Post: otro_grafo contiene los mismos vertices que un_grafo.
	'''
	for v in un_grafo:
		otro_grafo.agregar_vertice(v)

def _cargar_aristas_desde_csv(ruta_csv, grafo):
	'''
	Agrega las aristas correspondientes a un grafo a partir de un
	archivo CSV.
	ruta_csv: ruta del archivo csv.
	grafo: el grafo fue creado.
	'''
	with open(ruta_csv, 'r') as file:
		reader = csv.reader(file)
		for linea in reader:
			desde = linea[CIUDAD_ORIGEN]
			hasta = linea[CIUDAD_DESTINO]
			# No agrego el peso, ya que esa info. la tengo en el mapa
			# original.
			grafo.agregar_arista(desde, hasta, None)

def _exportar_archivo_kml(comando, ruta_salida, recorrido, info_ciudades):
	'''
	Crea y escribe un archivo KML con el formato necesario.
	comando: comando recientemente ejecutado (i.e.: ir Moscu, Sochi)
	ruta_salida: nombre del archivo de salida.
	recorrido: lista que contiene los nombres de las ciudades.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	'''
	kml = GeneradorKml(comando, ruta_salida)
	for ciudad in recorrido:
		kml.agregar_lugar(ciudad, info_ciudades[ciudad][LONGITUD], info_ciudades[ciudad][LATITUD])
	kml.agregar_lineas()
	kml.finalizar()

def _exportar_camino_reducido(ruta_salida, info_ciudades, camino_reducido):
	'''
	Crea y escribe un archivo CSV con un formáto idéntico al archivo de ciudades
	inicial, pero únicamente con los caminos estrictamente necesarios.
	ruta_salida: ruta indicada donde exportar el archivo KML.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	camino_reducido: lista de listas del tipo [v_salida, v_llegada, peso].
	'''
	with open(ruta_salida, 'w') as file:
		writer = csv.writer(file)
		file.write("{}\n".format(len(info_ciudades)))
		for ciudad in info_ciudades:
			writer.writerow([ciudad, info_ciudades[ciudad][LONGITUD], info_ciudades[ciudad][LATITUD]])
		file.write("{}\n".format(len(camino_reducido)))
		writer.writerows(camino_reducido)

# *****************************************************************
#                   FUNCIONES PRINCIPALES
# *****************************************************************

def ir_desde_hasta(mapa, desde, hasta, info_ciudades, ruta_salida):
	'''
	Permite ejecutar el comando 'ir'
	mapa: el grafo fue creado.
	desde, hasta: vertices pertenecientes al grafo.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_salida: ruta indicada donde exportar el archivo KML.
	'''
	camino_minimo = grafo_utilities.camino_minimo(mapa, desde, hasta)
	_exportar_archivo_kml(CMD_IR + " " + desde + ", " + hasta, ruta_salida, camino_minimo, info_ciudades)
	_imprimir_recorrido(mapa, camino_minimo)

def viajar_desde(mapa, origen, tipo_viaje, info_ciudades, ruta_salida):
	'''
	Permite ejecutar el comando 'viaje'.
	mapa: el grafo fue creado.
	origen: vertice perteneciente al grafo.
	tipo_viaje: string que especifica si el viaje es optimo o aproximado.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_salida: ruta indicada donde exportar el archivo KML.
	'''
	recorrido = None

	if tipo_viaje == VIAJE_OPTIMO:
		recorrido = grafo_utilities.viajante(mapa, origen)
	elif tipo_viaje == VIAJE_APROXIMADO:
		recorrido = grafo_utilities.viajante_aproximado(mapa, origen)

	_exportar_archivo_kml(CMD_VIAJE + " " + tipo_viaje + ", " + origen, ruta_salida, recorrido, info_ciudades)
	_imprimir_recorrido(mapa, recorrido)

def itinerario(mapa, recomendaciones, info_ciudades, ruta_salida):
	'''
	Permite ejecutar el comando 'itinerario'.
	mapa: el grafo fue creado.
	recomendaciones: ruta de un archivo CSV de recomendaciones.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_salida: ruta indicada donde exportar el archivo KML.
	'''
	mapa_recomendaciones = Grafo(True)
	_cargar_vertices_grafo(mapa, mapa_recomendaciones)
	_cargar_aristas_desde_csv(recomendaciones, mapa_recomendaciones)
	itinerario = grafo_utilities.orden_topologico(mapa_recomendaciones)
	_exportar_archivo_kml(CMD_ITINERARIO + " " + recomendaciones, ruta_salida, itinerario, info_ciudades)
	_imprimir_recorrido(mapa, itinerario)

def reducir_caminos(mapa, info_ciudades, ruta_salida):
	'''
	Permite ejecutar el comando 'reducir_caminos'.
	mapa: el grafo fue creado.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_salida: ruta indicada donde exportar el archivo KML.
	'''
	arbol = grafo_utilities.arbol_tendido_minimo(mapa)
	camino_reducido = []
	peso_total = _calcular_peso_total_mst(arbol, camino_reducido)
	_exportar_camino_reducido(ruta_salida, info_ciudades, camino_reducido)
	print("Peso total: {}".format(peso_total))