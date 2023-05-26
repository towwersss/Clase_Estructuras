#include <iostream>
#include <vector>
using namespace std;
#include"factura.h"
#include <fstream>

// se crea la función de para registrar los datos en la estructura de clientes. Se reciben como parametro el vector por referencia de tipo clientes y el tamaño.

void registrar_datos(vector<Cliente> &clientes, int n){
  for (int i=0;i<n;i++){
    // se crea un objeto de tipo cliente y un apuntdor
    Cliente c, *ptr;
    // se le asigna al apuntador el valor de memoria de el objeto c
    ptr = &c;
    cout<< " |  Nombre  |->" ;
    cin>>ptr->nombre;
    cout<< " |   Edad   |->";
    cin>>ptr->edad;
    cout<< " | Telefono |->";
    cin>>ptr->telefono;
    cout<< " |   Total  |->";
    cin>>ptr->total;
    // despues de almacenar la informacion en el apuntador pasamos añadimos los valores guardados al final del vector
    clientes.push_back(*ptr);
  }
}
// se crea funcion para generar un archivo, se reciben como parametros el vector por referencia de tipo clientes y el tamaño.
void crear_archivo(vector<Cliente> &clientes, int n){
  // se crea un apuntador 
  Cliente *ptr;
  string nombreArchivo = "factura.txt";
  // se abre el archivo y se especifica por medio del ::app que los datos se añaden al final del archivo
  ofstream f(nombreArchivo, ios::app);
  // se abre el archivo
  if(f.is_open()){
    // se recorre la el vector de estructuras
    for (int i = 0; i<n; i ++){
      // se le asigna al apuntador cada uno de los objetos de la estructura
      ptr=&clientes[i];
      // se ingresan los datos del objeto en el archivo
      f << "Nombre: " << ptr->nombre << " Edad:" << ptr->edad << " Telefono:"<< ptr->telefono<<" Total: "<<ptr->total<<endl;
    }
    // se cierra el archivo
    f.close();
  }
}
void imprimir_factura(vector<Cliente> &clientes, int n){
  // se crea un apuntador de clientes
  Cliente *ptr;
  // se crea una variable para capturar las lineas
  string line;
  // se declara nombre del archivo
  string nombreArchivo = "factura.txt";
  cout << "---------------------------" <<endl;
  cout << "       F A C T U R A       " <<endl;
  cout << "---------------------------" <<endl;
  // se abre el archivo
  ifstream f(nombreArchivo, ios::in);
  if(f.is_open()){
    // se obtiene la linea y se imprime
    while(getline(f, line)){
      cout << "       C L I E N T E   " << endl;
      cout << line << endl;
      
    }
  }
}