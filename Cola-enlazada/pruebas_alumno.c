#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

/* Pruebas para las condiciones de borde de la cola enlazada */
void pruebas_condiciones_borde(cola_t* cola) {

	print_test("Prueba condición borde: La cola se encuentra vacía", cola_esta_vacia(cola));
	print_test("Prueba condición borde: Ver primero en cola vacía es NULL", cola_ver_primero(cola) == NULL);
	print_test("Prueba condición borde: Desencolar en cola vacía es NULL", cola_desencolar(cola) == NULL);
}

/* Pruebas para encolar elemento NULL */
void pruebas_cola_encolar_null() {
	printf("-------------INICIO DE PRUEBAS ENCOLAR ELEMENTO NULL-------------\n");

	/* Creo una cola */
	cola_t* cola_prueba_null = cola_crear();

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p1: La cola fue creada", cola_prueba_null != NULL);
	pruebas_condiciones_borde(cola_prueba_null);

	/* Pruebo encolar el elemento NULL */
	print_test("Prueba p1: Encolar NULL", cola_encolar(cola_prueba_null, NULL));

	/* Pruebo comportamiento sobre la cola */
	print_test("Prueba p1: La cola no se encuentra vacía", !cola_esta_vacia(cola_prueba_null));
	print_test("Prueba p1: El primero es el elemento NULL", cola_ver_primero(cola_prueba_null) == NULL);
	print_test("Prueba p1: Desencolo NULL", cola_desencolar(cola_prueba_null) == NULL);

	/* Pruebo sobre una cola que fue encolada y luego desencolada */
	pruebas_condiciones_borde(cola_prueba_null);

	/* Destruyo la cola */
	cola_destruir(cola_prueba_null, NULL);
	print_test("Prueba p1: La cola fue destruida", true);
}

/* Pruebas para una cola con pocos elementos */
void pruebas_cola_algunos_elementos() {
	printf("-------------INICIO DE PRUEBAS CON COLA DE ALGUNOS ELEMENTOS-------------\n");

	/* Creo una cola */
	cola_t* cola_elementos = cola_crear();

	/* Declaro las variables a utilizar */
	int valores_prueba[] = {50, 111, 80, 9};
	size_t i = 0;

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p2: La cola fue creada", cola_elementos != NULL);
	pruebas_condiciones_borde(cola_elementos);

	/* Pruebo encolar sobre una cola recien creada */
	print_test("Prueba p2: Encolar referencia al valor1", cola_encolar(cola_elementos, &valores_prueba[i]));
	print_test("Prueba p2: El primero es la referencia al valor1", cola_ver_primero(cola_elementos) == &valores_prueba[0]);
	print_test("Prueba p2: Encolar referencia al valor2", cola_encolar(cola_elementos, &valores_prueba[++i]));
	print_test("Prueba p2: El primero es la referencia al valor1", cola_ver_primero(cola_elementos) == &valores_prueba[0]);
	print_test("Prueba p2: Encolar referencia al valor3", cola_encolar(cola_elementos, &valores_prueba[++i]));
	print_test("Prueba p2: El primero es la referencia al valor1", cola_ver_primero(cola_elementos) == &valores_prueba[0]);
	print_test("Prueba p2: Encolar referencia al valor4", cola_encolar(cola_elementos, &valores_prueba[++i]));
	print_test("Prueba p2: El primero es la referencia al valor1", cola_ver_primero(cola_elementos) == &valores_prueba[0]);

	/* Pruebo comportamiento sobre una cola con algunos elementos */
	i = 0;
	print_test("Prueba p2: La cola no se encuentra vacía", !cola_esta_vacia(cola_elementos));
	print_test("Prueba p2: Desencolo referencia al valor1", cola_desencolar(cola_elementos) == &valores_prueba[i]);
	print_test("Prueba p2: El primero es la referencia al valor2", cola_ver_primero(cola_elementos) == &valores_prueba[++i]);
	print_test("Prueba p2: Desencolo referencia al valor 2", cola_desencolar(cola_elementos) == &valores_prueba[i]);
	print_test("Prueba p2: El primero es la referencia al valor3", cola_ver_primero(cola_elementos) == &valores_prueba[++i]);
	print_test("Prueba p2: Desencolo referencia al valor3", cola_desencolar(cola_elementos) == &valores_prueba[i]);
	print_test("Prueba p2: El primero es la referencia al valor4", cola_ver_primero(cola_elementos) == &valores_prueba[++i]);
	print_test("Prueba p2: Desencolo referencia al valor4", cola_desencolar(cola_elementos) == &valores_prueba[i]);

	/* Pruebo comportamiento de una cola que fue encolada/desencolada */
	pruebas_condiciones_borde(cola_elementos);

	/* Pruebo encolar despues de desencolar, luego desencolo */
	print_test("Prueba p2: Encolo referencia al valor 4", cola_encolar(cola_elementos, &valores_prueba[i]));
	print_test("Prueba p2: El primero es la referencia al valor 4", cola_ver_primero(cola_elementos) == &valores_prueba[i]);
	print_test("Prueba p2: Desencolo referencia al valor 4", cola_desencolar(cola_elementos) == &valores_prueba[i]);

	/* Pruebo comportamiento de una cola que fue encolada/desencolada */
	pruebas_condiciones_borde(cola_elementos);

	/* Destruyo la cola */
	cola_destruir(cola_elementos, NULL);
	print_test("Prueba p2: La cola fue destruida", true);
}

