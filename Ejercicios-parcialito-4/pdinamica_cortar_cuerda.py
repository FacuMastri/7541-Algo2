"""
Se tiene un cable de largo "n" y una tabla de precios segun el largo. Sabiendo
que se lo puede dividir para aumentar el valor, implementar un algoritmo
que indique cual es el mayor valor que se le puede sacar al cable usando
programacion dinamica.

Indicar el orden del algoritmo.

Ejemplo: si P(1) = 1, P(2) = 5, P(3) = 8 y P(4) = 9, para n = 4 el algoritmo
debe devolver 10 ya que se obtendria su maximo valor cortandolo por la mitad.
Nota: se puede dividir el cable mas de una vez, o inclusive ninguna.
"""

MINIMO_INT = -23242424

def cortar_cuerda(precios, n):

	tabla_valores = [0 for x in range(n+1)]
	tabla_valores[0] = 0

	for i in range(1, n+1):
		valor_max = MINIMO_INT
		for j in range(i):
			valor_max = max(valor_max, precios[j] + tabla_valores[i-j-1])
		tabla_valores[i] = valor_max

	return tabla_valores[n]

# Orden del algoritmo: O(n^2) ya que seria como recorrer un array 2d. En el peor caso
# se completaria toda la tabla hasta llegar 