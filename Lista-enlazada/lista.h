#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
struct lista;
struct lista_iter;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA ENLAZADA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve true o false según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento en la primera posición de la lista, devolviendo
// true o false según si se pudo realizar o no.
// Pre: la lista fue creada.
// Post: se insertó un nuevo elemento al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento en la última posición de la lista, devolviendo
// true o false según si se pudo realizar o no.
// Pre: la lista fue creada.
// Post: se insertó un nuevo elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista.
// Pre: la lista fue creada.
// Post: se eliminó el primer elemento de la lista.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el dato del primer elemento de la lista.
// Pre: la lista fue creada.
// Post: devuelve el dato del primer elemento de la lista sin eliminarlo.
void *lista_ver_primero(const lista_t *lista);

// Devuelve el dato del último elemento de la lista.
// Pre: la lista fue creada.
// Post: devuelve el dato del último elemento de la lista sin eliminarlo.
void *lista_ver_ultimo(const lista_t* lista);


// Devuelve la cantidad de elementos de la lista.
// Pre: la lista fue creada.
// Post: devuelve el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. En el caso de que destruir_dato != NULL, se la llamara
// para cada uno de los datos almacenados en la lista.
// Pre: la lista fue creada; destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en el caso de que no se la utilice.
// Post: se eliminó la lista y/o se eliminaron todos los datos contenidos en ella.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera la lista. Si visitar devuelve false, la lista dejará de iterarse.
// Pre: la lista fue creada. La función visitar se llamará para cada elemento
// de la lista y debe ser != NULL. El parametro extra se la utilizará en la función
// visitar.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un nuevo iterador de una lista.
// Pre: la lista fue creada.
// Post: devuelve el iterador que se encuentra posicionado en
// la primera posición de la lista, o NULL si estuviera vacía.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posición en la lista.
// Pre: el iterador fue creado.
// Post: devuelve true en el caso de que se haya podido avanzar
// al próximo lugar, o false si se encuentra al final de la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato donde se encuentra posicionado el iterador.
// Pre: el iterador fue creado.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Verifica si el iterador se encuentra al final de la lista.
// Pre: el iterador fue creado.
// Post: devuelve true en si se encuentra al final, false en caso
// contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se destruyó el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un nuevo elemento en la posición donde se encuentra el iterador.
// Pre: el iterador fue creado, el dato será el elemento a insertar.
// Post: se insertó un nuevo elemento a la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento en la posición donde se encuentra el iterador.
// Pre: el iterador fue creado.
// Post: se eliminó un elemento de la lista.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
void pruebas_lista_alumno(void);

#endif // LISTA_H