/* Pruebas para una cola con strings */
void pruebas_cola_string() {
	printf("-------------INICIO DE PRUEBAS CON COLA DE STRINGS-------------\n");

	/* Creo una cola */
	cola_t* cola_strings = cola_crear();

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p3: La cola fue creada", cola_strings != NULL);
	pruebas_condiciones_borde(cola_strings);

	/* Declaro las variables a utilizar */
	char* ejemplo_nombres[] = {"Daenerys", "Jamie", "Jon", "Arya"};
	size_t cantidad_nombres = sizeof(ejemplo_nombres) / sizeof(ejemplo_nombres[0]);

	/* Pruebo encolar/desencolar la referencia al vector entero de char* */
	print_test("Prueba p3: Encolar referencia al valor5", cola_encolar(cola_strings, ejemplo_nombres));
	print_test("Prueba p3: La cola no se encuentra vacía", !cola_esta_vacia(cola_strings));
	print_test("Prueba p3: El primero es la referencia al valor5", cola_ver_primero(cola_strings) == ejemplo_nombres);
	print_test("Prueba p3: Desencolar referencia al valor5", cola_desencolar(cola_strings) == ejemplo_nombres);
	print_test("Prueba p3: La cola se encuentra vacía", cola_esta_vacia(cola_strings));

	/* Pruebo encolar cada nombre por separado en la cola */
	bool ok_encolar = true, ok_primero = true;
	for (size_t i = 0; i < cantidad_nombres; i ++) {
		// Si algún elemento no se pudo encolar correctamente, ok_encolar será false.
		// ok_primero tiene comportamiento similar.
		ok_encolar &= cola_encolar(cola_strings, &ejemplo_nombres[i]);
		ok_primero &= (cola_ver_primero(cola_strings) == &ejemplo_nombres[0]);
	}

	/* Pruebo comportamiento luego de encolar */
	print_test("Prueba p3: Se encolaron todos los elementos correctamente", ok_encolar && ok_primero);
	print_test("Prueba p3: El primero es la referencia al primer nombre", cola_ver_primero(cola_strings) == &ejemplo_nombres[0]);
	print_test("Prueba p3: La cola no se encuentra vacía", !cola_esta_vacia(cola_strings));

	/* Pruebo desencolar */
	bool ok_desencolar = true;
	ok_primero = true;
	char** nombre = &ejemplo_nombres[0];
	while (!cola_esta_vacia(cola_strings)) {
		ok_desencolar &= (cola_desencolar(cola_strings) == nombre);
		nombre ++;
		// Verifico que el nuevo primer elemento sea el próximo a desencolar.
		if (!cola_esta_vacia(cola_strings)) {
			ok_primero &= (cola_ver_primero(cola_strings) == nombre);
		}
	}

	/* Pruebo comportamiento luego de desencolar */
	print_test("Prueba p3: Se logró desencolar todos los elementos correctamente", ok_desencolar && ok_primero);
	pruebas_condiciones_borde(cola_strings);

	/* Destruyo la cola */
	cola_destruir(cola_strings, NULL);
	print_test("Prueba p3: La cola fue destruida", true);
}

/* Pruebas de la cola al trabajar con un volumen grande de elementos */
void pruebas_cola_volumen() {
	printf("-------------INICIO DE PRUEBAS DE VOLUMEN-------------\n");

	/* Creo una cola */
	cola_t* cola_volumen = cola_crear();

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p4: La cola fue creada", cola_volumen != NULL);
	pruebas_condiciones_borde(cola_volumen);

	/* Pruebo encolar un volumen grande de elementos */
	size_t tam = 10000;
	size_t i = 0;
	void* primer_elem = &i;
	bool ok_encolar = true, ok_primero = true;
	for ( ; i < tam; i ++) {
		ok_encolar &= cola_encolar(cola_volumen, &i);
		ok_primero &= (cola_ver_primero(cola_volumen) == primer_elem);
	}

	/* Pruebo comportamiento luego de encolar */
	print_test("Prueba p4: Se logró encolar todos los elementos correctamente", ok_encolar && ok_primero);
	print_test("Prueba p4: La cola no se encuentra vacía", !cola_esta_vacia(cola_volumen));

	/* Desencolo todos los elementos */
	bool ok_desencolar = true;
	ok_primero = true;
	while (!cola_esta_vacia(cola_volumen)) {
		ok_desencolar &= (cola_desencolar(cola_volumen) == &i);
		i ++;
		if (!cola_esta_vacia(cola_volumen)) {
			ok_primero &= (cola_ver_primero(cola_volumen) == &i);
		}
	}

	/* Pruebo comportamiento luego de desencolar */
	print_test("Prueba p4: Se logró desencolar todos los elementos correctamente", ok_desencolar && ok_primero);
	pruebas_condiciones_borde(cola_volumen);

	/* Destruyo la cola */
	cola_destruir(cola_volumen, NULL);
	print_test("Prueba p4: La cola fue destruida", true);
}

