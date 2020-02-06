"""
Como el servicio meteorológico nacional ha anunciado una fuerte tormenta debe refugiar los barcos en sus muelles lo más rapido posible.
Sabiendo que el muelle i puede almacenar M[i] barcos y que la distancia entre el muelle i y el barco j es D[i][j], implementar
en pseudocódigo un algoritmo Greedy que decida en que muelle se debe almacenar cada barco minimizando la distancia total a recorrer
"""

def refugiar_barcos(muelles, barcos, distancia_barcos):

	# La solucion sera una lista donde el barco barcos[j] debera recorrer una distancia solucion[j]
	solucion = []

	# Voy recorriendo todos los barcos y seteo la menor distancia
	# con el primer valor de inicio
	for j in range(len(barcos)):
		distancia_menor = distancia_barcos[0][0]
		num_muelle = 0
		# Por cada muelle voy probando, si la distancia al muelle[i][j] es menor
		# a la distancia menor actual y el muelle admite barcos entonces es una solucion
		for i in range(len(muelles)):
			if distancia_barcos[i][j] < distancia_menor and muelles[i] > 0:
				distancia_menor = distancia_barcos[i][j]
				num_muelle = i
		muelles[num_muelle] -= 1
		solucion.append(distancia_menor)

	return solucion


