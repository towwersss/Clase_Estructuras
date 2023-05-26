#include <iostream>
using namespace std;
#include "funciones.h"

int main() {
  // se crea el vector de estructuras de tipp javeMusic que almacenala la informacion consignada en archivos de texto
  vector<javeMusic> musica;
  // se crea la variable nombre para almacenar el nombre del archivo
  string nombre;
  // se crea una variables boleana que se la señal para cerrar el programa cuando la persona lo desee
  bool salir = false;
  // se crea la variable opcion para que el usuario digite que funciones quiere ejecutar
  int opcion;
  cout<<"Ingrese el numero de archivo que desea leer (1-5): ";
  cin>>nombre;
  // se pide el numero de archivo y, para que sea mas comodo para la persona, el .txt se añde automaticamente
  nombre=nombre+".txt";
  // se lee el archivo
  cout << "\033[1m\033[33m=== Datos Cargados Exitosamente ===\033[0m" <<endl;
    leer_archivo(nombre, musica);
  //se inicia un while para mostrar el menu y ejecutar lo dicho por quien maneje el programa cuantas veces quiera
    while (salir == false){
      //se imprime el menu
    menu();
      //se pide la opcion
    cin>>opcion;
      // se inicializa un switch que recibe como parametro la opcion para realizar la funcion que digite el usuario.
    switch(opcion){
      // se imprimen autores presentes en orden alfabetico
      case 1: autores_presentes_alfabeticamente(musica);
        break;
      case 2: {
        // se crea la variable autor, se pide su valor y se incerta la funcion para que esta retorne las canciones del autor por orden alfabetico
        string nombreAutor;
        cout << "Ingrese el nombre del autor: ";
        cin>>nombreAutor;
        canciones_autor_alfabeticamente(musica,nombreAutor);
      }
        break;
      //imprime albumes organizados cronologicamente
      case 3:cronologicamente(musica);
        break;
      case 4:{
        // se crea la variable nombreAlbum, se pide su valor y se incerta la funcion para que esta retorne los albumees por orden alfabetico
        string nombreAlbum;
        cout << "Ingrese el nombre del album: ";
        cin>>nombreAlbum;
        listado_de_album_alfabeticamente(musica,nombreAlbum);
      }
      break;
      //se imprimen valores organizados alfabeticamente, primero por album y despues por cancion
      case 5:canciones_y_album_alfabeticamente(musica);
      break;
      // se cambia el valor de la variable salir para finalizar la ejecucion del programa
      case 6: salir=true;
      break;
    }
  }
}