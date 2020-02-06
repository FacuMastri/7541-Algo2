/*
Se tiene un arreglo ordenado de N enteros. Sabiendo que cada elemento
se repetira a lo sumo log(n) veces, implementar una funcion O(logn) que
devuelva la cantidad de apariciones de un numero K pasado por parametro.

Justificar el orden de la funcion implementada. Es necesaria la precondicion
mencionada sobre la cantidad de repeticiones? Por que?

Pista: Cual seria el orden en un arreglo con n elementos iguales?
Y si todos los elementos fueran diferentes?
*/


// 1) Use Binary search to get index of the first occurrence of x in arr[]. Let the index of the first occurrence be i.
// 2) Use Binary search to get index of the last occurrence of x in arr[]. Let the index of the last occurrence be j.
// 3) Return (j – i + 1);

