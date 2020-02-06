/*

Escribir una función en C que, dado un arreglo de n cadenas y un entero positivo k,
imprima por pantalla las k cadenas más largas:

*/

// El ejercicio es mas facil usando un heap de minimos.
void imprimir_k_cadenas_largas(const char *cadenas[], size_t n, int k) {

  heap_t* heap = heap_crear(strcmp);

  // Encolo las primeras k cadenas de un arreglo
  // en un heap.
  for (size_t i = 0; i < k; i++) {
    heap_encolar(heap, cadenas[i]);
  }

  // Ahora, voy comparando las cadenas restantes en el array de strings
  // con el minimo del heap, si es mayor la nueva cadena al minimo
  // entonces lo desencolo y encolo la nueva cadena.
  for (size_t i = k; i < n; i++) {
    if (strcmp(cadenas[i], (const char*) heap_ver_minimo(heap)) > 0) {
      heap_desencolar(heap);
      heap_encolar(cadenas[i]);
    }
  }

  // Imprimo las cadenas del heap.
  while (!heap_esta_vacio(heap)) {
    char* cadena = heap_desencolar(heap);
    printf("%s\n", cadena);
  }

  heap_destruir(heap, NULL);
}