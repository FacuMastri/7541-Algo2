#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

// Imprime el contenido de una lista con el iterador interno.
bool imprimir_un_item(void* elemento, void* extra) {

    char* cadena = elemento;
    if (strcmp(cadena, "python") == 0) {
    	return false;
    }
    strcat((char*) extra, cadena);
    strcat((char*) extra, " ");

    return true;
}

// Suma el contenido de una lista con el iterador interno.
bool sumar(void* dato, void* extra) {
    int* int_dato = dato;
    *(int *) extra += *int_dato;
    return true;
}

// Inserta elementos a la lista desde un array de tamaño tam.
bool insertar_elem_desde_array(int array[], size_t tam, lista_t* lista) {

	bool ok_insertar_ultimo = true;
	for (int i = 0; i < tam; i ++) {
		array[i] = i;
		ok_insertar_ultimo &= lista_insertar_ultimo(lista, &array[i]);
	}

	return ok_insertar_ultimo;
}

// Pruebas para las condiciones de borde de la lista enlazada.
void pruebas_condiciones_borde_lista(lista_t* lista) {

	print_test("Prueba condición borde: Ver primero en lista vacía devuelve NULL", lista_ver_primero(lista) == NULL);
 	print_test("Prueba condición borde: Ver último en lista vacía devuelve NULL", lista_ver_ultimo(lista) == NULL);
 	print_test("Prueba condición borde: Borrar primero en lista vacía devuelve NULL", lista_borrar_primero(lista) == NULL);
 	print_test("Prueba condición borde: El largo de una lista vacía debería ser 0", lista_largo(lista) == 0);
 	print_test("Prueba condicion borde: La lista se encuentra vacía", lista_esta_vacia(lista));
}

