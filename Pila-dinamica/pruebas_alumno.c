#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stddef.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

/* Pruebas para las condiciones de borde de la pila */
void pruebas_condiciones_borde(pila_t* pila) {

	print_test("Prueba condición borde: La pila se encuentra vacía", pila_esta_vacia(pila));
	print_test("Prueba condición borde: Ver tope en pila vacía es NULL", pila_ver_tope(pila) == NULL);
	print_test("Prueba condición borde: Desapilar en pila vacía es NULL", pila_desapilar(pila) == NULL);
}

/* Pruebas para una pila inicializada a NULL */
void pruebas_pila_a_null() {
	printf("-------------INICIO DE PRUEBAS CON PILA NULL-------------\n");

	/* Declaro las variables a utilizar */
	pila_t* pila_a_null = NULL;
	char* ejemplo_apilar2 = "Prueba";
	int ejemplo_apilar = 50000;

	/* Inicio de pruebas */
	print_test("Prueba p1: Puntero inicializado a NULL", pila_a_null == NULL);

	/* Pruebo el comportamiento de un puntero inicializado a NULL */
	print_test("Prueba p1: Ver tope de un puntero inicializado a NULL es NULL", pila_ver_tope(pila_a_null) == NULL);
	print_test("Prueba p1: Apilar una referencia a un entero sobre un puntero inicializado a NULL es False", !pila_apilar(pila_a_null, &ejemplo_apilar));
	print_test("Prueba p1: Apilar NULL sobre un puntero inicializado a NULL es False", !pila_apilar(pila_a_null, NULL));
	print_test("Prueba p1: Apilar un string sobre un puntero inicializado a NULL es False", !pila_apilar(pila_a_null, &ejemplo_apilar2));
	print_test("Prueba p1: Desapilar de un puntero inicializado a NULL devuelve NULL", pila_desapilar(pila_a_null) == NULL);
}

/* Pruebas para apilar elemento NULL */
void pruebas_apilar_null() {
	printf("-------------INICIO DE PRUEBAS APILAR ELEMENTO NULL-------------\n");

	/* Creo una pila */
	pila_t* pila_prueba_null = pila_crear();

	/* Pruebo comportamiento sobre una pila recien creada */
	print_test("Prueba p2: La pila fue creada", pila_prueba_null != NULL);
	pruebas_condiciones_borde(pila_prueba_null);

	/* Pruebo apilar el elemento NULL */
	print_test("Prueba p2: Apilar NULL", pila_apilar(pila_prueba_null, NULL));

	/* Pruebo comportamiento sobre la pila */
	print_test("Prueba p2: La pila no se encuentra vacía", !pila_esta_vacia(pila_prueba_null));
	print_test("Prueba p2: El tope es el elemento NULL", pila_ver_tope(pila_prueba_null) == NULL);
	print_test("Prueba p2: Desapilo NULL", pila_desapilar(pila_prueba_null) == NULL);

	/* Pruebo sobre una pila que fue apilada y luego desapilada */
	pruebas_condiciones_borde(pila_prueba_null);

	/* Destruyo la pila */
	pila_destruir(pila_prueba_null);
	print_test("Prueba p2: La pila fue destruida", true);
}

