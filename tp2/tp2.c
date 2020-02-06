#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L // strdup and getline
#define TIME_FORMAT "%FT%T%z"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "hash.h"
#include "abb.h"
#include "lista.h"
#include "heap.h"
#include "strutil.h"

#define CMD_AGREGAR_ARCHIVO "agregar_archivo"
#define CMD_ORDENAR_ARCHIVO "ordenar_archivo"
#define CMD_VER_VISITANTES "ver_visitantes"
#define MSG_ERROR "Error en comando"
#define MSG_VISITANTES "Visitantes:"
#define MSG_OK "OK"
#define SEPARADOR_DATOS '\t'
#define SEPERADOR_BLOQUE_IP '.'
#define SEPARADOR_CMD ' '
#define MAX_LARGO_REGISTRO 200
#define RELACION_BYTE_KB 0.001
#define CAMPO_MEMORIA 1
#define CAMPO_IP 0
#define CAMPO_TIEMPO 1
#define CAMPO_CMD 0
#define CANT_MINIMA_PETICIONES 5
#define MAX_TIEMPO_PETICIONES 2
#define CAMPO_IP_INICIO 1
#define CAMPO_IP_FINAL 2
#define CAMPO_LOG_ENTRADA 1
#define CAMPO_LOG_SALIDA 2
#define CANT_PARAM_AGREGAR_ARCHIVO 1
#define CANT_PARAM_ORDENAR_ARCHIVO 2
#define CANT_PARAM_VER_VISITANTES 2

/**
 * Estructura auxiliar para mergear los registros de cada particion.
 */
typedef struct nodo {
    char* registro;
    size_t num_particion;
} merge_nodo_t;

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

/**
 * Convierte una cadena en formato ISO-8601 a un instante en el tiempo.
 * @param  iso8601: cadena en formato ISO-8601
 * @return una variable de tipo time_t que representa un instante
 * en el tiempo.
 */
time_t iso8601_to_time(const char* iso8601) {

    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}

/**
 * Funcion wrapper de lista_destruir.
 * @param lista: la lista fue creada.
 * Post: la lista fue destruida.
 */
void lista_destruir_wrapper(void* lista) {

    lista_destruir((lista_t*) lista, free);
}

/**
 * Compara dos IPs. Se utilizara en un heap de minimos.
 * @param  una_ip
 * @param  otra_ip
 * @return -1 si una_ip > otra_ip, 1 si una_ip < otra_ip o 0 si
 * son iguales.
 */
int comparar_ips(const char* una_ip, const char* otra_ip) {

    char** bloques_una_ip = split(una_ip, SEPERADOR_BLOQUE_IP);
    char** bloques_otra_ip = split(otra_ip, SEPERADOR_BLOQUE_IP);
    int resultado = 0;

    for (size_t i = 0; bloques_una_ip[i] && bloques_otra_ip[i]; i++) {
        if (atoi(bloques_una_ip[i]) > atoi(bloques_otra_ip[i])) {
            resultado = -1;
            break;
        } else if (atoi(bloques_una_ip[i]) < atoi(bloques_otra_ip[i])) {
            resultado = 1;
            break;
        }
    }
    free_strv(bloques_una_ip);
    free_strv(bloques_otra_ip);
    return resultado;
}

/**
 * Funcion de comparar_ips (inversa) para el ABB. 
 * @param  una_ip
 * @param  otra_ip
 * @return 1 si una_ip > otra_ip, -1 si una_ip < otra_ip o 0 si
 * son iguales.
 */
int comparar_ips_abb(const char* una_ip, const char* otra_ip) {

    return comparar_ips(una_ip, otra_ip) * -1;
}

/**
 * Funcion wrapper de comparar_ips
 * @param  una_ip
 * @param  otra_ip
 * @return -1 si una_ip > otra_ip, 1 si una_ip < otra_ip o 0 si
 * son iguales.
 */
int comparar_ips_wrapper(const void* una_ip, const void* otra_ip) {

    return comparar_ips((const char *) una_ip, (const char *) otra_ip);
}

/**
 * Compara dos registros segun campo de tiempo, y en el caso de ser necesario,
 * por campo de ip y por recurso.
 * @param  un_registro
 * @param  otro_registro
 * @return -1 si un_registro > otro_registro
 * 1 si un_registro < otro_registro.
 */
