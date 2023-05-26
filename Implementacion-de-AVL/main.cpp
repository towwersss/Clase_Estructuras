#include <iostream>
using namespace std;
#include "funciones.h"

int main() {
  ArbolAVL arbol;
  arbol.cargarArbol("entrada.txt", arbol);
  cout<<"la mediana de los datos es:"<<arbol.calcularMediana(arbol.InOrdenAVL(arbol.raiz)) <<endl;
  
}