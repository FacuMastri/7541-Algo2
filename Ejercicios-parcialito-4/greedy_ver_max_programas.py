"""
Hannah esta muy triste porque el primero de julio un conocido servicio de 
streaming dejara de transmitir varias series que a ella le interesaban ver.
Sin embargo, su amigo Clay le comento que durante ese mismo dia se transmitiran
episodios en diferentes horarios.

Implementar un algoritmo greedy que dados los horarios de inicio y fin de
cada transmision nos devuelva la mayor cantidad de programas que puede llegar
a ver, teniendo en cuenta que pueden haber superposiciones de todo tipo.

Considerar que se cuenta con una funcion bool horarios_colisionan(ini_1, fin_1, ini_2, fin_2)

Indicar el orden del algoritmo propuesto.
"""

# Considerando que los horarios estan ordenados segun el horario de fin
def ver_max_cant_programas(horarios):
	''' horarios es una lista de tuplas (hora_inicio, hora_fin)'''

	#horarios_ordenados = ordenar_por_horario_fin(horarios)

	programas = []
	# Agrego el primer programa ya que siempre lo voy
	# a poder ver
	programas.append((horarios[0][0], horarios[0][1]))
	for horario in horarios:
		if not horarios_colisionan(horario[0], horario[1], programas[-1][0], programas[-1][1]):
			programas.append(horario)

	return len(programas)


# El orden del algoritmo es O(n) si los horarios estan ordenados segun el horario
# de fin. En el caso de que tengamos que ordenar los horarios quedaria O(nlogn)