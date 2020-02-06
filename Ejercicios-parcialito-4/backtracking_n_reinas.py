"""
Implemente el pseudocodigo de un algoritmo de backtracking que resuelva el 
problema de las 8 Reinas (colocar 8 reinas en un tablero de 8x8 de manera,
que no se amenacen entre ellas). Puede considerar que ya posee la funcion es_valida()
que recibe una solucion parcial e indica si la misma es valida

Ayuda: puede representarse la solucion con un arreglo. Ejemplo: [4,6,8,2,7,1,3,5]
indica que las reinas fueron colocadas en las posiciones [(1,4), (2,6), (3,8)], etc.
"""

# Realizo el problema como si fuera N Reinas

def n_reinas(tablero, fila, n):

	# Caso base donde todas las reinas fueron
	# puestas
	if fila == n:
		return es_valida(tablero, n)

	# Chequeo si la opcion elegida es valida o no
	# Puedo meter esta condicion antes de realizar el paso de tablero[fila][col] = 1
	if not es_valida(tablero, n):
		return False

	for col in range(n):
		tablero[fila][col] = 1
		# Llamo recursivamente para mirar todas las opciones
		# disponibles a partir de la nueva reina posicionada
		if n_reinas(tablero, fila + 1, n):
			return True
		else:
			# Backtrack
			tablero[fila][col] = 0

	return False
