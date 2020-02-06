/*

Se tiene un árbol binario de búsqueda con cadenas como claves y función de comparación strcmp.
Implementar una primitiva lista_t* abb_mayores(const abb_t* abb, const char* cadena) que dado
un ABB y una cadena, devuelva una lista ordenada que contenga las claves del árbol que sean mayores a la
cadena recibida por parámetro (que no necesariamente está en el árbol).
Suponer que la estructura del TDA es:

typedef struct abb {
    const char* clave;
    struct abb* izq;
    struct abb* der;
} abb_t;

Aclaración: se debe realizar la menor cantidad posible de comparaciones

 */

bool aux_abb_mayores(const ab_t* arbol, lista_t* lista, const char* cadena) {

    // Condicion base de recursion: si no hay un nodo --> devuelvo false.
    if (!arbol) {
        return false;
    }

    // Primero llamo para toda la rama izquierda del arbol así me quedan
    // las claves ordenadas al insertar en la lista. RECORRIDO IN ORDER.
    aux_abb_mayores(arbol->izq, lista, cadena);
    if (strcmp(arbol->clave, cadena) > 0) {
        lista_insertar_ultimo(lista, arbol->clave);
    }

    // Una vez ya comparé el nodo actual y la izquierda, llamo recursivamente para la rama derecha.
    aux_abb_mayores(arbol->der, lista, cadena);

    return true;
}

lista_t* abb_mayores(const ab_t* abb, const char* cadena) {

    lista_t* mayores = lista_crear();
    if (!mayores) {
        return NULL;
    }

    aux_abb_mayores(abb, mayores);
 
    return mayores;
}