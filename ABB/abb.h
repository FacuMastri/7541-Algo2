#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct abb abb_t;
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);
typedef struct abb_iter abb_iter_t;

/* ******************************************************************
 *                  	PRIMITIVAS DEL ABB
 * *****************************************************************/

/**
 * Crea un nuevo árbol.
 * @param  cmp: función de comparación de claves.
 * @param  destruir_dato: función de destrucción de dato.
 * @return un nuevo árbol vacío.
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/**
 * Guarda una clave en el árbol.
 * @param  arbol: el árbol fue creado.
 * @param  clave: clave a guardar.
 * @param  dato: dato asociado a la clave.
 * @return True o False según si se logró guardar o no.
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/**
 * Borra un nodo del árbol.
 * @param  arbol: el árbol fue creado.
 * @param  clave: clave a buscar dentro del árbol.
 * @return dato asociado a la clave borrada o NULL si no existe.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/**
 * Obtiene el dato asociado a una clave del árbol.
 * @param  arbol: el árbol fue creado.
 * @param  clave: clave a buscar dentro del árbol.
 * @return dato asociado a la clave o NULL si no existe.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/**
 * Verifica si una clave pertenece a un árbol.
 * @param  arbol: el árbol fue creado.
 * @param  clave: clave a buscar dentro del árbol.
 * @return True o False según si la clave pertenece al árbol o no.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/**
 * Devuelve la cantidad de nodos de un árbol.
 * @param  arbol: el árbol fue creado.
 * @return cantidad de nodos de un árbol.
 */
size_t abb_cantidad(abb_t *arbol);

/**
 * Destruye un árbol.
 * @param arbol: el árbol fue creado.
 * Post: Se destruyó el árbol y todo su contenido.
 */
void abb_destruir(abb_t *arbol);

/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

/**
 * Itera el árbol in-order. Si visitar devuelve false, el árbol dejará
 * de iterarse.
 * @param  arbol: el arbol fue creado.
 * @param  visitar: la función se llamará para cada elemento del árbol y debe
 * ser != NULL.
 * @param  extra: se utilizará en la función visitar.
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* ******************************************************************
 *                  PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

/**
 * Crea un iterador in-order de un árbol.
 * @param  arbol: el árbol fue creado.
 * @return el iterador fue creado.
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/**
 * Avanza de manera in-order el iterador de un árbol.
 * @param  iter: el iterador fue creado.
 * @return True si se pudo avanzar hacia el siguiente nodo o
 * False en caso contrario.
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/**
 * Devuelve la clave donde se encuentra posicionado el iterador.
 * @param  iter: el iterador fue creado.
 * @return la clave donde se encuentra posicionado
 * el iterador.
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/**
 * Verifica si el iterador se encuentra al final de un árbol.
 * @param  iter: el iterador fue creado.
 * @return True si se encuentra al final de un árbol, False
 * en caso contrario.
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/**
 * Destruye el iterador de un árbol.
 * @param iter: el iterador fue creado.
 * Post: Se destruyó el iterador.
 */
void abb_iter_in_destruir(abb_iter_t* iter);

#endif // ABB_H