int comparar_registros(const char* un_registro, const char* otro_registro) {

    char** datos_un_registro = split(un_registro, SEPARADOR_DATOS);
    char** datos_otro_registro = split(otro_registro, SEPARADOR_DATOS);

    int resultado = strcmp(datos_un_registro[CAMPO_TIEMPO], datos_otro_registro[CAMPO_TIEMPO]);
    if (resultado != 0) {
        resultado *= -1;
    } else {
        resultado = comparar_ips(datos_un_registro[CAMPO_IP], datos_otro_registro[CAMPO_IP]);
        if (resultado == 0) {
            resultado = strcmp(un_registro, otro_registro) * -1;
        }
    }

    free_strv(datos_un_registro);
    free_strv(datos_otro_registro);

    return resultado;
}

/**
 * Funcion wrapper de comparar_registros
 * @param  un_registro
 * @param  otro_registro
 * @return -1 si un_registro > otro_registro o 1 si
 * un_registro < otro_registro.
 */
int comparar_registros_wrapper(const void* un_registro, const void* otro_registro) {

    return comparar_registros((const char*) un_registro, (const char*) otro_registro);
}

/**
 * Funcion wrapper de comparar_registros para particiones.
 * @param  un_registro
 * @param  otro_registro
 * @return -1 si un_registro > otro_registro o 1 si
 * un_registro < otro_registro.
 */
int comparar_registros_wrapper_particiones(const void* un_registro, const void* otro_registro) {

    return comparar_registros(((merge_nodo_t*) un_registro)->registro, ((merge_nodo_t*) otro_registro)->registro);
}

/**
 * Abre un archivo.
 * @param  archivo
 * @param  nombre_archivo
 * @param  modo
 * @return true o false segun si se logro abrir o no el archivo.
 * Post: el archivo fue abierto.
 */
bool abrir_archivo(FILE** archivo, char* nombre_archivo, char* modo) {

    *archivo = fopen(nombre_archivo, modo);
    if (!*archivo) {
        return false;
    }
    return true;
}

/**
 * Cierra un archivo.
 * @param archivo: el archivo fue abierto.
 * Post: el archivo fue cerrado.
 */
void cerrar_archivo(FILE** archivo) {

    fclose(*archivo);
}

/**
 * Reemplaza el salto de linea por un fin de string.
 * @param  str
 * Post: el ultimo caracter de la cadena fue modificado en el
 * caso de ser necesario.
 */
