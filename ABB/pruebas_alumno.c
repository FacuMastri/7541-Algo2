#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

// Suma el contenido de un ABB con el iterador interno.
bool sumar(const char* clave, void* valor, void* extra) {

    *(int*) extra += *(int*) valor;
    return true;
}

// Función auxiliar para el iterador interno: concatena el contenido de
// un ABB.
bool concatenar_datos(const char* clave, void* elemento, void* extra) {

    char* cadena = elemento;
    if (strcmp(cadena, "Kit") == 0) {
    	return false;
    }
    strcat((char*) extra, cadena);
    strcat((char*) extra, " ");

    return true;
}

// Función auxiliar para obtener el índice de una clave dentro de
// un array de strings.
size_t buscar(const char* clave, char* claves[], size_t largo) {

    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) {
        	return i;
        }
    }
    return -1;
}

// Función auxiliar para mezclar un arreglo de strings.
// Función obtenida de: https://www.geeksforgeeks.org/shuffle-a-given-array/
void mezclar_strings(char* claves[], size_t largo) {

    // Uso un seed diferente para que cada vez que se ejecute
    // no se obtenga el mismo resultado.
    srand((unsigned int) time(NULL));

    for (int i = (int) largo - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);
        char* aux = claves[i];
        claves[i] = claves[j];
        claves[j] = aux;
    }
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

/**
 * Las pruebas fueron tomadas de las pruebas provistas por la cátedra
 * para el Hash, pero adaptadas para el ABB.
 */

// Pruebas para la creación de un ABB vacío.
void prueba_crear_abb_vacio() {
	printf("-------------INICIO DE PRUEBAS: CREAR ABB VACÍO-------------\n");

	abb_t* abb = abb_crear(strcmp, free);

	// Prueba comportamiento básico de un ABB vacío.
	print_test("Prueba p1: El ABB fue creado", abb);
    print_test("Prueba p1: La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba p1: Obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba p1: Pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba p1: Borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p1: El hash fue destruido", true);
}

