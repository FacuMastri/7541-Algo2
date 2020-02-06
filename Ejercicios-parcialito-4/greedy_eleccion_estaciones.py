"""
Un camión debe viajar desde una ciudad a otra deteniéndose a cargar combustible cuando sea necesario.
El tanque de combustible le permite viajar hasta K kilometros.

Las estaciones se encuentran distribuidas a lo largo de la ruta siendo d(i) la distancia
desde la estación i-1 a la estación i.

Implementar un algoritmo que decida en qué estaciones debe cargar combustible
de manera que se detenga la menor cantidad de veces posible
"""


def calcular_menor_cant_detenimientos(K, estaciones, total_km):

	# Agregamos una estacion de mentira al final del camino, para no tener
	# que considerar al final del camino como un caso especial
	if sum(estaciones) < total_km:
		estaciones.append(total_km - sum(estaciones))

	restante = K
	eleccion_estaciones = []
	for i in range(len(estaciones)):
		# Recorrido hasta una estacion, resto la distancia recorrida a lo
		# que me aguanta el tanque.
		restante -= estaciones[i]
		if estaciones[i + 1] > restante:
			# Si la siguiente estacion esta mas lejos de lo que yo
			# puedo recorrer --> agrego la estacion donde estaba y reseteo
			# el combustible
			eleccion_estaciones.append(estaciones[i])
			restante = K

	eleccion_estaciones.append(estaciones[-1])
	return eleccion_estaciones

