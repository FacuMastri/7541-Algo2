#define _POSIX_C_SOURCE 200809L // strdup

#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "pila.h"

/* Definición del struct abb, nodo de abb e iterador. */

typedef struct abb_nodo {

    char* clave;
    void* dato;
    struct abb_nodo* izquierda;
    struct abb_nodo* derecha;
} abb_nodo_t;

struct abb {

	abb_nodo_t* raiz;
	size_t cantidad;
    abb_comparar_clave_t comparar_clave;
    abb_destruir_dato_t destruir_dato;  
};

struct abb_iter {

    pila_t* pila;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

/**
 * Crea un nodo.
 * @param  clave: clave asociada al nodo a crear.
 * @param  dato: dato asociado al nodo a crear.
 * @return nodo con su par clave, dato almacenado.
 */
abb_nodo_t* abb_nodo_crear(const char* clave, void* dato) {

    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
    if (!nodo) {
        return NULL;
    }

    // Copio la clave pasada por parámetro.
    char* clave_aux = strdup(clave);
    if (!clave_aux) {
        return NULL;
    }

    nodo->clave = clave_aux;
    nodo->dato = dato;
    nodo->derecha = NULL;
    nodo->izquierda = NULL;

    return nodo;
}

/**
 * Destruye un nodo.
 * @param nodo: el nodo fue creado.
 * @return dato del nodo.
 */
void* abb_nodo_destruir(abb_nodo_t* nodo) {

    void* dato = nodo->dato;
    // Libero la copia de la clave.
    free(nodo->clave); 
    free(nodo);

    return dato;
}

/**
 * Función recursiva de abb_destruir. Destruye todos los nodos de un árbol.
 * @param destruir_dato: función de destrucción de dato.
 * @param nodo: el nodo fue creado.
 */
void abb_nodo_destruir_recursivo(abb_destruir_dato_t destruir_dato, abb_nodo_t* nodo) {

    if (!nodo) {
        return;
    }

    abb_nodo_destruir_recursivo(destruir_dato, nodo->izquierda);
    abb_nodo_destruir_recursivo(destruir_dato, nodo->derecha);
    void* dato = abb_nodo_destruir(nodo);
    if (destruir_dato) {
        destruir_dato(dato);
    }
}

/**
 * Busca un nodo dentro de un árbol.
 * @param  comparar_clave: función de comparación de claves.
 * @param  nodo: el nodo fue creado.
 * @param  clave: clave a buscar.
 * @return el nodo buscado o NULL en caso de no encontrarlo.
 */
abb_nodo_t* abb_buscar_nodo(abb_comparar_clave_t comparar_clave, abb_nodo_t* nodo, const char* clave) {

    if (!nodo) {
        return NULL;
    }
    int res_comparacion = comparar_clave(nodo->clave, clave);

    if (res_comparacion == 0) {
        return nodo;
    }
    if (res_comparacion < 0) {
        return abb_buscar_nodo(comparar_clave, nodo->derecha, clave);
    }

    return abb_buscar_nodo(comparar_clave, nodo->izquierda, clave); 
}

/**
 * Busca el padre de un nodo.
 * @param  comparar_clave: función de comparación de claves.
 * @param  nodo: el nodo fue creado.
 * @param  clave: clave del hijo.
 * @return padre del nodo que tiene la clave buscada.
 */
abb_nodo_t* abb_buscar_padre(abb_comparar_clave_t comparar_clave, abb_nodo_t* nodo, const char* clave) {

    // Caso donde se busca el padre de la raiz.
    if (comparar_clave(nodo->clave, clave) == 0) {
        return NULL;
    }

    if ((nodo->derecha && comparar_clave(nodo->derecha->clave, clave) == 0) ||
       (nodo->izquierda && comparar_clave(nodo->izquierda->clave, clave) == 0)) {
        return nodo;
    }
    if (comparar_clave(nodo->clave, clave) < 0) {
        if (!nodo->derecha) {
            return nodo;
        }
        return abb_buscar_padre(comparar_clave, nodo->derecha, clave);
    } else {
        if (!nodo->izquierda) {
            return nodo;
        }
        return abb_buscar_padre(comparar_clave, nodo->izquierda, clave);
    }
}

/**
 * Actualiza el dato de un nodo.
 * @param  destruir_dato: función de destrucción de datos, puede ser NULL.
 * @param  actual: el nodo fue creado.
 * @param  dato: nuevo dato del nodo.
 * @return True indicando que se realizo la operación.
 */
bool abb_nodo_actualizar(abb_destruir_dato_t destruir_dato, abb_nodo_t* actual, void* dato) {

    if (destruir_dato) {
        destruir_dato(actual->dato);
    }
    actual->dato = dato;

    return true;
}

/**
 * Guarda un nodo dentro de un árbol.
 * @param  arbol: el árbol fue creado.
 * @param  actual: el nodo fue creado.
 * @param  clave: clave del nuevo nodo.
 * @param  dato: dato del nuevo nodo.
 * @return True o False según si se pudo realizar la operación o no.
 */
bool abb_guardar_aux(abb_t* arbol, abb_nodo_t* actual, const char* clave, void* dato) {

    abb_nodo_t* nodo = abb_nodo_crear(clave, dato);
    if (!nodo) {
        return false;
    }

    abb_nodo_t* padre = abb_buscar_padre(arbol->comparar_clave, actual, clave);
    if (!padre && !arbol->raiz) {
        arbol->raiz = nodo;
    } else if (!padre) {
        abb_nodo_destruir(nodo);
        return abb_nodo_actualizar(arbol->destruir_dato, arbol->raiz, dato);
    } else if (padre->derecha && arbol->comparar_clave(clave, padre->derecha->clave) == 0) {
        abb_nodo_destruir(nodo);
        return abb_nodo_actualizar(arbol->destruir_dato, padre->derecha, dato);
    } else if (padre->izquierda && arbol->comparar_clave(clave, padre->izquierda->clave) == 0) {
        abb_nodo_destruir(nodo);
        return abb_nodo_actualizar(arbol->destruir_dato, padre->izquierda, dato);
    } else if (arbol->comparar_clave(clave, padre->clave) < 0) {
        padre->izquierda = nodo;
    } else if (arbol->comparar_clave(clave, padre->clave) > 0) {
        padre->derecha = nodo;
    }

    arbol->cantidad++;
    return true;
}

/**
 * Calcula la cantidad de hijos de un nodo.
 * @param  nodo: el nodo fue creado.
 * @return cantidad de hijos de un nodo.
 */
size_t abb_nodo_calcular_cant_hijos(abb_nodo_t* nodo) {

	if (nodo->derecha && nodo->izquierda) {
		return 2;
	} 
    if ((!nodo->derecha && nodo->izquierda) || (!nodo->izquierda && nodo->derecha)) {
		return 1;
	}
    
	return 0;
}

/**
 * Busca el menor hijo izquierdo de un nodo.
 * @param  nodo: el nodo fue creado.
 */
abb_nodo_t* abb_nodo_buscar_reemplazante(abb_nodo_t* nodo) {

	abb_nodo_t* actual = nodo;

	while (actual->izquierda) {
        actual = actual->izquierda;
	}

	return actual;
}

/**
 * Borra un nodo sin hijos.
 * @param arbol: el árbol fue creado.
 * @param nodo: el nodo fue creado.
 * @param padre: el nodo fue creado o NULL si el nodo a borrar es la raiz. 
 */
void* abb_nodo_borrar_sin_hijos(abb_t* arbol, abb_nodo_t* nodo, abb_nodo_t* padre) {

    if (!padre) {
        arbol->raiz = NULL;
    } else if (padre->derecha && arbol->comparar_clave(padre->derecha->clave, nodo->clave) == 0) {
        padre->derecha = NULL;
    } else if (padre->izquierda && arbol->comparar_clave(padre->izquierda->clave, nodo->clave) == 0) {
        padre->izquierda = NULL;
    }

    arbol->cantidad--;
    return abb_nodo_destruir(nodo);
}

/**
 * Borra un nodo con un único hijo.
 * @param arbol: el árbol fue creado.
 * @param actual: el nodo fue creado.
 * @param padre: el nodo fue creado.
 * @return dato del nodo borrado.
 */
void* abb_nodo_borrar_unico_hijo(abb_t* arbol, abb_nodo_t* actual, abb_nodo_t* padre) {

    if (actual->izquierda) {
        if (!padre) {
            arbol->raiz = actual->izquierda;
        } else if (padre->derecha && arbol->comparar_clave(padre->derecha->clave, actual->clave) == 0) {
            padre->derecha = actual->izquierda;
        } else if (padre->izquierda && arbol->comparar_clave(padre->izquierda->clave, actual->clave) == 0) {
            padre->izquierda = actual->izquierda;
        }
    } else if (actual->derecha) {
        if (!padre) {
            arbol->raiz = actual->derecha;
        } else if (padre->derecha && arbol->comparar_clave(padre->derecha->clave, actual->clave) == 0) {
            padre->derecha = actual->derecha;
        } else if (padre->izquierda && arbol->comparar_clave(padre->izquierda->clave, actual->clave) == 0) {
            padre->izquierda = actual->derecha;
        }
    }

    arbol->cantidad--;
    return abb_nodo_destruir(actual);
}

/**
 * Borra un nodo con dos hijos.
 * @param arbol: el árbol fue creado.
 * @param actual: el nodo fue creado.
 * @return dato del nodo borrado.
 */
void* abb_nodo_borrar_con_dos_hijos(abb_t* arbol, abb_nodo_t* actual) {

    abb_nodo_t* reemplazante = abb_nodo_buscar_reemplazante(actual->derecha);
    char* clave_aux = strdup(reemplazante->clave);
    
    // El reemplazante a lo sumo tendrá 1 hijo.
    void* dato_aux = abb_borrar(arbol, reemplazante->clave);
    void* dato = actual->dato;
    actual->dato = dato_aux;
    free(actual->clave);
    actual->clave = clave_aux;

    return dato;
}

/**
 * Función recursiva de abb_borrar.
 * @param arbol: el árbol fue creado.
 * @param actual: el nodo fue creado.
 * @param clave: clave del nodo a borrar.
 * @return dato del nodo borrado.
 */
void* abb_borrar_aux(abb_t* arbol, abb_nodo_t* actual, const char* clave) {

    abb_nodo_t* nodo_a_borrar = abb_buscar_nodo(arbol->comparar_clave, actual, clave);
    size_t cant_hijos = abb_nodo_calcular_cant_hijos(nodo_a_borrar);

    if (cant_hijos == 0) {
        abb_nodo_t* padre = abb_buscar_padre(arbol->comparar_clave, actual, clave);
        return abb_nodo_borrar_sin_hijos(arbol, nodo_a_borrar, padre);
    }
    if (cant_hijos == 1) {
        abb_nodo_t* padre = abb_buscar_padre(arbol->comparar_clave, actual, clave);
        return abb_nodo_borrar_unico_hijo(arbol, nodo_a_borrar, padre);
    }
    
    return abb_nodo_borrar_con_dos_hijos(arbol, nodo_a_borrar);
}

/**
 * Apila todos los hijos izquierdos de un nodo.
 * @param pila: la pila fue creada.
 * @param nodo: el nodo fue creado.
 */
void pila_apilar_izquierdos(pila_t* pila, abb_nodo_t* nodo) {

	if (!nodo) {
		return;
	}

	pila_apilar(pila, nodo);
	pila_apilar_izquierdos(pila, nodo->izquierda);
}

/**
 * Visita in-order los nodos cuyas claves se encuentren entre la clave
 * de inicio y la clave final.
 * @param nodo: el nodo fue creado
 * @param visitar: funcion que utiliza la clave de un nodo.
 * @param clave_inicio
 * @param clave_final
 * @param comparar_clave: funcion de comparacion
 */
void abb_in_order_visitar(abb_nodo_t* nodo, bool visitar(const char *), char* clave_inicio, char* clave_final, abb_comparar_clave_t comparar_clave) {

    if (!nodo) {
        return;
    }
    if (comparar_clave(nodo->clave, clave_inicio) > 0) {
        abb_in_order_visitar(nodo->izquierda, visitar, clave_inicio, clave_final, comparar_clave);
    }
    if (comparar_clave(clave_inicio, nodo->clave) <= 0 && comparar_clave(clave_final, nodo->clave) >= 0) {
        if (!visitar(nodo->clave)) {
            return;
        }
    }
    if (comparar_clave(clave_final, nodo->clave) > 0) {
        abb_in_order_visitar(nodo->derecha, visitar, clave_inicio, clave_final, comparar_clave);
    }
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {

    abb_t* arbol = malloc(sizeof(abb_t));
    if (!arbol) {
        return NULL;
    }

    arbol->raiz = NULL;
    arbol->cantidad = 0;
    arbol->comparar_clave = cmp;
    arbol->destruir_dato = destruir_dato;

    return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {

    if (!arbol->raiz && abb_cantidad(arbol) == 0) {
        abb_nodo_t* raiz_aux = abb_nodo_crear(clave, dato);
        if (!raiz_aux) {
            return false;
        }
        arbol->raiz = raiz_aux;
        arbol->cantidad++;
        return true;
    }

    return abb_guardar_aux(arbol, arbol->raiz, clave, dato);
}

void *abb_borrar(abb_t *arbol, const char *clave) {

    if (!abb_pertenece(arbol, clave)) {
        return NULL;
    }

    return abb_borrar_aux(arbol, arbol->raiz, clave);
}

void *abb_obtener(const abb_t *arbol, const char *clave) {

    abb_nodo_t* nodo = abb_buscar_nodo(arbol->comparar_clave, arbol->raiz, clave);
    if (!nodo) {
        return NULL;
    }

    return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {

    abb_nodo_t* nodo = abb_buscar_nodo(arbol->comparar_clave, arbol->raiz, clave);
    if (!nodo) {
        return false;
    }
    return true;
}

size_t abb_cantidad(abb_t *arbol) {

	return arbol->cantidad;
}

void abb_destruir(abb_t *arbol) {

    abb_nodo_destruir_recursivo(arbol->destruir_dato, arbol->raiz);
    free(arbol);
}

/* *****************************************************************
 *                   PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {

    pila_t* pila = pila_crear();
    if (!pila) {
        return;
    }

    pila_apilar_izquierdos(pila, arbol->raiz);
    abb_nodo_t* actual = pila_desapilar(pila);

    while (actual && visitar(actual->clave, actual->dato, extra)) {
        pila_apilar_izquierdos(pila, actual->derecha);
        actual = pila_desapilar(pila);
    }

    pila_destruir(pila);
}

void abb_in_order_range(abb_t *arbol, bool visitar(const char *), char* clave_inicio, char* clave_final) {

    abb_in_order_visitar(arbol->raiz, visitar, clave_inicio, clave_final, arbol->comparar_clave);
}

/* *****************************************************************
 *                   PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {

    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) {
        return NULL;
    }

    pila_t* pila = pila_crear();
    if (!pila) {
    	free(iter);
        return NULL;
    }

    iter->pila = pila;
    // Apilo raíz y todos los hijos izquierdos.
    pila_apilar_izquierdos(iter->pila, arbol->raiz);

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {

    if (abb_iter_in_al_final(iter)) {
        return false;
    }
    // Desapilo, y apilo el hijo derecho del desapilado junto
    // con todos sus hijos izquierdos.
    abb_nodo_t* actual = pila_desapilar(iter->pila);
    pila_apilar_izquierdos(iter->pila, actual->derecha);

    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {

    if (abb_iter_in_al_final(iter)) {
        return NULL;
    }

    return ((abb_nodo_t*) pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {

	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {

	pila_destruir(iter->pila);
	free(iter);
}