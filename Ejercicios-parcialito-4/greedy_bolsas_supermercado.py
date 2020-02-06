""" 
Las bolsas de un supermercado se cobran por separado y soportan hasta un peso máximo P, por encima del cual se rompen.
Implementar el pseudocódigo de un algoritmo greedy que, teniendo una lista de pesos de n productos comprados,
encuentre la mejor forma de distribuir los productos en la menor cantidad posible de bolsas.
Realizar el seguimiento del algoritmo propuesto para bolsas con peso máximo 5 y para una lista con los pesos:
[ 4, 2, 1, 3, 5 ]. ¿El algoritmo implementado encuentra siempre la solución óptima? Justificar.
"""

P_MAX = 10 # kg

def bolsas_supermercado(productos_comprados):

	cant_bolsas = 0
	peso_restante = P_MAX
	# Supongo que todo producto es menor o igual a P_MAX
	# Ordeno y pongo los mas pesados al principio
	productos_comprados.sort()
	for peso_producto in productos_comprados:
		if peso_restante > peso_producto:
			peso_restante -= peso_producto
			continue
		cant_bolsas += 1
		peso_restante = P_MAX
	return cant_bolsas


# Seguimiento de codigo:
# Ordenando la lista de pesos: [5, 4, 3, 2, 1]
# Primer producto (peso 5) ocupa todo una bolsa. bolsas = 1
# Segundo producto (peso 4) no ocupa todo una bolsa. Peso restante bolsa = 1, bolsas = 1
# Tercer producto (peso 3) no alcanza el peso restante de la bolsa anterior. Peso restante bolsa = 2, bolsas = 2
# Cuarto prodcuto (peso 2) alcanza justo para llenar la bolsa anterior. Peso restante bolsa = 0, bolsas = 3
# Quinto producto (peso 1) no ocupa todo una bolsa. Peso restante bolsa = 4. bolsas = 4


# Considerando el ejemplo del enunciado, el algoritmo propusto no encuentra siempre la solucion optima
# ya que por ejemplo se puede lograr una cantidad de 3 bolsas, si por ejemplo, meto los productos con pesos
# de forma que su suma den el maximo de peso admitido por la bolsa. Es decir, puedo meter 4 y 1 juntos, 3 y 2 juntos
# y 5 solo --> total bolsas = 3