// Pruebas para guardar claves en un ABB.
void prueba_abb_guardar() {
	printf("-------------INICIO DE PRUEBAS: ABB INSERTAR-------------\n");

	// Declaro variables a utilizar.
    abb_t* abb = abb_crear(strcmp, NULL);
    char* clave1 = "perro", *valor1 = "guau";
    char* clave2 = "gato", *valor2 = "miau";
    char* clave3 = "vaca", *valor3 = "mu";

    // Inserta 1 valor y luego lo borra
    print_test("Prueba p2: Insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba p2: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p2: Obtener clave1 devuelve valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba p2: La clave1 pertenece al ABB", abb_pertenece(abb, clave1));
    print_test("Prueba p2: Borrar clave1 devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba p2: La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Inserta otros 2 valores y no los borra (se destruyen con el abb)
    print_test("Prueba p2: Insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba p2: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p2: Obtener clave2 devuelve valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba p2: La clave2 pertenece al ABB", abb_pertenece(abb, clave2));
    print_test("Prueba p2: Insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba p2: La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba p2: Obtener clave3 devuelve valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba p2: La clave3 pertenece al ABB", abb_pertenece(abb, clave3));

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p2: El ABB fue destruido", true);
}

// Pruebas para guardar claves en un ABB y luego reemplazar sus valores.
void prueba_abb_reemplazar() {
	printf("-------------INICIO DE PRUEBAS: ABB REEMPLAZAR VALORES-------------\n");

	// Declaro las variables a utilizar.
   	abb_t* abb = abb_crear(strcmp, NULL);
    char* clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char* clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    // Inserta 2 valores.
    print_test("Prueba p3: Insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba p3: Obtener clave1 devuelve valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba p3: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p3: Insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba p3: Obtener clave2 devuelve valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba p3: La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Reemplaza los 2 valores previamente insertados.
    print_test("Prueba p3: Insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba p3: Obtener clave1 devuelve valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba p3: Insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba p3: Obtener clave2 devuelve valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba p3: La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p3: El ABB fue destruido", true);
}

// Pruebas para guardar claves en un ABB y luego reemplazar sus valores
// çon función de destrucción de datos.
void prueba_abb_reemplazar_con_destruir() {
	printf("-------------INICIO DE PRUEBAS: ABB REEMPLAZAR VALORES CON DESTRUCCIÓN-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    char* clave1 = "perro", *valor1a, *valor1b;
    char* clave2 = "gato", *valor2a, *valor2b;

    // Pide memoria para 4 valores.
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    // Inserta 2 valores.
    print_test("Prueba p4: Insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba p4: Obtener clave1 devuelve valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba p4: Obtener clave1 devuelve valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba p4: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p4: Insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba p4: Obtener clave2 devuelve valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba p4: Obtener clave2 devuelve valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba p4: La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Reemplaza los 2 valores previamente insertados (debe liberar lo que reemplaza).
    print_test("Prueba p4: Insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba p4: Obtener clave1 devuelve valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba p4: Obtener clave1 devuelve valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba p4: La cantidad de elementos es 1", abb_cantidad(abb) == 2);
    print_test("Prueba p4: Insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba p4: Obtener clave2 devuelve valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba p4: Obtener clave2 devuelve valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba p4: La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Se destruye el ABB (se debe liberar lo que quedó dentro).
    abb_destruir(abb);
    print_test("Prueba p4: El ABB fue destruido, y se liberó su contenido", true);
}

// Pruebas para borrar claves de un ABB.
void prueba_abb_borrar() {
	printf("-------------INICIO DE PRUEBAS: ABB BORRAR-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    char* clave1 = "perro", *valor1 = "guau";
    char* clave2 = "gato", *valor2 = "miau";
    char* clave3 = "vaca", *valor3 = "mu";

    // Inserta 3 valores.
    print_test("Prueba p5: Insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba p5: Insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba p5: Insertar clave3", abb_guardar(abb, clave3, valor3));

    // Al borrar cada elemento comprueba que ya no está pero los otros sí.
    print_test("Prueba p5: Pertenece clave3, devuelve true", abb_pertenece(abb, clave3));
    print_test("Prueba p5: Borrar clave3, devuelve valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba p5: Borrar clave3, devuelve NULL", !abb_borrar(abb, clave3));
    print_test("Prueba p5: Pertenece clave3, devuelve falso", !abb_pertenece(abb, clave3));
    print_test("Prueba p5: Obtener clave3, devuelve NULL", !abb_obtener(abb, clave3));
    print_test("Prueba p5: La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba p5: Pertenece clave1, devuelve true", abb_pertenece(abb, clave1));
    print_test("Prueba p5: Borrar clave1, devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba p5: Borrar clave1, devuelve NULL", !abb_borrar(abb, clave1));
    print_test("Prueba p5: Pertenece clave1, devuelve falso", !abb_pertenece(abb, clave1));
    print_test("Prueba p5: Obtener clave1, devuelve NULL", !abb_obtener(abb, clave1));
    print_test("Prueba p5: La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba p5: Pertenece clave2, devuelve true", abb_pertenece(abb, clave2));
    print_test("Prueba p5: Borrar clave2, devuelve valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba p5: Borrar clave2, devuelve NULL", !abb_borrar(abb, clave2));
    print_test("Prueba p5: Pertenece clave2, devuelve falso", !abb_pertenece(abb, clave2));
    print_test("Prueba p5: Obtener clave2, devuelve NULL", !abb_obtener(abb, clave2));
    print_test("Prueba p5: La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p5: El ABB fue destruido", true);
}

// Pruebas para guardar una clave vacía en un ABB.
void prueba_abb_clave_vacia() {
	printf("-------------INICIO DE PRUEBAS: ABB GUARDAR CLAVE VACÍA-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    char* clave = "", *valor = "";

    // Prueba insertar una clave vacía y verifica comportamiento.
    print_test("Prueba p6: Insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba p6: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p6: Obtener clave vacia devuelve valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba p6: Pertenece clave vacia, devuelve true", abb_pertenece(abb, clave));
    print_test("Prueba p6: Borrar clave vacia, devuelve valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba p6: La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p6: El ABB fue destruido", true);
}

// Pruebas para guardar una clave vacía con dato NULL.
void prueba_abb_valor_null() {
	printf("-------------INICIO DE PRUEBAS: ABB GUARDAR CLAVE VACÍA (DATO NULL)-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    char* clave = "", *valor = NULL;

    // Inserta clave con valor NULL.
    print_test("Prueba p7: Insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba p7: La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba p7: Obtener clave vacia devuelve valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba p7: Pertenece clave vacia, devuelve true", abb_pertenece(abb, clave));
    
    // Borra clave con valor NULL.
    print_test("Prueba p7: Borrar clave vacia, devuelve valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba p7: La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p7: El ABB fue destruido", true);
}

// Pruebas para guardar un volumen grande de claves.
void prueba_abb_volumen(size_t largo, bool debug) {
	printf("-------------INICIO DE PRUEBAS: ABB VOLUMEN (CON Y SIN DESTRUCCIÓN)-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char* claves[largo];
    unsigned* valores[largo];

    // Inserta 'largo' parejas en el ABB.
    for (unsigned i = 0; i < largo; i++) {
        claves[i] = malloc(largo_clave);
        valores[i] = malloc(sizeof(unsigned));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }
    // Mezclo el arreglo de strings para que a la hora de guardar 
    // en un ABB, la complejidad temporal no sea O(n) ya que
    // quedaría como una lista.
    mezclar_strings(claves, largo);

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba p8: Almacenar muchos elementos", ok);
    if (debug) print_test("Prueba p8: La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que devuelva los valores correctos.
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba p8: Pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba p8: La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que borre y devuelva los valores correctos.
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok)  {
            break;
       }
    }

    if (debug) print_test("Prueba p8: Borrar muchos elementos", ok);
    if (debug) print_test("Prueba p8: La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruye el ABB y crea uno nuevo que sí libera.
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    // Inserta 'largo' parejas en el abb.
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    for(size_t i = 0; i < largo; i++) {
        free(claves[i]);
    }

    // Destruye el ABB - debería liberar los enteros.
    abb_destruir(abb);
    print_test("Prueba p8: El ABB fue destruido y su contenido liberado", true);
}

// Pruebas para el iterador externo del ABB.
void prueba_abb_iterar() {
	printf("-------------INICIO DE PRUEBAS: ITERADOR EXTERNO ABB-------------\n");

	// Declaro variables a utilizar.
	abb_t *abb = abb_crear(strcmp, NULL);
    char* claves[] = {"perro", "gato", "vaca"};
    char* valores[] = {"guau", "miau", "mu"};

    // Inserta 3 valores.
    print_test("Prueba p9: Insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba p9: Insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba p9: Insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char* clave;
    size_t indice;

    print_test("Prueba p9: El iterador fue creado", iter);
    print_test("Prueba p9: Iterador esta al final, devuelve false", !abb_iter_in_al_final(iter));

    // Primer valor.
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba p9: Iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba p9: Iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba p9: Iterador avanzar devuelve true", abb_iter_in_avanzar(iter));
    print_test("Prueba p9: Iterador no esta al final", !abb_iter_in_al_final(iter));

    // Segundo valor.
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba p9: Iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba p9: Iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba p9: Iterador avanzar devuelve true", abb_iter_in_avanzar(iter));
    print_test("Prueba p9: Iterador no esta al final", !abb_iter_in_al_final(iter));

    // Tercer valor.
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba p9: Iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba p9: Iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba p9: Iterador esta al final", abb_iter_in_al_final(iter));

    // Vuelve a tratar de avanzar.
    print_test("Prueba p9: Iterador ver actual, devuelve NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba p9: Iterador avanzar devuelve false", !abb_iter_in_avanzar(iter));
    print_test("Prueba p9: Iterador esta al final", abb_iter_in_al_final(iter));

    // Destruyo el ABB y el iterador.
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    print_test("Prueba p9: El ABB y su iterador fueron destruidos", true);
}

// Pruebas para iterar un volumen gránde de elementos con el iterador externo.
void prueba_abb_iterar_volumen(size_t largo) {
	printf("-------------INICIO DE PRUEBAS: ITERADOR EXTERNO ABB: VOLUMEN-------------\n");

	// Declaro variables a utilizar.
	abb_t *abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char* claves[largo];
    size_t valores[largo];

    // Inserta 'largo' parejas en el abb.
    for (unsigned i = 0; i < largo; i++) {
        claves[i] = malloc(largo_clave);
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
    }
    // Mezclo el arreglo de strings para que a la hora de guardar 
    // en un ABB, la complejidad temporal no sea O(n) ya que
    // quedaría como una lista.
    mezclar_strings(claves, largo);

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba p10: Iterador no esta al final", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char* clave;
    size_t* valor;

    for (i = 0; i < largo; i++) {
        if (abb_iter_in_al_final(iter)) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if (!clave) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if (!valor) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba p10: Iteración en volumen", ok);
    print_test("Prueba p10: Iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba p10: Iterador esta al final", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if (valores[i] != largo) {
            ok = false;
            break;
        }
    }
    print_test("Prueba p10: Iteración en volumen, se cambiaron todo los elementos", ok);

    for(size_t j = 0; j < largo; j++) {
        free(claves[j]);
    }

    // Destruyo el ABB y el iterador.
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    print_test("Prueba p11: El ABB y su iterador fueron destruidos", true);
}

// Pruebas para el iterador interno sin corte.
void prueba_abb_iterar_interno_sin_corte() {
	printf("-------------INICIO DE PRUEBAS: ITERADOR INTERNO ABB: SIN CORTE-------------\n");

	// Declaro variables a utilizar.
    abb_t* abb = abb_crear(strcmp, NULL);
    size_t tam = 4;
    int datos[4] = {1, 2, 3, 4};
    char* claves[4] = {"perrito", "gatito", "vaquita", "monito"};
    int suma = 0;

    print_test("Prueba p11: El ABB fue creado", abb);

    // Pruebo guardar claves.
    bool ok_guardar = true;
    for (size_t i = 0; i < tam; i++) {
    	ok_guardar &= abb_guardar(abb, *(claves + i), datos + i);
    }
    print_test("Prueba p11: Se guardaron todos los elementos correctamente", ok_guardar);
    print_test("Prueba p11: La cantidad de elementos es 4", abb_cantidad(abb) == tam);

    // Pruebo iterar con el iterador interno.
    abb_in_order(abb, sumar, &suma);
    print_test("Prueba p11: Se sumaron todos los elementos", suma == 10);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p11: El ABB fue destruido", true);
}

// Pruebas para el iterador interno con corte.
void prueba_abb_iterar_interno_con_corte() {
	printf("-------------INICIO DE PRUEBAS: ITERADOR INTERNO ABB: CON CORTE-------------\n");

	// Declaro las variables a utilizar.
	abb_t* abb = abb_crear(strcmp, NULL);
	size_t tam = 7;
	char* claves[7] = {"Clark", "Harrington", "Headey", "Dinklage", "Williams", "Turner", "Momoa"};
    char* datos[7] = {"Emilia", "Kit", "Lena", "Peter", "Maisie", "Sophie", "Jason"};
    char cadena[14] = "";
    char cadena_esperada[14] = "Emilia Peter ";
    
    print_test("Prueba p12: El ABB fue creado", abb);

   	// Pruebo guardar claves.
    bool ok_guardar = true;
    for (size_t i = 0; i < tam; i++) {
    	ok_guardar &= abb_guardar(abb, *(claves + i), *(datos + i));
    }

    print_test("Prueba p12: Se guardaron todos los elementos correctamente", ok_guardar);
    print_test("Prueba p12: La cantidad de elementos es 7", abb_cantidad(abb) == tam);

    // Pruebo iterar con el iterador interno.
    abb_in_order(abb, concatenar_datos, &cadena);
    print_test("Prueba p12: Se logró concatenar correctamente", strcmp(cadena, cadena_esperada) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("Prueba p12: El ABB fue destruido", true);
}

// Pruebas para el iterador externo con un ABB vacío.
void prueba_iterar_abb_vacio() {
	printf("-------------INICIO DE PRUEBAS: ITERADOR EXTERNO ABB: ABB VACÍO-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    // Prueba comportamiento básico de un iterador creado sobre un ABB vacío.
    print_test("Prueba p13: Crear iterador sobre abb vacío", iter);
    print_test("Prueba p13: El iterador está al final", abb_iter_in_al_final(iter));
    print_test("Prueba p13: El iterador no puede avanzar", !abb_iter_in_avanzar(iter));
    print_test("Prueba p13: Ver actual devuelve NULL", !abb_iter_in_ver_actual(iter));

    // Destruyo ABB e iterador.
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    print_test("Prueba p13: El iterador fue destruido", true);
    print_test("Prueba p13: El ABB fue destruido", true);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/
  
void pruebas_abb_alumno() {

	prueba_crear_abb_vacio();
	prueba_abb_guardar();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_clave_vacia();
	prueba_abb_valor_null();
	prueba_abb_volumen(5000, true);
	prueba_abb_iterar();
	prueba_abb_iterar_volumen(5000);
	prueba_abb_iterar_interno_sin_corte();
	prueba_abb_iterar_interno_con_corte();
	prueba_iterar_abb_vacio();
}