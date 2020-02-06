#include "strutil.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(void) {
    /* Ejecuta todas las pruebas unitarias. */
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_strutil();

    return failure_count() > 0;
}
