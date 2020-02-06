import sys
import csv
import comandos
from constantes import *
from grafo import Grafo

# *****************************************************************
#                   FUNCIONES AUXILIARES
# *****************************************************************

def _ejecutar_comando(linea_comando, sedes, info_ciudades, ruta_archivo_mapa):
	'''
	Ejecuta el comando correspondiente.
	linea_comando: comando recibido por stdin.
	sedes: el grafo fue creado.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_archivo_mapa: ruta indicada donde exportar el archivo KML.
	Devuelve True o False segun si se pudo realizar la operacion.
	'''
	comando_aux = linea_comando[0].split()

	if comando_aux[CAMPO_CMD] == CMD_IR:
		if len(comando_aux) >= 2:
			desde = " ".join(comando_aux[1:])
		if len(linea_comando) != 2:
			print("{} {}".format(ERROR_CMD, CMD_IR), sys.stderr)
			return False
		comandos.ir_desde_hasta(sedes, desde, linea_comando[1][1:], info_ciudades, ruta_archivo_mapa)
		return True

	if comando_aux[CAMPO_CMD] == CMD_VIAJE:
		if len(comando_aux) >= 2:
			tipo_viaje = " ".join(comando_aux[1:])
		if len(linea_comando) != 2:
			print("{} {}".format(ERROR_CMD, CMD_VIAJE), sys.stderr)
			return False
		comandos.viajar_desde(sedes, linea_comando[1][1:], tipo_viaje, info_ciudades, ruta_archivo_mapa)
		return True

	if comando_aux[CAMPO_CMD] == CMD_ITINERARIO:
		if len(comando_aux) != 2:
			print("{} {}".format(ERROR_CMD, CMD_ITINERARIO), sys.stderr)
			return False
		comandos.itinerario(sedes, comando_aux[RECOMENDACIONES], info_ciudades, ruta_archivo_mapa)
		return True

	if comando_aux[CAMPO_CMD] == CMD_REDUCIR_CAMINOS:
		if len(comando_aux) != 2:
			print("{} {}".format(ERROR_CMD, CMD_REDUCIR_CAMINOS), sys.stderr)
			return False
		comandos.reducir_caminos(sedes, info_ciudades, comando_aux[RUTA_SALIDA])
		return True

	else:
		print("{} {}".format(ERROR_CMD, comando_aux[CAMPO_CMD]), sys.stderr)
		return False

def _leer_entrada_estandar(sedes, info_ciudades, ruta_archivo_mapa):
	'''
	Lee los comandos ingresados por entrada estandar.
	sedes: el grafo fue creado.
	info_ciudades: diccionario que posee como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	ruta_archivo_mapa: ruta indicada donde exportar el archivo KML.
	'''
	for linea in sys.stdin:
		linea = linea.rstrip("\n")
		linea_aux = linea.split(",")
		if not _ejecutar_comando(linea_aux, sedes, info_ciudades, ruta_archivo_mapa):
			break

def _crear_grafo_desde_csv(ruta_archivo, info_ciudades):
	'''
	Crea y completa un grafo a partir de un archivo CSV.
	ruta_archivo: ruta del archivo CSV.
	info_ciudades: diccionario que va a poseer como clave los nombres de las ciudades
	y como dato una tupla del estilo (longitud, latitud).
	Devuelve un grafo completo.
	'''
	grafo = Grafo()
	with open(ruta_archivo, 'r') as file:
		reader = csv.reader(file)
		cant_ciudades = next(reader)
		for i in range(int(cant_ciudades[CAMPO_CIUDAD])):
			datos = next(reader)
			grafo.agregar_vertice(datos[CAMPO_CIUDAD])
			info_ciudades[datos[CAMPO_CIUDAD]] = (datos[CAMPO_LONGITUD], datos[CAMPO_LATITUD])
		next(reader)
		for linea in reader:
			grafo.agregar_arista(linea[CIUDAD_ORIGEN], linea[CIUDAD_DESTINO], int(linea[PESO_ARISTA]))

	return grafo

# *****************************************************************
#                       FUNCION PRINCIPAL
# *****************************************************************

def main():

	if len(sys.argv) != 3:
		print(ERROR_CANT_PARAMETROS)
		return

	info_ciudades = {}
	sedes = _crear_grafo_desde_csv(sys.argv[DATOS_CIUDADES], info_ciudades)
	_leer_entrada_estandar(sedes, info_ciudades, sys.argv[KML_SALIDA])


if __name__ == "__main__":
	main()
