/* 
En un colegio de Villa General Belgrano, los alumnos deben formar de la siguiente manera: primero las
niñas ordenadas por altura de menor a mayor. Luego los niños, también ordenados por altura de menor a
mayor. Escribir una función en C que reciba una cola de enteros (representando las alturas de los alumnos
en centímetros), y devuelva true si es posible que estén bien formados (considerando sólo las alturas) o
false en caso contrario. Se puede vaciar la cola sin necesidad de dejarla como se la recibió. Por ejemplo:

• Primero -> [ 125, 128, 129, 124, 134, 138, 140 ]: true
• Primero -> [ 125, 128, 129, 133, 134, 138, 140 ]: true
• Primero -> [ 125, 120, 129, 133, 124, 138, 140 ]: false

Indicar el orden del algoritmo.
*/

// Evalua si la formacion de alturas de los alumnos es correcta.
// Pre: La cola fue creada.
// Post: devuelve true o false según corresponda.
bool es_cola_bien_formada(cola_t* cola_alturas) {

	bool bien_formados = true;
	size_t contador_altura_irregular = 0;

	while (!cola_esta_vacia(cola_alturas)) {
		int altura_act = *((int*) cola_desencolar(cola_alturas)); // Primero, casteo a int* el void* que sale de la cola, luego desreferencio todo con *.
		if (!cola_ver_primero(cola_alturas)) { // Fixea el error de cuando llego a desencolar el ultimo y despues no tengo primero.
			break;
		}
		int altura_sig = *((int*) cola_ver_primero(cola_alturas));
		if (altura_act > altura_sig) {
			contador_altura_irregular ++;
		}
		if (contador_altura_irregular > 1) {
			bien_formados = false;
			break;
		}
	}

	return bien_formados;
}