/* Pruebas de una cola de punteros pedidos con malloc() y destruidos con free() */
void pruebas_cola_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS DE COLA CON DESTRUCCION-------------\n");

	/* Declaro variables a utilizar */
	cola_t* cola_destruccion = cola_crear();
	int* ejemplo_1 = malloc(sizeof(int));
	char* ejemplo_2 = malloc(sizeof(char));
	void* ejemplo_3 = malloc(sizeof(float));

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p5: La cola fue creada", cola_destruccion != NULL);
	pruebas_condiciones_borde(cola_destruccion);

	/* Pruebo encolar los elementos */
	print_test("Prueba p5: Encolar referencia al valor1", cola_encolar(cola_destruccion, ejemplo_1));
	print_test("Prueba p5: El primero es la referencia al valor1", cola_ver_primero(cola_destruccion) == ejemplo_1);
	print_test("Prueba p5: Encolar referencia al valor2", cola_encolar(cola_destruccion, ejemplo_2));
	print_test("Prueba p5: El primero es la referencia al valor1", cola_ver_primero(cola_destruccion) == ejemplo_1);
	print_test("Prueba p5: Encolar referencia al valor3", cola_encolar(cola_destruccion, ejemplo_3));
	print_test("Prueba p5: El primero es la referencia al valor1", cola_ver_primero(cola_destruccion) == ejemplo_1);

	/* Destruyo la cola */
	cola_destruir(cola_destruccion, free);
	print_test("Prueba p5: La cola fue destruida", true);
}

/* Pruebas de una cola que es destruida sin modificar los elementos almacenados */
void pruebas_cola_sin_destruccion() {
	printf("-------------INICIO DE PRUEBAS DE COLA SIN DESTRUCCION-------------\n");

	/* Declaro las variables a utilizar. */
	cola_t* cola_sin_destruccion = cola_crear();
	size_t tam = 10;
    int array[tam];
    for (int i = 0; i < tam; i++) {
        array[i] = i;
    }

    /* Pruebo comportamiento sobre una cola recien creada */
    print_test("Prueba p6: La cola fue creada", cola_sin_destruccion != NULL);
    pruebas_condiciones_borde(cola_sin_destruccion);

    /* Pruebo encolar los elementos */
    bool ok_encolar = true;
    for (int i = 0; i < tam; i++) {
        ok_encolar &= cola_encolar(cola_sin_destruccion, &array[i]);
    }

    print_test("Prueba p6: Todos los elementos fueron encolados", ok_encolar);
    print_test("Prueba p6: La cola no se encuentra vacía", !cola_esta_vacia(cola_sin_destruccion));

    /* Pruebo destruir la cola sin modificar los datos almacenados */
    cola_destruir(cola_sin_destruccion, NULL);
    bool datos_no_modificados = true;
    for (int i = 0; i < tam; i++) {
        datos_no_modificados &= array[i] == i;
    }
    print_test("Prueba p6: La cola fue destruida, los datos no fueron modificados", datos_no_modificados);
}

/* Pruebas de una cola vacía que es destruida con función de destrucción de datos */
void pruebas_cola_vacia_destruccion() {
	printf("-------------INICIO DE PRUEBAS DE DESTRUCCIÓN COLA VACÍA-------------\n");

	/* Declaro las variables a utilizar. */
	cola_t* cola = cola_crear();

	/* Pruebo comportamiento sobre una cola recien creada */
	print_test("Prueba p7: La cola fue creada", cola != NULL);
	pruebas_condiciones_borde(cola);

	/* Pruebo destruir cola vacia con función de destrucción de datos */
	cola_destruir(cola, free);
	print_test("Prueba p7: La cola fue destruida", true);
}

void pruebas_cola_alumno() {

	pruebas_cola_encolar_null();
	pruebas_cola_algunos_elementos();
	pruebas_cola_string();
	pruebas_cola_volumen();
	pruebas_cola_con_destruccion();
	pruebas_cola_sin_destruccion();
	pruebas_cola_vacia_destruccion();
}