/* ******************************************************************
 *                PRUEBAS DE LAS PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Pruebas para la creación de una lista.
void pruebas_lista_crear() {
	printf("-------------INICIO DE PRUEBAS CREAR LISTA-------------\n");

 	// Creo la lista.
 	lista_t* lista = lista_crear();

 	// Pruebo comportamiento sobre una lista recien creada.
 	print_test("Prueba p1: La lista fue creada", lista != NULL);
 	pruebas_condiciones_borde_lista(lista);

 	// Destruyo la lista.
 	lista_destruir(lista, NULL);
 	print_test("Prueba p1: La lista fue destruida", true);
 }

// Pruebas para insertar primero en una lista.
void pruebas_lista_insertar_primero() {
	printf("-------------INICIO DE PRUEBAS INSERTAR PRIMERO-------------\n");

	// Creo la lista.
    lista_t* lista = lista_crear();

    // Declaro las variables a utilizar.
    int elemento1 = 3434;
    int elemento2 = 20000;

    // Pruebo comportamiento sobre una lista recien creada.
    print_test("Prueba p2: La lista fue creada", lista != NULL);
    pruebas_condiciones_borde_lista(lista);

    // Pruebo insertar primero.
    print_test("Prueba p2: Insertar elemento1 al principio", lista_insertar_primero(lista, &elemento1));
    print_test("Prueba p2: Ver primero debería devolver el elemento1", lista_ver_primero(lista) == &elemento1);
    print_test("Prueba p2: Ver último debería devolver el elemento1", lista_ver_ultimo(lista) == &elemento1);
    print_test("Prueba p2: Insertar elemento2 al principio", lista_insertar_primero(lista, &elemento2));
    print_test("Prueba p2: Ver primero debería devolver el elemento2", lista_ver_primero(lista) == &elemento2);
    print_test("Prueba p2: Ver último debería devolver el elemento1", lista_ver_ultimo(lista) == &elemento1);
    print_test("Prueba p2: El largo de la lista debería ser 2", lista_largo(lista) == 2);

    // Destruyo la lista.
    lista_destruir(lista, NULL);
    print_test("Prueba p2: La lista fue destruida", true);
}

// Pruebas para inserar último en una lista.
void pruebas_lista_insertar_ultimo() {
	printf("-------------INICIO DE PRUEBAS INSERTAR ÚLTIMO-------------\n");

	// Creo la lista.
	lista_t* lista = lista_crear();

	// Declaro las variables a utilizar.
	char* elemento1 = "Elemento 1";
	char* elemento2 = "Elemento 2";

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p3: La lista fue creada", lista != NULL);
	pruebas_condiciones_borde_lista(lista);

	// Pruebo insertar último.
    print_test("Prueba p3: Insertar elemento1 al final", lista_insertar_ultimo(lista, elemento1));
    print_test("Prueba p3: Ver último debería devolver el elemento1", lista_ver_ultimo(lista) == elemento1);
    print_test("Prueba p3: Ver primero debería devolver el elemento1", lista_ver_primero(lista) == elemento1);
    print_test("Prueba p3: Insertar elemento2 al final", lista_insertar_ultimo(lista, elemento2));
    print_test("Prueba p3: Ver último debería devolver el elemento2", lista_ver_ultimo(lista) == elemento2);
    print_test("Prueba p3: Ver primero debería devolver el elemento1", lista_ver_primero(lista) == elemento1);
    print_test("Prueba p3: El largo de la lista debería ser 2", lista_largo(lista) == 2);

    // Destruyo la lista.
    lista_destruir(lista, NULL);
    print_test("Prueba p3: La lista fue destruida", true);
}

// Pruebas para borrar primero en una lista.
void pruebas_lista_borrar_primero() {
	printf("-------------INICIO DE PRUEBAS BORRAR PRIMERO-------------\n");

	// Creo la lista.
	lista_t* lista = lista_crear();

	// Declaro las variables a utilizar.
	size_t elemento1 = 42424;
	size_t elemento2 = 20000;

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p4: La lista fue creada", lista != NULL);
	pruebas_condiciones_borde_lista(lista);

	// Pruebo borrar primero.
    print_test("Prueba p4: Insertar elemento1 al final", lista_insertar_ultimo(lista, &elemento1));
    print_test("Prueba p4: Insertar elemento2 al final", lista_insertar_ultimo(lista, &elemento2));
    print_test("Prueba p4: El largo de la lista debería ser 2", lista_largo(lista) == 2);
    print_test("Prueba p4: Borrar primero debería devolver el elemento1", lista_borrar_primero(lista) == &elemento1);
    print_test("Prueba p4: El largo de la lista debería ser 1", lista_largo(lista) == 1);
    print_test("Prueba p4: Borrar primero debería devolver el elemento2", lista_borrar_primero(lista) == &elemento2);
    
    // Pruebo comportamiento sobre una lista que fue vaciada.
    pruebas_condiciones_borde_lista(lista);

    // Destruyo la lista.
    lista_destruir(lista, NULL);
    print_test("Prueba p4: La lista fue destruida", true);

}

// Pruebas de la lista al trabajar con un volumen grande de elementos.
void pruebas_lista_volumen() {
	printf("-------------INICIO DE PRUEBAS DE VOLUMEN-------------\n");

	// Creo la lista.
	lista_t* lista_volumen = lista_crear();

	// Declaro las variables a utilizar.
	size_t tam = 10000;
	int array[tam];

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p5: La lista fue creada", lista_volumen != NULL);
	pruebas_condiciones_borde_lista(lista_volumen);

	// Pruebo insertando un volumen grande de elementos.
	bool ok_insertar = true, ok_ultimo = true;
	for (int i = 0; i < tam; i ++) {
		array[i] = i;
		ok_insertar &= lista_insertar_ultimo(lista_volumen, &array[i]);
		ok_ultimo &= lista_ver_ultimo(lista_volumen) == &array[i];
	}
	print_test("Prueba p5: Se insertaron todos los elementos correctamente", ok_ultimo && ok_insertar);
	print_test("Prueba p5: Ver último debería devolver el elemento 10000", lista_ver_ultimo(lista_volumen) == &array[tam - 1]);
	print_test("Prueba p5: El largo de la lista es 10000", lista_largo(lista_volumen) == tam);

	// Pruebo borrando todos los elementos.
	bool ok_borrar = true, ok_primero = true;
	for (size_t i = 0; i < tam; i ++) {
		ok_borrar &= lista_borrar_primero(lista_volumen) == &array[i];
		if (!lista_esta_vacia(lista_volumen)) {
			ok_primero &= lista_ver_primero(lista_volumen) == &array[i + 1];
		}
	}
	print_test("Prueba p5: Todos los elementos fueron eliminados correctamente", ok_borrar && ok_primero);
	pruebas_condiciones_borde_lista(lista_volumen);

	// Destruyo la lista.
	lista_destruir(lista_volumen, NULL);
	print_test("Prueba p5: La lista fue destruida", true);
}

// Pruebas de una lista con función de destrucción de elementos.
void pruebas_lista_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS DESTRUCCION DE LISTA CON DESTRUCCION DE ELEMENTOS-------------\n");

	// Creo la lista.
	lista_t* lista_destrucccion = lista_crear();

	// Declaro las variables a utilizar.
	int* ejemplo1 = malloc(sizeof(int));
	char* ejemplo2 = malloc(sizeof(char));
	void* ejemplo3 = malloc(sizeof(void*));

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p6: La lista fue creada", lista_destrucccion != NULL);
	pruebas_condiciones_borde_lista(lista_destrucccion);

	// Pruebo insertar elementos.
	print_test("Prueba p6: Insertar referencia al valor1", lista_insertar_ultimo(lista_destrucccion, ejemplo1));
	print_test("Prueba p6: Ver último debería devolver el valor1", lista_ver_ultimo(lista_destrucccion) == ejemplo1);
	print_test("Prueba p6: Insertar referencia al valor2", lista_insertar_ultimo(lista_destrucccion, ejemplo2));
	print_test("Prueba p6: Ver último debería devolver el valor2", lista_ver_ultimo(lista_destrucccion) == ejemplo2);
	print_test("Prueba p6: Insertar referencia al valor3", lista_insertar_ultimo(lista_destrucccion, ejemplo3));
	print_test("Prueba p6: Ver último debería devolver el valor3", lista_ver_ultimo(lista_destrucccion) == ejemplo3);
	print_test("Prueba p6: El largo de la lista es 3", lista_largo(lista_destrucccion) == 3);

	// Destruyo la lista.
	lista_destruir(lista_destrucccion, free);
	print_test("Prueba p6: La lista fue destruida", true);
}

// Pruebas de una lista que es destruida sin modificar los elementos almacenados.
void pruebas_lista_sin_destruccion() {
	printf("-------------INICIO DE PRUEBAS DESTRUCCION DE LISTA SIN DESTRUCCION DE ELEMENTOS-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p7: La lista fue creada", lista != NULL);
	pruebas_condiciones_borde_lista(lista);

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p7: Los elementos fueron insertados correctamente", ok_insertar);
	print_test("Prueba p7: La lista no se encuentra vacía", !lista_esta_vacia(lista));

	// Pruebo destruir la lista sin modificar los datos almacenados.
	lista_destruir(lista, NULL);
	bool datos_no_modificados = true;
	for (size_t i = 0; i < tam; i++) {
		datos_no_modificados &= array[i] == i;
	}
	print_test("Prueba p7: La lista fue destruida, los datos no fueron modificados", datos_no_modificados);
}

void pruebas_lista_vacia_destruccion() {
	printf("-------------INICIO DE PRUEBAS DESTRUCCION DE LISTA VACIA CON DESTRUCCION DE ELEMENTOS-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();

	// Pruebo comportamiento sobre una lista recien creada.
	print_test("Prueba p8: La cola fue creada", lista != NULL);
	pruebas_condiciones_borde_lista(lista);

	// Pruebo destruir la lista vacia con función de destrucción de datos.
	lista_destruir(lista, free);
	print_test("Prueba p8: La lista fue destruida", true);
}

/* ******************************************************************
 *             		PRUEBAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Pruebas para el iterador interno con corte.
void pruebas_iterar_interno_con_corte() {

	// Declaro las variables a utilizar.
    char* array[7] = {"Hola", "Mundo", "python", "!", "Esto", "es", "Python"};
    char cadena[12] = "";
    char cadena_esperada[12] = "Hola Mundo ";
    lista_t* lista = lista_crear();

    // Pruebo comportamiento sobre una lista recien creada.
    print_test("Prueba p9: La lista fue creada", lista != NULL);
    pruebas_condiciones_borde_lista(lista);

   	// Inserto elementos en la lista.
    bool ok_insertar = true, ok_ultimo = true;
    for (size_t i = 0; i < 7; i++) {
        ok_insertar &= lista_insertar_ultimo(lista, array[i]);
        ok_ultimo &= lista_ver_ultimo(lista) == array[i];
    }
    print_test("Prueba p9: Se insertaron todos los elementos correctamente", ok_insertar && ok_ultimo);
    print_test("Prueba p9: Ver último debería devolver el elemento 7", lista_ver_ultimo(lista) == array[6]);
    print_test("Prueba p9: El largo de la lista es 7", lista_largo(lista) == 7);

    // Pruebo iterar con el iterador interno.
    lista_iterar(lista, imprimir_un_item, &cadena);
    print_test("Prueba p9: Se concatenó correctamente", strcmp(cadena, cadena_esperada) == 0);

    // Destruyo la lista.
    lista_destruir(lista, NULL);
    print_test("Prueba p9: La lista fue destruida", true);
}

// Pruebas para el iterador interno sin corte.
void pruebas_iterar_interno_sin_corte() {
	printf("-------------INICIO DE PRUEBAS ITERADOR INTERNO: SUMAR ELEMENTOS SIN CORTE-------------\n");

	// Creo la lista.
	lista_t* lista_numeros = lista_crear();

	// Declaro las variables a utilizar.
    int suma = 0;
    int vector_num[9] = {5, 10, 15, 20, 25, 30, 35, 40, 45};

    // Pruebo comportamiento sobre una lista recien creada.
    print_test("Prueba p10: La lista fue creada", lista_numeros != NULL);
    pruebas_condiciones_borde_lista(lista_numeros);

    // Inserto elementos.
    bool ok_ultimo = true, ok_insertar = true;
    for (size_t i = 0; i < 9; i++) {
        ok_insertar &= lista_insertar_ultimo(lista_numeros, &vector_num[i]);
        ok_ultimo &= (lista_ver_ultimo(lista_numeros) == &vector_num[i]);
    }
    print_test("Prueba p10: Se insertaron todos los elementos corectamente", ok_ultimo && ok_insertar);
    print_test("Prueba p10: Ver último debería devolver el elemento 9", lista_ver_ultimo(lista_numeros) == &vector_num[8]);
    print_test("Prueba p10: El largo de la lista es 9", lista_largo(lista_numeros) == 9);

    // Pruebo iterar con el iterador interno.
    lista_iterar(lista_numeros, sumar, &suma);
    print_test("Prueba p10: La suma de los elementos debería ser 225", suma == 225);

    // Destruyo la lista.
    lista_destruir(lista_numeros, NULL);
    print_test("Prueba p10: La lista fue destruida", true);
}

/* ******************************************************************
 *             		PRUEBAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Pruebas para la creación de un iterador.
void pruebas_iterador_crear() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: CREAR ITERADOR-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p11: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);

	// Pruebo comportamiento de un iterador recien creado.
	print_test("Prueba p11: El iterador fue creado", iterador != NULL);
	print_test("Prueba p11: El iterador se encuentra al principio de la lista", lista_iter_ver_actual(iterador) == &array[0]);
	print_test("Prueba p11: El iterador no se encuentra al final de la lista", !lista_iter_al_final(iterador));

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p11: El iterador fue destruido", true);
}

// Pruebas para avanzar el iterador.
void pruebas_iterador_avanzar() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: AVANZAR ITERADOR-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p12: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p12: El iterador fue creado", iterador != NULL);

	// Pruebo avanzar el iterador hasta el final de la lista.
	bool ok_actual = true;
	size_t i = 0;
	while (!lista_iter_al_final(iterador)) {
		ok_actual &= lista_iter_ver_actual(iterador) == &array[i];
		i ++;
		lista_iter_avanzar(iterador);
	}

	// Pruebo comportamiento de un iterador que avanzo hasta el final.
	print_test("Prueba p12: El iterador avanzó correctamente", ok_actual && i == tam);
	print_test("Prueba p12: El iterador se encuentra al final de la lista", lista_iter_al_final(iterador));

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p12: El iterador fue destruido", true);
}

// Pruebas para borrar el primer elemento de una lista con un iterador.
void pruebas_iterador_borrar_primero() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: BORRAR PRIMERO-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p13: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p13: El iterador fue creado", iterador != NULL);

	// Pruebo borrar con el iterador posicionado en el primer elemento de la lista.
	print_test("Prueba p13: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p13: Borrar debería eliminar el primer elemento de la lista", lista_iter_borrar(iterador) == &array[0]);
	print_test("Prueba p13: El iterador se encuentra en el segundo elemento de la lista", lista_iter_ver_actual(iterador) == &array[1]);
	print_test("Prueba p13: El primer elemento de la lista es aquel donde se encuentra el iterador", lista_ver_primero(lista) == lista_iter_ver_actual(iterador));
	print_test("Prueba p13: El largo de la lista es 9", lista_largo(lista) == tam - 1);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p13: El iterador fue destruido", true);
}

// Pruebas para borrar el último elemento de una lista con un iterador.
void pruebas_iterador_borrar_ultimo() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: BORRAR ULTIMO-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p14: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p14: El iterador fue creado", iterador != NULL);

	// Pruebo avanzar el iterador hasta el último elemento de la lista.
    while (!lista_iter_al_final(iterador) && lista_iter_ver_actual(iterador) != &array[tam - 1]) {
        lista_iter_avanzar(iterador);
    }

    // Pruebo borrar con el iterador posicionado en el último elemento de la lista.
	print_test("Prueba p14: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p14: Borrar debería eliminar el uĺtimo elemento de la lista", lista_iter_borrar(iterador) == &array[tam - 1]);
	print_test("Prueba p14: El largo de la lista es 9", lista_largo(lista) == tam - 1);
	print_test("Prueba p14: El iterador se encuentra al final de la lista", lista_iter_al_final(iterador));
	print_test("Prueba p14: El último elemento de la lista es el anterior al que fue eliminado", lista_ver_ultimo(lista) == &array[tam - 2]);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p14: El iterador fue destruido", true);
}

// Pruebas para borrar algún elemento del medio de una lista con un iterador.
void pruebas_iterador_borrar_medio() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: BORRAR ELEMENTO DEL MEDIO-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p15: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p15: El iterador fue creado", iterador != NULL);

	// Pruebo avanzar el iterador hasta la mitad de la lista.
	size_t i = 0;
	for(; i < tam / 2; i ++) {
		lista_iter_avanzar(iterador);
	}

	// Pruebo borrar con el iterador posicionado en algún elemento del medio.
	print_test("Prueba p15: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p15: Borrar debería eliminar algún elemento del medio", lista_iter_ver_actual(iterador) == lista_iter_borrar(iterador));
	print_test("Prueba p15: El largo de la lista es 9", lista_largo(lista) == tam - 1);
	print_test("Prueba p15: El iterador se encuentra en la posición siguiente", lista_iter_ver_actual(iterador) == &array[i + 1]);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p15: El iterador fue destruido", true);
}

// Pruebas para insertar como primer elemento de una lista usando un iterador.
void pruebas_iterador_insertar_primero() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: INSERTAR ELEMENTO AL PRINCIPIO-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int ejemplo1 = 1234;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p16: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p16: El iterador fue creado", iterador != NULL);

	// Pruebo insertar con el iterador posicionado en el primer elemento de la lista.
	print_test("Prueba p16: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p16: Insertar debería agregar un elemento correctamente", lista_iter_insertar(iterador, &ejemplo1));
	print_test("Prueba p16: El iterador se encuentra en la primera posición", lista_iter_ver_actual(iterador) == &ejemplo1);
	print_test("Prueba p16: El largo de la lista es 11", lista_largo(lista) == tam + 1);
	print_test("Prueba p16: La lista tiene un nuevo primer elemento", lista_ver_primero(lista) == &ejemplo1);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p16: El iterador fue destruido", true);
}

// Pruebas para insertar como último elemento de una lista usando un iterador.
void pruebas_iterador_insertar_ultimo() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: INSERTAR ELEMENTO AL FINAL-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int ejemplo1 = 1234;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p17: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p17: El iterador fue creado", iterador != NULL);

	// Pruebo avanzar el iterador hasta el final de la lista.
	while (!lista_iter_al_final(iterador)) {
		lista_iter_avanzar(iterador);
	}

	// Pruebo insertar con el iterador posicionado al final de la lista.
	print_test("Prueba p17: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p17: El iterador se encuentra al final de la lista", lista_iter_al_final(iterador));
	print_test("Prueba p17: Insertar debería agregar un elemento correctamente", lista_iter_insertar(iterador, &ejemplo1));
	print_test("Prueba p17: El largo de la lista es 11", lista_largo(lista) == tam + 1);
	print_test("Prueba p17: La lista tiene un nuevo último elemento", lista_ver_ultimo(lista) == &ejemplo1);
	print_test("Prueba p17: El iterador se encuentra en el último elemento de la lista", lista_iter_ver_actual(iterador) == &ejemplo1);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p17: El iterador fue destruido", true);
}

// Pruebas para insertar en alguna posición del medio de una lista usando un iterador.
void pruebas_iterador_insertar_medio() {
	printf("-------------INICIO DE PRUEBAS ITERADOR EXTERNO: INSERTAR ELEMENTO EN EL MEDIO-------------\n");

	// Declaro las variables a utilizar.
	lista_t* lista = lista_crear();
	size_t tam = 10;
	int ejemplo1 = 1234;
	int array[tam];

	// Inserto elementos en la lista.
	bool ok_insertar = true;
	ok_insertar = insertar_elem_desde_array(array, tam, lista);
	print_test("Prueba p18: Los elementos fueron insertados correctamente", ok_insertar);

	// Creo el iterador.
	lista_iter_t* iterador = lista_iter_crear(lista);
	print_test("Prueba p18: El iterador fue creado", iterador != NULL);

	// Pruebo avanzar el iterador hasta la mitad de la lista.
	size_t i = 0;
	for(; i < tam / 2; i ++) {
		lista_iter_avanzar(iterador);
	}

	// Pruebo insertar con el iterador posicionado en alguna posición del medio.
	print_test("Prueba p18: El largo de la lista es 10", lista_largo(lista) == tam);
	print_test("Prueba p18: Insertar debería agregar un elemento correctamente", lista_iter_insertar(iterador, &ejemplo1));
	print_test("Prueba p18: El largo de la lista es 11", lista_largo(lista) == tam + 1);
	print_test("Prueba p18: El iterador se encuentra en la posición del elemento insertado", lista_iter_ver_actual(iterador) == &ejemplo1);

	// Destruyo el iterador y la lista.
	lista_iter_destruir(iterador);
	lista_destruir(lista, NULL);
	print_test("Prueba p18: El iterador fue destruido", true);
}

void pruebas_lista_alumno() {

	pruebas_lista_crear();
	pruebas_lista_insertar_primero();
	pruebas_lista_insertar_ultimo();
	pruebas_lista_borrar_primero();
	pruebas_lista_volumen();
	pruebas_lista_con_destruccion();
	pruebas_lista_sin_destruccion();
	pruebas_lista_vacia_destruccion();
	pruebas_iterar_interno_sin_corte();
	pruebas_iterar_interno_con_corte();
	pruebas_iterador_crear();
	pruebas_iterador_avanzar();
	pruebas_iterador_borrar_primero();
	pruebas_iterador_borrar_ultimo();
	pruebas_iterador_borrar_medio();
	pruebas_iterador_insertar_primero();
	pruebas_iterador_insertar_ultimo();
	pruebas_iterador_insertar_medio();
}