#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

// Funcion auxiliar para comparar enteros.
int comparar_enteros(const void* a, const void* b) {

	if (*(const int*) a == *(const int*) b) {
		return 0;
	}
	if (*(const int*) a > *(const int*) b) {
		return 1;
	}

	return -1;
}

// Función auxiliar para mezclar un arreglo de enteros.
// Función obtenida de: https://www.geeksforgeeks.org/shuffle-a-given-array/
void mezclar_enteros(int datos[], size_t largo) {

    // Uso un seed diferente para que cada vez que se ejecute
    // no se obtenga el mismo resultado.
    srand((unsigned int) time(NULL));

    for (int i = (int) largo - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);
        int aux = datos[i];
        datos[i] = datos[j];
        datos[j] = aux;
    }
}

/* ******************************************************************
 *                       PRUEBAS UNITARIAS
 * *****************************************************************/

// Pruebas para un heap vacio.
void pruebas_heap_vacio() {
	printf("-------------INICIO DE PRUEBAS: CREAR HEAP-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);

	// Pruebo comportamiento de un heap vacio.
	print_test("Prueba p1: El heap fue creado", heap);
	print_test("Prueba p1: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p1: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p1: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p1: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p1: El heap fue destruido", true);
}

// Pruebas para encolar en un heap.
void pruebas_heap_encolar() {
	printf("-------------INICIO DE PRUEBAS: ENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 25, elemento3 = 33, elemento4 = 100;

	// Pruebo encolar.
	print_test("Prueba p2: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p2: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p2: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p2: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p2: El heap fue destruido", true);
}

// Pruebas para desencolar en un heap.
void pruebas_heap_desencolar() {
	printf("-------------INICIO DE PRUEBAS: DESENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 25, elemento3 = 33, elemento4 = 100;

	// Encolo y desencolo.
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p3: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p3: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p3: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	print_test("Prueba p3: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba p3: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba p3: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento4);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento3);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento3);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento2);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento2);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p3: El heap fue destruido", true);
}

// Pruebas de volumen para un heap, tanto para encolar como desencolar.
void pruebas_heap_volumen() {
	printf("-------------INICIO DE PRUEBAS: VOLUMEN-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	size_t tam = 10000;
	int datos[tam];

	for (int i = 0; i < tam; i++) {
		datos[i] = i;
	}
	int dato_max = datos[tam - 1];
	// Shuffleo el array así no encolo en algún orden determinado.
	mezclar_enteros(datos, tam);

	// Pruebo encolar.
	bool ok_encolar = true;
	for (size_t i = 0; i < tam; i++) {
		ok_encolar = heap_encolar(heap, &datos[i]);
		if (!ok_encolar) {
			break;
		}
	}

	print_test("Prueba p4: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p4: Todos los elementos fueron encolados", ok_encolar && heap_cantidad(heap) == tam);
	print_test("Prueba p4: Ver max devuelve el elemento correcto", *(int*) heap_ver_max(heap) == dato_max);

	// Pruebo desencolar.
	bool ok_desencolar = true;
	while (!heap_esta_vacio(heap)) {
		ok_desencolar = *(int*) heap_desencolar(heap) == dato_max;
		if (!ok_desencolar) {
			break;
		}
		dato_max--;
	}

	print_test("Prueba p4: Todos los elementos fueron desencolados", ok_desencolar && heap_cantidad(heap) == 0);
	print_test("Prueba p4: El heap se encuentra vacio", heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p4: El heap fue destruido", true);
}

// Pruebas para un heap vacio con funcion de destruccion de datos.
void pruebas_heap_vacio_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP VACIO CON DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);

	// Pruebo comportamiento de un heap vacio.
	print_test("Prueba p5: El heap fue creado", heap);
	print_test("Prueba p5: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p5: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p5: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p5: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	// Destruyo el heap.
	heap_destruir(heap, free);
	print_test("Prueba p5: El heap fue destruido", true);
}

// Pruebas para un heap no vacio con funcion de destruccion de datos.
void pruebas_heap_no_vacio_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP NO VACIO CON DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int* elemento1 = malloc(sizeof(int));
	int* elemento2 = malloc(sizeof(int));
	int* elemento3 = malloc(sizeof(int));
	*elemento1 = 5456, *elemento2 = 4949494, *elemento3 = 9999;

	// Pruebo encolar elementos.
	print_test("Prueba p6: El heap fue creado", heap);
	print_test("Prueba p6: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p6: Encolo elemento 1", heap_encolar(heap, elemento1));
	print_test("Prueba p6: Encolo elemento 2", heap_encolar(heap, elemento2));
	print_test("Prueba p6: Encolo elemento 3", heap_encolar(heap, elemento3));
	print_test("Prueba p6: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p6: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, free);
	print_test("Prueba p6: El heap fue destruido y los datos liberados", true);
}

// Pruebas para un heap no vacio sin funcion de destruccion de datos.
void pruebas_heap_no_vacio_sin_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP NO VACIO SIN DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	size_t tam = 10;
	int datos[tam];
	for (int i = 0; i < tam; i++) {
		datos[i] = i;
	}

	// Pruebo encolar elementos.
	bool ok_encolar = true;
	for (size_t i = 0; i < tam; i++) {
		ok_encolar = heap_encolar(heap, &datos[i]);
		if (!ok_encolar) {
			break;
		}
	}

	print_test("Prueba p7: Todos los elementos fueron encolados", ok_encolar && heap_cantidad(heap) == tam);

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	bool datos_no_modificados = true;
	for (size_t i = 0; i < tam; i++) {
		datos_no_modificados = datos[i] == i;
		if (!datos_no_modificados) {
			break;
		}
	}
	print_test("Prueba p7: El heap fue destruido y los datos no fueron modificados", datos_no_modificados);
}

// Pruebas para heap sort.
void pruebas_heap_sort() {
	printf("-------------INICIO DE PRUEBAS: HEAP SORT-------------\n");

	// Declaro las variables a utilizar.
	int tam = 10000;
	int datos_aux[tam];
	void* datos[tam];
	int i;

	for (i = 0; i < tam; i++) {
		datos_aux[i] = i;
		datos[i] = &datos_aux[i];
	}
	// Shuffleo el array de enteros.
	mezclar_enteros(datos_aux, tam);

	// Aplico heap sort.
	heap_sort(datos, tam, comparar_enteros);

	// Verifico si ordeno de manera correcta.
	bool ok_orden = true;
	for (int j = 0; i < tam; i++) {
		ok_orden = *(int*) datos[i] == j;
		if (!ok_orden) {
			break;
		}
	}

	print_test("Prueba p8: Heap sort ordenó correctamente", ok_orden);
}

// Pruebas para crear un heap basado en un array.
void pruebas_heap_crear_arr() {
	printf("-------------INICIO DE PRUEBAS: CREAR HEAP DESDE ARRAY-------------\n");

	// Declaro las variables a utilizar.
	int tam = 10000;
	int datos_aux[tam];
	void* datos[tam];

	for (int i = 0; i < tam; i++) {
		datos_aux[i] = i;
		datos[i] = &datos_aux[i];
	}
	int dato_max = datos_aux[tam - 1];
	// Shuffleo el array de enteros.
	mezclar_enteros(datos_aux, tam);

	// Creo heap desde un array.
	heap_t* heap = heap_crear_arr(datos, tam, comparar_enteros);

	// Pruebo si se creo el heap como deberia.
	print_test("Prueba p9: El heap fue creado ", heap);
	print_test("Prueba p9: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p9: La cantidad de elementos es la correcta", heap_cantidad(heap) == tam);
	print_test("Prueba p9: Ver maximo devuelve el elemento correcto", *(int*) heap_ver_max(heap) == tam - 1);

	// Pruebo desencolar.
	bool ok_desencolar = true;
	while (!heap_esta_vacio(heap)) {
		ok_desencolar = *(int*) heap_desencolar(heap) == dato_max;
		if (!ok_desencolar) {
			break;
		}
		dato_max--;
	}

	print_test("Prueba p9: Todos los elementos fueron desencolados", ok_desencolar && heap_cantidad(heap) == 0);
	print_test("Prueba p9: El heap se encuentra vacio", heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p9: El heap fue destruido", true);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/
 
 void pruebas_heap_alumno() {

 	pruebas_heap_vacio();
 	pruebas_heap_encolar();
 	pruebas_heap_desencolar();
 	pruebas_heap_volumen();
 	pruebas_heap_vacio_con_destruccion();
 	pruebas_heap_no_vacio_con_destruccion();
 	pruebas_heap_no_vacio_sin_destruccion();
 	pruebas_heap_sort();
 	pruebas_heap_crear_arr();
}