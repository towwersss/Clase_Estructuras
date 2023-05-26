/* 
Fecha de entrega: 20 de Febrero de 2020
Nombre: Paula Sofia Torres Rodriguez
Actividad: Taller 00 - Primer Punto
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {
  // se crea un array de 10 posiciones y una variable "i" que funcionará como iterador
    int array[10], i;
  // se usa la funcion "srand" para generar numeros aleatorios en un intervalo de tiempo 0
    srand(time(0));
    cout << "Numeros aleatorios: ";
  // se crea un for en el que se incertan 10 numeros del 0-26 en el arreglo 
    for (i=0;i<10;i++) {
        array[i] =  rand() % 26;
        cout << array[i] << " ";
    }
    cout <<endl;
  // se crea un puntero
    int *puntero;
  // se le asigna al puntero el array (en este punto, el puntero esta viendo la primera posicion del array)
    puntero = array;

    cout<< "contenido del array: " ;
  // se imprime el contenido del array. Para esto se hace uso del operador "*".
    for (i=0;i<10;i++) {
        cout << *(puntero + i) << " ";
    }

    cout <<endl;
    cout<< "Direcciones de memoria: ";
  // se imprime las direcciones de memoria de cada una de las pocisiones del array. Para esto se omite uso del operador "*".
    for (i=0;i<10;i++) {
        cout << (puntero + i) << " ";
    }

}
