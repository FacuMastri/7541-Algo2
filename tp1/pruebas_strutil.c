#include "strutil.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void pruebas_split() {
	printf("-------------INICIO DE PRUEBAS SPLIT: EJEMPLO GENERAL-------------\n");

	// Declaro las variables a utilizar.
	char* string = "abc,def,ghi";
	char* sub_string1 = "abc";
	char* sub_string2 = "def";
	char* sub_string3 = "ghi";
	char** array = split(string, ',');

	size_t largo_array = 0;
	while (array[largo_array]) {
		largo_array ++;
	}

	// Verifico si coincide cada substring con lo esperado.
	print_test("El primer substring es el correcto", strcmp(sub_string1, array[0]) == 0);
	print_test("El segundo substring es el correcto", strcmp(sub_string2, array[1]) == 0);
	print_test("El tercero substring es el correcto", strcmp(sub_string3, array[2]) == 0);
	print_test("El largo del arreglo dinámico de cadenas dinámicas es el correcto", largo_array == 3);

	free_strv(array);
	print_test("El arreglo dinámico de cadenas dinámicas fue destruido", true);
}

void pruebas_split_casos_bordes() {

	// Declaro las variables a utilizar.
	char* ejemplo1 = "abc,,def";
	char* ejemplo2 = "abc,def,";
	char* ejemplo3 = ",abc,def";
	char* ejemplo4 = "";
	char* ejemplo5 = ",";

	// Pruebo comportamiento de split.
    char** array = split(ejemplo1, ',');
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 1-------------\n");
    print_test("Prueba caso borde 1: La posición 0 en el arreglo dinámico es la correcta", strcmp(array[0],"abc") == 0);
    print_test("Prueba caso borde 1: La posición 1 en el arreglo dinámico es la correcta", strcmp(array[1],"\0") == 0);
    print_test("Prueba caso borde 1: La posición 2 en el arreglo dinámico es la correcta", strcmp(array[2],"def") == 0);
    print_test("Prueba caso borde 1: El arreglo dinámico termina en NULL", array[3] == NULL);

    // Destruyo el arreglo dinámico de cadenas, y todas las cadenas que contiene.
    free_strv(array);
    print_test("Prueba caso borde 1: El arreglo dinámico de cadenas dinámicas fue destruido", true);

    // Pruebo comportamiento de split.
    array = split(ejemplo2, ',');
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 2-------------\n");
    print_test("Prueba caso borde 2: La posición 0 en el arreglo dinámico es la correcta", strcmp(array[0],"abc") == 0);
    print_test("Prueba caso borde 2: La posición 1 en el arreglo dinámico es la correcta", strcmp(array[1],"def") == 0);
    print_test("Prueba caso borde 2: La posición 2 en el arreglo dinámico es la correcta", strcmp(array[2],"\0") == 0);
    print_test("Prueba caso borde 2: El arreglo dinámico termina en NULL", array[3] == NULL);
    free_strv(array);
    print_test("Prueba caso borde 2: El arreglo dinámico de cadenas dinámicas fue destruido", true);

    // Pruebo comportamiento de split.
    array = split(ejemplo3, ',');
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 3-------------\n");
    print_test("Prueba caso borde 3: La posición 0 en el arreglo dinámico es la correcta", strcmp(array[0],"\0") == 0);
    print_test("Prueba caso borde 3: La posición 1 en el arreglo dinámico es la correcta", strcmp(array[1],"abc") == 0);
    print_test("Prueba caso borde 3: La posición 2 en el arreglo dinámico es la correcta", strcmp(array[2],"def") == 0);
    print_test("Prueba caso borde 3: El arreglo dinámico termina en NULL", array[3] == NULL);

    // Destruyo el arreglo dinámico de cadenas, y todas las cadenas que contiene.
    free_strv(array);
    print_test("Prueba caso borde 3: El arreglo dinámico de cadenas dinámicas fue destruido", true);

    // Pruebo comportamiento de split.
    array = split(ejemplo4, ',');
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 4-------------\n");
    print_test("Prueba caso borde 4: La posición 0 en el arreglo dinámico es la correcta", strcmp(array[0],"\0") == 0);
    print_test("Prueba caso borde 4: El arreglo dinámico termina en NULL", array[1] == NULL);

    // Destruyo el arreglo dinámico de cadenas, y todas las cadenas que contiene.
    free_strv(array);
    print_test("Prueba caso borde 4: El arreglo dinámico de cadenas dinámicas fue destruido", true);

    // Pruebo comportamiento de split.
    array = split(ejemplo5, ',');
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 5-------------\n");
    print_test("Prueba caso borde 5: La posición 0 en el arreglo dinámico es la correcta", strcmp(array[0],"\0") == 0);
    print_test("Prueba caso borde 5: La posición 1 en el arreglo dinámico es la correcta", strcmp(array[1],"\0") == 0);
    print_test("Prueba caso borde 5: El arreglo dinámico termina en NULL", array[2] == NULL);

    // Destruyo el arreglo dinámico de cadenas, y todas las cadenas que contiene.
    free_strv(array);
    print_test("Prueba caso borde 5: El arreglo dinámico de cadenas dinámicas fue destruido", true);

    // Pruebo comportamiento de split.
    printf("-------------INICIO DE PRUEBAS SPLIT: CASO BORDE 6-------------\n");
    print_test("Prueba caso borde 6: El caracter de seperacion es /0", split(ejemplo1, '\0') == NULL);
}