void reemplazar_salto_linea(char* str) {

    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/**
 * Guarda la ip y/o su horario de acceso.
 * @param historial_ips: hash donde se almacenara el horario.
 * @param ip: clave del hash.
 * @param horario: dato del hash.
 */
void guardar_horario_ip(hash_t* historial_ips, char* ip, char* horario) {

    time_t tiempo = iso8601_to_time(horario);
    time_t* tiempo_aux = malloc(sizeof(time_t));
    *tiempo_aux = tiempo;

    if (hash_pertenece(historial_ips, ip)) {
        lista_t* horarios = hash_obtener(historial_ips, ip);
        lista_insertar_ultimo(horarios, tiempo_aux);
    } else {
        lista_t* nueva_ip_tiempos = lista_crear();
        lista_insertar_ultimo(nueva_ip_tiempos, tiempo_aux);
        hash_guardar(historial_ips, ip, nueva_ip_tiempos);
    }
}

/**
 * Imprime las ips sospechosas de ataque DoS.
 * @param ips_sospechosas: heap que contiene las ips sospechosas
 * Post: el heap queda vacio.
 */
void imprimir_ips_sospechosas(heap_t* ips_sospechosas) {

    while (!heap_esta_vacio(ips_sospechosas)) {
        char* ip_a_imprimir = heap_desencolar(ips_sospechosas);
        fprintf(stdout, "DoS: %s\n", ip_a_imprimir);
        free(ip_a_imprimir);
    }
    fprintf(stdout, "%s\n", MSG_OK);
}

/**
 * Detecta un posible ataque de DoS segun las especificaciones dadas
 * @param historial_ips: hash que contiene el historial con las ips.
 */
void detectar_ataque_dos(hash_t* historial_ips) {

    heap_t* ips_sospechosas = heap_crear(comparar_ips_wrapper);
    hash_iter_t* iter = hash_iter_crear(historial_ips);

    while (!hash_iter_al_final(iter)) {
        const char* ip = hash_iter_ver_actual(iter);
        lista_t* horarios_ip = hash_obtener(historial_ips, ip);
        if (lista_largo(horarios_ip) < CANT_MINIMA_PETICIONES) {
            hash_iter_avanzar(iter);
            continue;
        }
        lista_iter_t* iter_lista = lista_iter_crear(horarios_ip);
        lista_iter_t* otro_iter_lista = lista_iter_crear(horarios_ip);
        for (size_t i = 0; i < CANT_MINIMA_PETICIONES - 1; i++) {
            lista_iter_avanzar(otro_iter_lista);
        }
        while (!lista_iter_al_final(otro_iter_lista)) {
            time_t* un_horario = lista_iter_ver_actual(iter_lista);
            time_t* otro_horario = lista_iter_ver_actual(otro_iter_lista);
            if (difftime(*otro_horario, *un_horario) < MAX_TIEMPO_PETICIONES) {
                // Copio la IP por un tema de tipo de parametros entre heap_encolar
                // y hash_iter_ver_actual.
                char* ip_actual = strdup(ip);
                if (!ip_actual) {
                    return;
                }
                heap_encolar(ips_sospechosas, ip_actual);
                break;
            }
            lista_iter_avanzar(iter_lista);
            lista_iter_avanzar(otro_iter_lista);
        }
        lista_iter_destruir(iter_lista);
        lista_iter_destruir(otro_iter_lista);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    imprimir_ips_sospechosas(ips_sospechosas);
    heap_destruir(ips_sospechosas, NULL);
}

/**
 * Crea el nombre para un archivo de particion.
 * @param  nombre: nombre del prefijo del archivo, puede ser el nombre del
 * archivo original.
 * @param  particion: numero de particion a crear.
 * @return nombre de la particion.
 */
char* crear_nombre_particion(const char* nombre, size_t particion) {

    char* nombre_archivo = malloc(sizeof(char) * (strlen(nombre) + 5));
    sprintf(nombre_archivo, "%s_%02zu", nombre, particion);

    return nombre_archivo;
}

/**
 * Crea el FILE* para la particion, en el modo que sea necesario.
 * @param  nombre
 * @param  particion
 * @param  modo 
 * @return archivo de particion abierto.
 */
FILE* crear_archivo_particion(const char* nombre, size_t particion, char* modo) {

    char* nombre_archivo = crear_nombre_particion(nombre, particion);
    FILE* salida_actual = fopen(nombre_archivo, modo);
    free(nombre_archivo);

    return salida_actual;
}

/**
 * Abre todas las particiones.
 * @param  nombre_log_entrada
 * @param  num_particiones
 * @param  particiones
 * @return una lista con todos los nombres de las particiones.
 * Post: los archivos fueron abiertos.
 */
lista_t* abrir_particiones(char* nombre_log_entrada, size_t num_particiones, FILE** particiones) {

    lista_t* nombres_particiones = lista_crear();

    for (size_t i = 1; i <= num_particiones; i++) {
        char* nombre_particion = crear_nombre_particion(nombre_log_entrada, i);
        lista_insertar_ultimo(nombres_particiones, nombre_particion);
        if (!abrir_archivo(&particiones[i - 1], nombre_particion, "r")) {
            fprintf(stderr, "%s %s\n", MSG_ERROR, CMD_ORDENAR_ARCHIVO);
        }
    }
    return nombres_particiones;
}

/**
 * Cierra todas las particiones.
 * @param num_particiones
 * @param particiones
 * @param nombres_particiones
 * Post: las particiones fueron eliminadas y la lista destruida.
 */
void cerrar_particiones(size_t num_particiones, FILE** particiones, lista_t* nombres_particiones) {

    for (size_t i = 1; i <= num_particiones; i++) {
        cerrar_archivo(&particiones[i - 1]);
        char* nombre_particion = lista_borrar_primero(nombres_particiones);
        remove(nombre_particion);
        free(nombre_particion);
    }
    lista_destruir(nombres_particiones, NULL);
}

/**
 * Almacena en un heap un nodo que contiene un registro y el origen del
 * que provine ese registro.
 * @param linea 
 * @param nodo
 * @param num_particion
 * @param registros
 */
void guardar_registro(char* linea, merge_nodo_t* nodo, size_t num_particion, heap_t* registros) {

    char* linea_aux = strdup(linea);
    if (!linea_aux) {
        return;
    }
    nodo->registro = linea_aux;
    nodo->num_particion = num_particion;
    heap_encolar(registros, nodo);
}

/**
 * Traspasa los elementos de una lista hacia un arreglo.
 * @param lista
 * @param datos
 */
void lista_a_arr(lista_t* lista, void** datos) {

    for (size_t i = 0; !lista_esta_vacia(lista); i++) {
        char* dato_aux = lista_borrar_primero(lista);
        datos[i] = dato_aux;
    }
}

/**
 * Mergea todas las particiones ordenadas en un solo archivo.
 * @param  nombre_log_entrada
 * @param  nombre_log_salida
 * @param  num_particiones
 * @return true o false segun si se pudo realizar o no la operacion.
 */
bool merge_particiones_ordenadas(char* nombre_log_entrada, char* nombre_log_salida, size_t num_particiones) {

    FILE* log_ordenado;
    if (!abrir_archivo(&log_ordenado, nombre_log_salida, "w")) {
        fprintf(stderr, "%s %s\n", MSG_ERROR, CMD_ORDENAR_ARCHIVO);
        return false;
    }

    FILE* particiones[num_particiones];
    heap_t* registros = heap_crear(comparar_registros_wrapper_particiones);
    char* linea = NULL; size_t cantidad = 0; ssize_t leidos;

    // Abro todas las particiones.
    lista_t* nombres_particiones = abrir_particiones(nombre_log_entrada, num_particiones, particiones);

    // Guardo la primera linea de cada particion.
    for (size_t i = 0; i < num_particiones; i++) {
        merge_nodo_t* nodo = malloc(sizeof(merge_nodo_t));
        getline(&linea, &cantidad, particiones[i]);
        guardar_registro(linea, nodo, i, registros);
    }

    // Merge.
    while (!heap_esta_vacio(registros)) {
        merge_nodo_t* nodo = heap_desencolar(registros);
        fprintf(log_ordenado, "%s", nodo->registro);
        if ((leidos = getline(&linea, &cantidad, particiones[nodo->num_particion])) > 0) {
            merge_nodo_t* nuevo_nodo = malloc(sizeof(merge_nodo_t));
            guardar_registro(linea, nuevo_nodo, nodo->num_particion, registros);
        }
        free(nodo->registro);
        free(nodo);
    }

    // Cierro particiones, las elimino y libero memoria.
    cerrar_particiones(num_particiones, particiones, nombres_particiones);
    heap_destruir(registros, NULL);
    free(linea);
    cerrar_archivo(&log_ordenado);
    fprintf(stdout, "%s\n", MSG_OK);

    return true;
}

/**
 * Genera archivo de particiones ordenadas.
 * @param  nombre_log_entrada
 * @param  nombre_log_salida
 * @param  elementos_maximos: cantidad de elementos maximos que tendra
 * cada particion.
 * @return true o false según si se puedo realizar o no la operacion.
 */
bool generar_particiones_ordenadas(char* nombre_log_entrada, char* nombre_log_salida, size_t elementos_maximos) {

    FILE* log;
    if (!abrir_archivo(&log, nombre_log_entrada, "r")) {
        fprintf(stderr, "%s %s\n", MSG_ERROR, CMD_ORDENAR_ARCHIVO);
        return false;
    }

    char* linea = NULL; size_t cantidad = 0, cant_particiones = 1; ssize_t leidos;
    heap_t* registros = heap_crear(comparar_registros_wrapper);
    lista_t* registros_lista = lista_crear();

    for (size_t i = 0; i < elementos_maximos; i++) {
        if ((leidos = getline(&linea, &cantidad, log)) <= 0) {
            break;
        }
        char* linea_aux = strdup(linea);
        if (!linea_aux) {
            return false;
        }
        heap_encolar(registros, linea_aux);
    }

    FILE* particion = crear_archivo_particion(nombre_log_entrada, cant_particiones, "w");
    cant_particiones++;

    // Genero las particiones ordenadas con el metodo replacement-selection.
    do {
        while (!heap_esta_vacio(registros)) {
            char* registro = heap_desencolar(registros);
            fprintf(particion, "%s", registro);
            if ((leidos = getline(&linea, &cantidad, log)) > 0) {
                char* linea_aux = strdup(linea);
                if (!linea_aux) {
                    return false;
                }
                if (comparar_registros(linea_aux, registro) <= 0) {
                    heap_encolar(registros, linea_aux);
                } else {
                    lista_insertar_ultimo(registros_lista, linea_aux);
                }
            }
            free(registro);
        }
        cerrar_archivo(&particion);
        size_t cant_registros = lista_largo(registros_lista);
        void* registros_arr[cant_registros];
        lista_a_arr(registros_lista, registros_arr);
        heap_destruir(registros, NULL);
        registros = heap_crear_arr(registros_arr, cant_registros, comparar_registros_wrapper);
        if (!heap_esta_vacio(registros)) {
            particion = crear_archivo_particion(nombre_log_entrada, cant_particiones, "w");
            cant_particiones++;
        }
    } while (!heap_esta_vacio(registros));

    free(linea);
    cerrar_archivo(&log);
    heap_destruir(registros, NULL);
    lista_destruir(registros_lista, NULL);

    return merge_particiones_ordenadas(nombre_log_entrada, nombre_log_salida, cant_particiones - 1);
}

/**
 * Imprime una direccion de IP.
 * @param ip
 * @return True o False segun si se pudo realizar la operacion o no.
 */
bool imprimir_visitantes(const char* ip) {

    if (!ip) {
        return false;
    }
    fprintf(stdout, "\t%s\n", ip);
    return true;
}

/**
 * Imprime por stderr un mensaje de error.
 * @param linea_comando
 * @param comando
 * Post: la memoria pedida para linea_comando es liberada.
 */
void imprimir_mensaje_error(char** linea_comando, char* comando) {

    fprintf(stderr, "%s %s\n", MSG_ERROR, comando);
    free_strv(linea_comando);
}

/* *****************************************************************
 *                     FUNCIONES PRINCIPALES
 * *****************************************************************/

/**
 * Almacena las IPs de un archivo para posterior uso.
 * @param  nombre_archivo
 * @param  ips_visitantes
 * @return true o false segun si se pudo agregar las IPs del archivo.
 */
bool agregar_archivo(char* nombre_archivo, abb_t* ips_visitantes) {

    FILE* log;
    if (!abrir_archivo(&log, nombre_archivo, "r")) {
        fprintf(stderr, "%s %s\n", MSG_ERROR, CMD_AGREGAR_ARCHIVO);
        return false;
    }

    hash_t* historial_ips = hash_crear(lista_destruir_wrapper);
    char* linea = NULL; size_t cantidad = 0; ssize_t leidos;

    // Leo del archivo y voy almacenando IP con sus tiempos en un
    // hash y las IP en un ABB para ver_visitantes.
    while ((leidos = getline(&linea, &cantidad, log)) > 0) {
        char** datos_log = split(linea, SEPARADOR_DATOS);
        abb_guardar(ips_visitantes, datos_log[CAMPO_IP], NULL);
        guardar_horario_ip(historial_ips, datos_log[CAMPO_IP], datos_log[CAMPO_TIEMPO]);
        free_strv(datos_log);
    }

    free(linea);
    detectar_ataque_dos(historial_ips);
    cerrar_archivo(&log);
    hash_destruir(historial_ips);

    return true;
}

/**
 * Genera un log ordenado con la informacion proveniente
 * de un log de entrada.
 * @param  nombre_log_entrada
 * @param  nombre_log_salida 
 * @param  max_memoria: maxima cantidad de memoria a utilizar a la hora de
 * ordenar un archivo.
 * @return true o false segun si se pudo ordenar el archivo o no.
 */
bool ordenar_archivo(char* nombre_log_entrada, char* nombre_log_salida, int max_memoria) {

    double elementos_maximos = max_memoria / (MAX_LARGO_REGISTRO * RELACION_BYTE_KB);

    return generar_particiones_ordenadas(nombre_log_entrada, nombre_log_salida, (int) elementos_maximos);
}

/**
 * Imprime las ips visitantes que se encuentran entre la ip de inicio
 * y la ip final.
 * @param  ips_visitantes: el arbol fue creado.
 * @param  ip_inicio
 * @param  ip_final
 * @return true o false según si se logro realizar la operacion.
 */
bool ver_visitantes(abb_t* ips_visitantes, char* ip_inicio, char* ip_final) {

    fprintf(stdout, "%s\n", MSG_VISITANTES);
    abb_in_order_range(ips_visitantes, imprimir_visitantes, ip_inicio, ip_final);
    fprintf(stdout, "%s\n", MSG_OK);
    return true;
}

/**
 * Ejecuta el comando correspondiente.
 * @param  linea_comando: comando recibido por stdin.
 * @param  ips_visitantes
 * @param  max_memoria: maxima cantidad de memoria a utilizar a la hora de
 * ordenar un archivo.
 * @return true o false segun si se pudo ejecutar el comando o no.
 */
bool ejecutar_comando(char** linea_comando, abb_t* ips_visitantes, int max_memoria) {

    bool resultado;

    if (strcmp(linea_comando[CAMPO_CMD], CMD_AGREGAR_ARCHIVO) == 0) {
        // Si existen mas de 1 parametro, son ignorados y el comando
        // se ejecuta igual. 
        if (!linea_comando[CAMPO_LOG_ENTRADA]) {
            imprimir_mensaje_error(linea_comando, CMD_AGREGAR_ARCHIVO);
            return false;
        }
        resultado = agregar_archivo(linea_comando[CAMPO_LOG_ENTRADA], ips_visitantes);

    } else if (strcmp(linea_comando[CAMPO_CMD], CMD_ORDENAR_ARCHIVO) == 0) {
        // Si existen mas de 2 parametros, son ignorados y el comando
        // se ejecuta igual.
        if (!linea_comando[CAMPO_LOG_ENTRADA] || !linea_comando[CAMPO_LOG_SALIDA]) {
            imprimir_mensaje_error(linea_comando, CMD_ORDENAR_ARCHIVO);
            return false;
        }
        resultado = ordenar_archivo(linea_comando[CAMPO_LOG_ENTRADA], linea_comando[CAMPO_LOG_SALIDA], max_memoria);

    } else if (strcmp(linea_comando[CAMPO_CMD], CMD_VER_VISITANTES) == 0) {
        // Si existen mas de 2 parametros, son ignorados y el comando
        // se ejecuta igual.
        if (!linea_comando[CAMPO_IP_INICIO] || !linea_comando[CAMPO_IP_FINAL]) {
            imprimir_mensaje_error(linea_comando, CMD_VER_VISITANTES);
            return false;
        }
        resultado = ver_visitantes(ips_visitantes, linea_comando[CAMPO_IP_INICIO], linea_comando[CAMPO_IP_FINAL]);
        
    } else {
        imprimir_mensaje_error(linea_comando, linea_comando[CAMPO_CMD]);
        return false;
    }
    free_strv(linea_comando);
    return resultado;
}

/**
 * Lee los comandos ingresados por entrada estandar.
 * @param memoria_disponible: maxima memoria disponible para realizar
 * el ordenamiento de un archivo.
 * @param ips_visitantes: el arbol fue creado.
 */
void leer_entrada_estandar(char* memoria_disponible, abb_t* ips_visitantes) {

    char* linea = NULL; size_t cantidad = 0; ssize_t leidos;

    while ((leidos = getline(&linea, &cantidad, stdin)) > 0) {
        reemplazar_salto_linea(linea);
        char** linea_comando = split(linea, SEPARADOR_CMD);
        int max_memoria = atoi(memoria_disponible);
        if (!ejecutar_comando(linea_comando, ips_visitantes, max_memoria)) {
            break;
        }
    }
    free(linea);  
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "%s\n", MSG_ERROR);
        return 1;
    }

    for (size_t i = 0; argv[CAMPO_MEMORIA][i]; i++) {
        if (!isdigit(argv[CAMPO_MEMORIA][i])) {
            fprintf(stderr, "%s %s\n", MSG_ERROR, argv[CAMPO_MEMORIA]);
            return 1;
        }
    }

    abb_t* ips_visitantes = abb_crear(comparar_ips_abb, NULL);
    leer_entrada_estandar(argv[1], ips_visitantes);
    abb_destruir(ips_visitantes);

    return 0;
}