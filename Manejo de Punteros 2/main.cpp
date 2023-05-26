#include <iostream>
#include <vector>
using namespace std;
#include"factura.h"


int main() {
  // se crea el vector de clientes
  vector<Cliente> clientes;
  cout << "----------------------" << endl;
  cout << "     BIENVENIDO        " << endl;
  cout << "----------------------" << endl;
  // se le pide a el ususario ingresar determinada cantidad de usuarios
  cout << "¿Cuantos clientes desea ingresar?" << endl;
  int n;
  cin>> n;
  // se hace uso de las funciones 
  registrar_datos(clientes,n);
  crear_archivo(clientes,n);
  imprimir_factura(clientes,n);

}