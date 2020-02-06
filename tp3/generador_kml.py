class GeneradorKml(object):
	'''Clase que representa un generador de archivos KML'''

	def __init__(self, titulo, ruta_salida):
		'''
		Crea un archivo KML.
		titulo: nombre del header principal del archivo.
		ruta_salida: ruta del archivo de salida.
		Post: el archivo fue creado.
		'''
		try:
			self.file = open(ruta_salida, "w")
		except IOError:
			return None
		self.salida = []
		self.coordenadas = []
		formato = ""
		formato += "<?xml version='1.0' encoding='UTF-8'?>\n"
		formato += "<kml xmlns='http://earth.google.com/kml/2.1'>\n"
		formato += "\t<Document>\n"
		formato += "\t\t<name>" + titulo + "</name>\n\n"
		self.salida.append(formato)

	def agregar_lugar(self, lugar, longitud, latitud):
		'''
		Agrega una locacion.
		lugar: string que representa una locacion.
		longitud: string que representa la longitud en un mapa del lugar
		(i.e.: -58.3679593)
		latitud: string que representa la latitud en un mapa del lugar
		(i.e.: -34.6176355)
		'''
		self.coordenadas.append((longitud, latitud))
		formato = ""
		formato += "\t\t<Placemark>\n"
		formato += "\t\t\t<name>" + lugar + "</name>\n"
		formato += "\t\t\t<Point>\n"
		formato += "\t\t\t\t<coordinates>" + longitud + ", " + latitud + "</coordinates>\n"
		formato += "\t\t\t</Point>\n"
		formato += "\t\t</Placemark>\n"
		self.salida.append(formato)

	def agregar_lineas(self):
		'''
		Agrega el recorrido entre dos puntos.
		'''
		formato = ""
		for i in range(len(self.coordenadas) - 1):
			if i == 0:
				formato += "\n\t\t<Placemark>\n"
			else:
				formato += "\t\t<Placemark>\n"
			formato += "\t\t\t<LineString>\n"
			formato += "\t\t\t\t<coordinates>" + self.coordenadas[i][0] + ", " + self.coordenadas[i][1] + " " + self.coordenadas[i + 1][0] + ", " + self.coordenadas[i + 1][1]
			formato += "</coordinates>\n"
			formato += "\t\t\t</LineString>\n"
			formato += "\t\t</Placemark>\n"
		self.salida.append(formato)

	def finalizar(self):
		'''
		Escribe en el archivo KML todo el contenido necesario.
		Post: el archivo fue cerrado.
		'''
		self.salida.append("\t</Document>\n</kml>")
		try:
			self.file.writelines(self.salida)
			return True
		except IOError:
			return False
		finally:
			self.file.close()