/* Pruebas para una pila con pocos elementos */
void pruebas_pila_algunos_elementos() {
	printf("-------------INICIO DE PRUEBAS CON PILA DE ALGUNOS ELEMENTOS-------------\n");

	/* Creo una pila */
	pila_t* pila_elementos = pila_crear();

	/* Declaro las variables a utilizar */
	int valores_prueba[] = {50, 111, 80, 9};
	size_t i = 0;

	/* Pruebo comportamiento sobre una pila recien creada */
	print_test("Prueba p3: La pila fue creada", pila_elementos != NULL);
	pruebas_condiciones_borde(pila_elementos);

	/* Pruebo apilar sobre una pila recien creada */
	print_test("Prueba p3: Apilar referencia al valor1", pila_apilar(pila_elementos, &valores_prueba[i]));
	print_test("Prueba p3: El tope es la referencia al valor1", pila_ver_tope(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: Apilar referencia al valor2", pila_apilar(pila_elementos, &valores_prueba[++i]));
	print_test("Prueba p3: El tope es la referencia al valor2", pila_ver_tope(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: Apilar referencia al valor3", pila_apilar(pila_elementos, &valores_prueba[++i]));
	print_test("Prueba p3: El tope es la referencia al valor3", pila_ver_tope(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: Apilar referencia al valor4", pila_apilar(pila_elementos, &valores_prueba[++i]));

	/* Pruebo comportamiento sobre una pila con algunos elementos */
	print_test("Prueba p3: La pila no se encuentra vacía", !pila_esta_vacia(pila_elementos));
	print_test("Prueba p3: El tope es la referencia al valor4", pila_ver_tope(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: Desapilo referencia al valor4", pila_desapilar(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: El tope es la referencia al valor3", pila_ver_tope(pila_elementos) == &valores_prueba[--i]);
	print_test("Prueba p3: Desapilo referencia al valor3", pila_desapilar(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: El tope es la referencia al valor2", pila_ver_tope(pila_elementos) == &valores_prueba[--i]);
	print_test("Prueba p3: Desapilo referencia al valor2", pila_desapilar(pila_elementos) == &valores_prueba[i]);
	print_test("Prueba p3: El tope es la referencia al valor1", pila_ver_tope(pila_elementos) == &valores_prueba[--i]);
	print_test("Prueba p3: Desapilo referencia al valor1", pila_desapilar(pila_elementos) == &valores_prueba[i]);

	/* Pruebo comportamiento de una pila que fue apilada/desapilada */
	pruebas_condiciones_borde(pila_elementos);

	/* Destruyo la pila */
	pila_destruir(pila_elementos);
	print_test("Prueba p3: La pila fue destruida", true);
}

/* Pruebas para una pila con strings */
void pruebas_pila_string() {
	printf("-------------INICIO DE PRUEBAS CON PILA DE STRINGS-------------\n");

	/* Creo una pila */
	pila_t* pila_strings = pila_crear();

	/* Pruebo comportamiento sobre una pila recien creada */
	print_test("Prueba p4: La pila fue creada", pila_strings != NULL);
	pruebas_condiciones_borde(pila_strings);

	/* Declaro las variables a utilizar */
	char* ejemplo_nombres[] = {"Daenerys", "Jamie", "Jon", "Arya"};
	size_t cantidad_nombres = sizeof(ejemplo_nombres) / sizeof(ejemplo_nombres[0]);

	/* Pruebo apilar/desapilar la referencia al vector entero de char* */
	print_test("Prueba p4: Apilar referencia al valor5", pila_apilar(pila_strings, ejemplo_nombres));
	print_test("Prueba p4: La pila no se encuentra vacía", !pila_esta_vacia(pila_strings));
	print_test("Prueba p4: El tope es la referencia al valor5", pila_ver_tope(pila_strings) == ejemplo_nombres);
	print_test("Prueba p4: Desapilar referencia al valor5", pila_desapilar(pila_strings) == ejemplo_nombres);
	print_test("Prueba p4: La pila se encuentra vacía", pila_esta_vacia(pila_strings));

	/* Pruebo apilar cada nombre por separado en la pila */
	bool ok_apilar = true, ok_tope = true;
	for (size_t i = 0; i < cantidad_nombres; i ++) {
		// Si algún elemento no se pudo apilar correctamente, ok_apilar sera false
		// ok_tope tiene comportamiento similar
		ok_apilar &= pila_apilar(pila_strings, &ejemplo_nombres[i]);
		ok_tope &= (pila_ver_tope(pila_strings) == &ejemplo_nombres[i]);
	}

	/* Pruebo comportamiento luego de apilar */
	print_test("Prueba p4: Se apilaron todos los elementos correctamente", ok_apilar && ok_tope);
	print_test("Prueba p4: El tope es la referencia al ultimo nombre", pila_ver_tope(pila_strings) == &ejemplo_nombres[cantidad_nombres - 1]);
	print_test("Prueba p4: La pila no se encuentra vacía", !pila_esta_vacia(pila_strings));

	/* Pruebo desapilar */
	bool ok_desapilar = true;
	char** nombre = &ejemplo_nombres[cantidad_nombres - 1];
	while (!pila_esta_vacia(pila_strings)) {
		ok_desapilar &= (pila_desapilar(pila_strings) == nombre);
		nombre --;
		// Verifico que el nuevo tope sea el próximo elemento a desapilar
		if (!pila_esta_vacia(pila_strings)) {
			ok_tope &= (pila_ver_tope(pila_strings) == nombre);
		}
	}

	/* Pruebo comportamiento luego de desapilar */
	print_test("Prueba p4: Se logró desapilar todos los elementos correctamente", ok_desapilar && ok_tope);
	pruebas_condiciones_borde(pila_strings);

	/* Destruyo la pila */
	pila_destruir(pila_strings);
	print_test("Prueba p4: La pila fue destruida", true);
}

/* Pruebas de la pila al trabajar con un volumen grande de elementos */
void pruebas_pila_volumen() {
	printf("-------------INICIO DE PRUEBAS DE VOLUMEN-------------\n");

	/* Creo una pila */
	pila_t* pila_volumen = pila_crear();

	/* Pruebo comportamiento sobre una pila recien creada */
	print_test("Prueba p5: La pila fue creada", pila_volumen != NULL);
	pruebas_condiciones_borde(pila_volumen);

	/* Defino un tamanio mucho mayor al tamanio de la pila inicial */
	size_t tam = 10000;

	/* Pruebo apilar hasta llegar al nuevo tamanio */
	size_t i = 0;
	bool ok_apilar = true, ok_tope = true;
	for ( ; i < tam; i++) {
		ok_apilar &= pila_apilar(pila_volumen, &i);
		ok_tope &= (pila_ver_tope(pila_volumen) == &i);
	}

	/* Pruebo comportamiento luego de apilar */
	print_test("Prueba p5: Se logro apilar todos los elementos correctamente", ok_apilar && ok_tope);
	print_test("Prueba p5: La pila no se encuentra vacía", !pila_esta_vacia(pila_volumen));
	print_test("Prueba p5: El tope es la referencia al valor9999", pila_ver_tope(pila_volumen) == &i);

	/* Desapilo todos los elementos */
	bool ok_desapilar = true;
	while (!pila_esta_vacia(pila_volumen)) {
		ok_desapilar &= (pila_desapilar(pila_volumen) == &i);
		i --;
		if (!pila_esta_vacia(pila_volumen)) {
			ok_tope &= (pila_ver_tope(pila_volumen) == &i);
		}
	}

	/* Pruebo comportamiento luego de desapilar */
	print_test("Prueba p5: Se logro desapilar todos los elementos correctamente", ok_desapilar && ok_tope);
	pruebas_condiciones_borde(pila_volumen);

	/* Destruyo la pila */
	pila_destruir(pila_volumen);
	print_test("Prueba p5: La pila fue destruida", true);
}

void pruebas_pila_alumno() {

	pruebas_pila_a_null();
	pruebas_apilar_null();
	pruebas_pila_algunos_elementos();
	pruebas_pila_string();
	pruebas_pila_volumen();
}