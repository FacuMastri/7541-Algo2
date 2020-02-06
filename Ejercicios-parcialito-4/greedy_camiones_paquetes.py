"""
Se tienen paquetes que se quieren transportar, y camiones para realizar dichos transportes. 
Cada camión puede utilizarse más de una vez, y puede utilizarse para algunos paquetes 
(no todos los camiones pueden transportar todos los paquetes, se conoce cuáles paquetes puede llevar cada camión)
y cada camión tiene un costo de envío diferente (por cada paquete se debe realizar un envío por separado).

Proponer, en pseudocódigo, un algoritmo Greedy que permita determinar qué camiones utilizar para cada paquete,
de forma de minimizar los costos. 
¿Por qué el algoritmo implementado es de tipo Greedy?
¿Cuál es el orden de dicho algoritmo? ¿Es óptima (siempre) la solución? Justificar.
"""

def minimizar_costos(paquetes, camiones):

	costo_minimo = 0

	for paquete in paquetes:
		minimo_costo_paquete = camiones[0][0] # Camiones es una lista de tuplas de la forma: (costo_envio, tipo_de_paquete_aceptado)
		for camion in camiones:
			if camion[0] < minimo_costo_paquete and camion_puede_transportar(camion[1], paquete) and camion_esta_desocupado(camion):
				minimo_costo_paquete = camion[0]
		costo_minimo += minimo_costo_paquete

	return costo_minimo

# El algoritmo implementado es greedy porque espera que, a medidad de ir encontrando optimos locales, llegar al optimo global
# 
# El orden del algoritmo es O(p*c) siendo 'p' la cantidad de paquetes y 'c' la cantidad de camiones ya que debo recorrer por cada
# paquete toda la lista de camiones para encontrar la mejor solucion.
# 
# La solucion no es optima, ya que el algoritmo propuesto busca encontrar el menor costo de envio para cada paquete provocando que
# ese camion deje de ser utilizable. Supongamos que tenemos dos paquetes (A y B), al buscar el menor costo de envio nos encontramos
# con un camion que tiene un costo 5 para el paquete A pero a su vez tiene un costo 2 para el paquete B. Al elegir ese camion
# para el paquete A, el paquete B queda libre para otro camion cuyo costo minimo es 10 para ambos paquetes, generando un total de 15 de costo de envio.
# Si el paquete B hubiera elegido el camion 1 y el paquete A elegia el camion 2 entonces se tendria un costo de 12 de envio.