void pruebas_join() {

	// Declaro las variables a utilizar.
	char **strv = split("abc,def,ghi", ',');
	char *resultado1 = join(strv, ';');

	// Pruebo comportamiento de join.
	printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 1-------------\n");
	print_test("Prueba ejemplo 1: El resultado de hacer split y luego join es el correcto", strcmp(resultado1, "abc;def;ghi") == 0);
	print_test("Prueba ejemplo 1: La cadena devuelta por join termina en /0", resultado1[11] == '\0');

	// Destruyo las cadenas.
	free(resultado1);
	free_strv(strv);
	print_test("Prueba ejemplo 1: La cadena devuelta por join fue destruida", true);

	// Declaro las variables a utilizar
	char **palabras = split("Hola mundo", ' ');
	char *resultado2 = join(palabras, ',');

	// Pruebo comportamiento de join.
	printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 2-------------\n");
	print_test("Prueba ejemplo 2: El resultado de hacer split y luego join es el correcto", strcmp(resultado2, "Hola,mundo") == 0);
	print_test("Prueba ejemplo 2: La cadena devuelta por join termina en /0", resultado2[10] == '\0');

	// Destruyo las cadenas.
	free(resultado2);
	free_strv(palabras);
	print_test("Prueba ejemplo 2: La cadena devuelta por join fue destruida", true);

    // Declaro las variables a utilizar.
    char** ejemplo3 = split("abc,def,ghi,jfjfjf,kfeifekfiekfi,fowoowowow,algomaddalegatofuncionlaaa", ',');
    char* resultado3 = join(ejemplo3, ';');

    // Pruebo comportamiento de join.
    printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 3-------------\n");
    print_test("Prueba ejemplo 3: El resultado de hacer split y luego join es el correcto", strcmp(resultado3, "abc;def;ghi;jfjfjf;kfeifekfiekfi;fowoowowow;algomaddalegatofuncionlaaa") == 0);
    print_test("Prueba ejemplo 3: La cadena devuelta por join termina en /0", resultado3[strlen(resultado3)] == '\0');

    // Destruyo las cadenas.
    free(resultado3);
    free_strv(ejemplo3);
    print_test("Prueba ejemplo 3: La cadena devuelta por join fue destruida", true);

    // Declaro las variables a utilizar.
    char* ejemplo4 = malloc(1 * sizeof(char));
    ejemplo4[0] = '\0';

    // Pruebo comportamiento de join.
    printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 4-------------\n");
    print_test("Prueba ejemplo 4: El resultado de hacer split y luego join es el correcto", strcmp(ejemplo4, "") == 0);
    print_test("Prueba ejemplo 4: La cadena devuelta por join termina en /0", ejemplo4[0] == '\0');

    // Destruyo la cadena.
    free(ejemplo4);
    print_test("Prueba ejemplo 4: Las cadenas fueron destruidas", true);

    // Declaro las variables a utilizar.
    char* ejemplo5[3] = {"", "", NULL};
    char* resultado5 = join(ejemplo5, ',');

    // Pruebo comportamiento de join.
    printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 5-------------\n");
    print_test("Prueba ejemplo 5: El resultado de hacer split y luego join es el correcto", strcmp(resultado5, ",") == 0);
    print_test("Prueba ejemplo 5: La cadena devuelta por join termina en /0", resultado5[1] == '\0');

    // Destruyo la cadena.
    free(resultado5);

    // Declaro las variables a utilizar.
    char* ejemplo6[2] = {"", NULL};
    char* resultado6 = join(ejemplo6, 'x');

    // Pruebo comportamiento de join.
    printf("-------------INICIO DE PRUEBAS JOIN: EJEMPLO 6-------------\n");
    print_test("Prueba ejemplo 6: El resultado de hacer split y luego join es el correcto", strcmp(resultado6, "") == 0);
    print_test("Prueba ejemplo 6: La cadena devuelta por join termina en /0", resultado6[0] == '\0');

    // Destruyo la cadena.
    free(resultado6);
}

void pruebas_strutil() {

    pruebas_split();
    pruebas_split_casos_bordes();
    pruebas_join();
}
