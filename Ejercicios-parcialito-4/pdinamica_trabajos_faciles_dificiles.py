'''
Se tiene una serie de trabajos faciles y dificiles. Cada dia i se puede optar
por hacer un trabajo facil o dificil, donde la ganancia por ese trabajo
esta dada por facil[i] y dificil[i]. Si en el dia i se hace un trabajo
dificil, no se puede haber trabajado el dia anterior (i-1) (ya que hay que preparar las maquinas)

Implementar un algoritmo utilizando la tecnica de programacion dinamica, que
devuelva la maxima ganancia que se puede obtener en N dias. Indicar y justificar
el orden del algoritmo.
'''

# ganancia[i] = 0 si i == 0
# 			  = facil[i] si i == 1
# 			  = max(ganancia[i-1] + facil[i], g[i-2] + dificil[i])

def calcular_ganancia(facil, dificil, dias):

	# Creo el array de ganancias lleno de 0
	ganancia = [0 for x in range(dias + 1)]

	# Recorro todo llenando segun la ecuacion
	# de recurrencia
	for i in range(len(ganancia)):
		if i == 0:
			ganancia[i] = 0
		elif i == 1:
			ganancia[i] = facil[i]
		else:
			ganancia[i] = max(ganancia[i - 1] + facil[i], ganancia[i - 2] + dificil[i])

	return ganancia[dias]

# El orden del algoritmo es O(n) siendo 'n' la cantidad de dias, ya que debo
# recorrer todo el array de ganancias e ir completandolo segun la ecuacion
# de recurrencia realizando operaciones de costo O(1)


