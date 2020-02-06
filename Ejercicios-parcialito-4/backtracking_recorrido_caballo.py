"""
El problema del recorrido del caballo de ajedrez consiste en indicar una serie de 64 movimientos para que un
caballo que se encuentra en una dada posición del tablero pise todas las casillas sin repetir ninguna.

Escribir el pseudocódigo de una función bool recorrido_del_caballo(A, x, y, i) que resuelva este problema
usando backtracking sabiendo que:

-El parámetro A es una matriz de enteros de 8x8.
-Los parámetros x e y indican la posición actual del caballo.
-i es el número de paso actual.
-La función devuelve true o false de acuerdo a si se encontró un recorrido o no.
-Se tiene una función obtener_movimientos(x, y) que dada una posición devuelve una lista con todos 
los movimientos posibles, descartando sólo aquellos que se excedan del tablero.

Inicialmente la función se llama con A llena de ceros, algún par de puntos x e y (entre 0 y 8) e i igual a 0. Si la
función devuelve true debe completar la matriz con el orden en el cual se visita cada casilla.
"""

CANT_FINAL = 64

def recorrido_del_caballo(A, x, y, i):

	if i == CANT_FINAL:
		return True

	movimientos_posibles = obtener_movimientos(x,y)
	# Pruebo todos los movimientos posibles para la posicion actual
	for m in movimientos_posibles:
		x_actual, y_actual = m
		# Si puedo moverme hacia esa posicion, me muevo
		if A[x_actual][y_actual] == 0:
			A[x_actual][y_actual] = i
			i += 1
			# Llamo recursivamente para la nueva posicion y pruebo todas
			# las posibles posiciones desde ahi. Si devuelve false hago backtrack
			if recorrido_del_caballo(A, x_actual, y_actual, i):
				return True
			else:
				# Backtrack
				A[x_actual][y_actual] = 0
				i -= 1
	return False