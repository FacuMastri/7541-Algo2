"""
Se quiere utilizar el Teorema de Pascal que define a los coeficientes binomiales de manera recursiva:

(n, k) = (n - 1, k - 1) + (n - 1, k) para 1 <= k <= n
(n, 0) = 1 para todo n >= 0
(0, k) = 0 para todo k > 0
(n, n) = 1 para todo n > 0

Implementar el pseudocodigo de un algoritmo que calcule (n, k) utilizando programacion
dinamica. 
Cual es el orden temporal y espacial del algoritmo?
"""


def calcular_coef_binomiales(n, k):

	# Creo la matriz para guardar los resultados, tambien podia hacer M = [n + 1][k + 1]
	M = [[0 for x in range(k + 1)] for x in range (n+1)]

	for i in range (n + 1):
		for j in range(min(i, k) + 1):
			# Caso base
			if j == 0 or j == i:
				M[i][j] = 1
			# Aplico 
			else:
				M[i][j] = M[i - 1][j - 1] + M[i - 1][j]

	return M[n][k]