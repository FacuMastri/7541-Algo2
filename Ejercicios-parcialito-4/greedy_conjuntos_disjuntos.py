"""
Se tiene un arreglo con n enteros positivos, y se desea separar todos sus elementos en dos conjuntos disjuntos,
tales que la diferencia entre la suma de los elementos de cada conjunto sea mínima.

Diseñar un algoritmo greedy para formar los dos conjuntos. Indicar el orden de la solución.
"""

def formar_conjuntos(array, n):

	conjunto_1 = []
	conjunto_2 = []

	for i in range(n):
		if sum(conjunto_1) + array[i] < sum(conjunto_2) + array[i]:
			if array[i] not in conjunto_1:
				conjunto_1.append(array[i])
			else:
				conjunto_2.append(array[i])
		else:
			if array[i] not in conjunto_2:
				conjunto_2.append(array[i])
			else:
				conjunto_1.append(array[i])

# Orden O(n)