'''
Se cuenta con varios productos dados por un arreglo R donde R[i] indica
el precio del producto i. Cada dia se debe comprar uno (y solo uno) de los
productos. Ademas, se acerca la temporada de ski y los oriundos de un famoso
pueblo al extremo sur de Neuquen, saben que en temporada alta aumentan los
precios todos los dias. Tal es asi, que el precio del producto i, el dia j
es R[i]^j (j comenzando en 1).

Implementar un algoritmo Greedy que nos indique el precio minimo total al que
podemos comprar todos los productos.

Explicar brevemente por que el algoritmo implementado es Greedy, e indicar
y justificar el orden del algoritmo.
'''

def calcular_precio_minimo(productos):

	# Ordeno el arreglo de mayor a menor ya que los precios de los
	# productos crecen dia a dia exponencialmente.
	productos_ordenados = productos.sorted()
	precio_minimo_total = 0

	# Suponiendo que hay tantas cantidad de dias como
	# productos, por cada dia voy comprando el mas caro
	# 
	for i in range(len(productos)):
		precio_minimo_total += productos_ordenados[i] ** (i + 1)

	return precio_minimo_total

# Orden del algoritmo: O(nlogn) (por el ordenamiento) siendo 'n' la cantidad de productos.