# Implementar una función, que dado un grafo G, un vértice V y un número natural N, devuelva una lista con todos los vértices
# del grafo G que se encuentren a N pasos del vértice V. (Puede implementarse en pseudocódigo).
# ¿De qué orden es la solución implementada? Haga una mínima explicación de la implementación,
# si cree que el código no es suficientemente claro.

# Uso recorrido BFS sin usar un diccionario para los padres.
def n_pasos_de_vertice(grafo, v, n):

    visitados = {}
    orden = {}
    visitados[v] = True
    orden[v] = 0
    resul = []
    q = cola()
    q.encolar(v)
    
    # Recorrido BFS
    while not cola_esta_vacia(q):
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados[w] = True
                orden[w] = orden[v] + 1
                q.encolar(w)

    # Chequeo cuales vertices estan a N pasos
    # del vertice (v)
    for v in orden:
        if orden[v] == n:
            resul.append(v)

    return resul

# La solucion implementada es de O (V + E) donde 'V' es la cantidad de vertices y 'E' la cantidad
# de aristas. Es un recorrido BFS sin usar un diccionario para los padres. Este orden se obtiene
# si la forma de representacion del grafo es una lista de adyacencia o un diccionario de diccionarios