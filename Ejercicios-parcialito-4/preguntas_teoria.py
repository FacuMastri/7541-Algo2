"""
a) ¿Qué condiciones debe cumplir un problema para poder resolverlo mediante Programación Dinámica? ¿Qué desventaja tiene esta técnica en general? 

Un problema debe cumplir, para que sea resuelto mediante PD, que posea optimal substructure and overlapping subproblems.
Optimal substructure = la solucion a un problema puede ser construida a traves de la solucion a los subproblemas.
Overlapping subproblems = hay un orden natural de los subproblemas de menor a mayor. Es decir, los subproblemas
"mayores" son resueltos mediante la composicion de problemas "menores".

b) ¿Bajo qué condiciones un algoritmo Greedy no encuentra la solución óptima a un problema? De un ejemplo.

Desventajas: uso de espacio para guardar las soluciones a los subproblemas, requiere mucha practica.

Un algoritmo greedy no encuentra la solucion optima a un problema cuando se plantea un contraejemplo al algoritmo. Por ejemplo:
en el problema de scheduling, si se ordenan los horarios de la charla segun su horario de inicio, se puede encontrar
con la primera charla que ocupe todo el tiempo disponible y asi solamente se obtendria 1 charla

2) Indicar verdadero o falso. Justificar:

c) Es posible encontrar el camino minimo entre dos vertices de un grafo no pesado usando BFS.

Verdadero, ya que al momento de visitar por primera vez un nodo, ese camino hasta ese nodo
es el camino mas corto desde el nodo de inicio.

d) Si buscamos el camino minimo entre dos vertices de un grafo pesado (pesos positivos) usando Dijkstra
el camino minimo encontrado puede no ser la solucion optima

Falso, Dijkstra se trata de un algoritmo greedy y trabaja como tal, es decir: busca el nodo
mas cercano al actual que todavia no haya sido visitado (optimo local) en pos de obtener un optimo global.
Ademas, no existe ejemplo donde se pruebe que Dijsktra devuelva una solucion no optima.

e) Si en A* la funcion heuristica es h(x) = 0, el algoritmo resultante es equivalente a Dijkstra.

Verdadero, ya que si h(x) = 0 entonces para cada vertice se elige el vertice siguiente
en funcion solo del costo total calculado hasta ese momento dando como resultado un comportamiento
igual al de Dijkstra.

"""