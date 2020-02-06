"""
Se tiene una grilla de m x n casilleros con obstaculos y se sabe que solo se
puede mover hacia abajo y hacia la derecha por los lugares sin obstaculos.

Determinar la cantidad de caminos posibles que hay para llegar desde el
casillero (0,0) hasta el casillero (m-1,n-1)
"""

def calcular_caminos(m, n):

	matriz = [[1 for x in range(m)] for x in range(n)]

	for i in range(1, m):
		for j in range(1, n):
			if matriz[i][j] == OBSTACULO:
				continue
			matriz[i][j] = matriz[i - 1][j] + matriz[i][j - 1]

	return matriz[m - 1][n - 1]


