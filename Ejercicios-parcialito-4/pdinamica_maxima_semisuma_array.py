"""
Se define la maxima semisuma de un arreglo como un segmento del mismo en que
la suma de todos los elementos sea la mayor posible. Dado un arreglo de numeros
reales (que pueden ser positivos, negativos o cero) usando programacion dinamica
escribir el pseudocodigo de una funcion que devuelva el valor de la maxima semisuma

Pista: esta bien si necesitan recorrer dos veces el arreglo, una para calcular
el valor de la recurrencia y otra para encontrar la solucion al problema.

Ejemplo:
f([]) = 0
f([-6, 12, -7, 0, 14, -7, 5]) = 19 (la maxima semisuma esta entre los indices 1 y 4 inclusive)
f([4, 3, 9, 12, 8, 0, 2]) = 38 (son todos numeros positivos, la maxima semisuma es todo)
f([-2.5, -9, -4, -1.3, -9, -7]) = -1.3 (todos numeros negativos, la maxima semisuma es el mayor)
"""

# MS(i) = Max[MS(i-1) + A[i] , A[i]]

def max_semisuma_array(array, tamanio_array):

	maxima_semisuma = array[0]
	maximo_actual = array[0]

	for i in range(tamanio_array):
		maximo_actual = max(array[i], maximo_actual + array[i])
		maxima_semisuma = max(maximo_actual, maxima_semisuma)

	return maxima_semisuma


"""
Dado un arreglo de n números reales, se desea encontrar el valor máximo posible para la suma de una ventana
contigua. Por ejemplo, para el arreglo [3 -1 -5 6 7 -9], el valor máximo es 13, que se obtiene sumando 6 + 7.

Para resolverlo usando programación dinámica, se define M[i] como el valor máximo de ventana que se puede
obtener utilizando los primeros i elementos del arreglo. Para cada valor de i, el valor de M[i] se puede formar
extendiendo la ventana que termina en i - 1, o bien comenzando una ventana nueva en i.

a) Mostrar la relación de recurrencia. 
b) Mostrar paso por paso la resolución para el arreglo [-15 29 -36 3 -22 11 19 -5 0 4]. 
c) ¿De qué orden es el algoritmo en tiempo y memoria?
"""

# a) Relacion de recurrencia: MS(i) = Max[MS(i-1) + A[i] , A[i]]
# c)O(n) tiempo y O(1) espacio