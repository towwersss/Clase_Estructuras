#include <iostream>
using namespace std;
#include "funciones.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <string.h>

// se crea funcion para mostrar el menu de opciones
void menu(){
    cout << endl;
    cout << "\033[1m\033[34m ==== MENÚ PRINCIPAL ==== \033[0m" << endl;
    cout << "Ingrese el número de la opción que desea visualizar de la lista:" << endl;
    cout << "\033[1m\033[32m1. Listar todos los autores presentes, ordenados alfabéticamente.\033[0m" << endl;
    cout << "\033[1m\033[32m2. Listar todas las canciones de un autor, ordenadas alfabéticamente.\033[0m" << endl;
    cout << "\033[1m\033[32m3. Listar todos los álbumes presentes, ordenados cronológicamente.\033[0m" << endl;
    cout << "\033[1m\033[32m4. Listar todas las canciones de un álbum, ordenadas alfabéticamente.\033[0m" << endl;
    cout << "\033[1m\033[32m5. Listar todas las canciones y su álbum, ordenadas alfabéticamente por álbum y canción.\033[0m" << endl;
    cout << "\033[1m\033[31m6. Salir\033[0m" << endl; 
    cout << endl;
}

//funcion permite leer el archivo
void leer_archivo(string nombreArchivo, vector<javeMusic>& musica){
  // se declara la variable que almacenará las lineas del archivo
  string line;
  ifstream f(nombreArchivo, ios::in);
  if(f.is_open()){
    getline(f, line);
    while (getline(f, line)) {
      // se crea un objeto llamado "m" el cual es de tipo javeMusic par almacenar los datos del txt en la estructura
        javeMusic m;
      // se inicializa la posicion de lectura del txt en 0
        size_t pos = 0;
        // se crea la variable "pos" almacena el resultado de la funcion "find". Este es la primera ocurrencia de la cadena "|", presente en la linea
        pos = line.find("|");
      // por medio de la funcion "substr" se extrae el string que va desde la primera posicion en la que encuentra el caracter "|" hasta la aquella que sea igual a la diferencia con la que le prosigue. 

      // se realiza el proceso explicado anteriormente para almacenar en la estructura el nombre, autor, genero, album y año 
        m.nombre = line.substr(0, pos);
        size_t pos_autor = pos + 1;
        pos = line.find('|', pos_autor);
        m.autor = line.substr(pos_autor, pos - pos_autor);
        // Email
        size_t pos_genero = pos + 1;
        pos = line.find('|', pos_genero);
        m.genero = line.substr(pos_genero, pos-pos_genero);

        size_t pos_album = pos + 1;
        pos = line.find('|', pos_album );
        m.album = line.substr(pos_album, pos-pos_album );
      
        size_t pos_year= pos + 1;
        pos = line.find('|', pos_year);
        string year = line.substr(pos_year, pos-pos_year);
        m.year = stoi(year);

      // Se añaden a la lista los objetos que se recolectan del txt
      musica.push_back(m);
      // se imprimen los valore
      cout << "_________________________"<<endl;
      cout << "Nombre: "<< m.nombre<<endl;
      cout << "Autor: "<< m.autor<<endl;
      cout << "Genero: "<< m.genero<<endl;
      cout << "Album: "<<m.album<<endl;
      cout << "Año: "<<m.year<<endl;
      
    }
    f.close();
 }
}


//1. Funcion lista todos los autores presentes, ordenados alfabéticamente. Aqui, se recibe como parametros el vector de estructuras que será organizado
void autores_presentes_alfabeticamente(vector<javeMusic>& musica){
  // Se define la funcion sort en la cual se involucran dos iteradores que (.begin y .end) los cuales recorren la lista de a cuerdo a la funcion de comparación del tercer paramentro de este metodo. En este caso, como se debe organizar por orden alfabetido del autor, se llama a la funcion 'Autor'.
  sort(musica.begin(), musica.end(), Autor);
  cout<<" "<<endl;
  cout << "________________________________________" <<endl;
  cout<< "|        Autores (alfabeticamente)      |"<<endl;
  cout << "________________________________________" <<endl;
  // se intacia un for each para recorrer la estructura
  for(const auto& c : musica){ 
    //se imprime el nombre del autor en el orden correspondiente
  cout << "Autor: "<<c.autor<<endl;
    }
  cout << "________________________________________" <<endl;
}


//2.La funcion, dado un autor, lista todas sus canciones ordenadas alfabéticamente. Se recibe como omo parametros el vector de estructuras que será organizado y el nombre del Autor recibido por consola
void canciones_autor_alfabeticamente(vector<javeMusic>& musica, string nombreAutor){
  cout << "________________________________________" <<endl;
  cout<< "|  Canciones (autor/ alfabeticamente)   |"<<endl;
  cout << "________________________________________" <<endl;
  // Se define la funcion sort en la cual se involucran dos iteradores que (.begin y .end) los cuales recorren la lista de a cuerdo a la funcion de comparación del tercer paramentro de este metodo. En este caso, como se debe organizar por orden alfabetido del autor, se llama a la funcion 'Canciones'.
  sort(musica.begin(), musica.end(), Canciones);
  cout<<"Autor: "<<nombreAutor<<endl;
  
  for(const auto& c : musica){ 
     // se intacia un for each para recorrer la estructura
    if (c.autor == nombreAutor){
      // De acuerdo con el autor dado, se listan las canciones en orden alfabetico
      cout << "Canciones:"<<c.nombre<<endl;
    }
 }
}


//3. La funcion lista todos los álbumes presentes, ordenados cronológicamente.Aqui, se recibe como parametros el vector de estructuras que será organizado.
void cronologicamente(vector<javeMusic>& musica){
  // Se define la funcion sort en la cual se involucran dos iteradores que (.begin y .end) los cuales recorren la lista de a cuerdo a la funcion de comparación del tercer paramentro de este metodo. En este caso, como se debe organizar por orden alfabetido del autor, se llama a la funcion 'compararPorYear'.
   sort(musica.begin(), musica.end(), compararPorYear);
  cout << "____________________________________" <<endl;
  cout<< "|     Almbumes (cronologicamente)   |"<<endl;
  cout << "____________________________________" <<endl;
  // se intacia un for each para recorrer la estructura
  for(const auto& c : musica){ 
    // Se listan los albumes por orden cronologico
    cout <<"Albumes: " <<c.album<< " Año" << c.year <<endl;
    }
}


//"4. Esta funcion recive como parametro un álbum y listar todas las canciones que componen un álbum, ordenadas alfabéticamente por el nombre de la canción.Se recibe como omo parametros el vector de estructuras que será organizado y el nombre del Album recibido por consola.
void listado_de_album_alfabeticamente(vector<javeMusic>& musica, string nombreAlbum){
  cout << "_______________________________________________" <<endl;
  cout<< "|    Canciones (Alfabeticamente|Dado Album)     |"<<endl;
  cout << "_______________________________________________" <<endl;
  // Se define la funcion sort en la cual se involucran dos iteradores que (.begin y .end) los cuales recorren la lista de a cuerdo a la funcion de comparación del tercer paramentro de este metodo. En este caso, como se debe organizar por orden alfabetido del autor, se llama a la funcion 'Canciones'.
  sort(musica.begin(), musica.end(), Canciones);
 sort(musica.begin(), musica.end(), Canciones);
  cout << "Album: "<< nombreAlbum <<endl;
  // se intacia un for each para recorrer la estructura
  for(const auto& c : musica){ 
    if (c.album == nombreAlbum){
      // De acuerdo con el album dado, se listan las canciones en orden alfabetico
      cout << "Canciones: "<<c.nombre <<endl;
    }
 }
}


//5. Funcion Lista todas las canciones y su álbum, ordenadas alfabéticamente primero por el álbum y después por el nombre de la canción. 
void canciones_y_album_alfabeticamente(vector<javeMusic>& musica){
  cout << "____________________________________________" <<endl;
  cout<< "|     Canciones y almbum (alfabettico)      |"<<endl;
  cout << "___________________________________________" <<endl;
  // Se define la funcion sort en la cual se involucran dos iteradores que (.begin y .end) los cuales recorren la lista de a cuerdo a la funcion de comparación del tercer paramentro de este metodo. En este caso, como se debe organizar por orden alfabetido del autor, se llama a la funcion 'Canciones'.
  
  sort(musica.begin(), musica.end(), Album);
  // se intacia un for each para recorrer la estructura
  for(const auto& c : musica){ 
    // Se listan los albumes ordenados alfabeticamente
      cout << "Album: "<<c.album<<endl;
  }
  // se intacia un for each para recorrer la estructura
  for(const auto& c : musica){ 
    // Se listan los canciones ordenados alfabeticamente tras haber organizado los albumes
      cout << "Cancion: "<<c.nombre <<endl;
  }
}

// Funciones de comparacion
bool Autor(const javeMusic &a, const javeMusic& b){
    return a.autor < b.autor;
} // retorna true or false dependiendo de si el primer caracter de el nombre del autor que se compara con el resto de los valores del vector por medio del iterador es "mayor" o "menor".
bool Canciones(const javeMusic &a, const javeMusic& b){
    return a.nombre < b.nombre;
}// retorna true or false dependiendo de si el primer caracter de el nombre de la cancion que se compara con el resto de los valores del vector por medio del iterador es "mayor" o "menor".
bool compararPorYear(const javeMusic &a, const javeMusic& b) {
    return a.year < b.year;
}// retorna true or false dependiendo de si el año de produccion que se compara con el resto de los valores del vector por medio del iterador es "mayor" o "menor".
bool Album(const javeMusic &a, const javeMusic& b){
  if(a.album!=b.album)
    return a.album < b.album;
  return a.nombre<b.nombre;
}// retorna true or false dependiendo de si el primer caracter de el nombre del album que se compara con el resto de los valores del vector por medio del iterador es "mayor o menor". Esto en cado de que los nombres no sean iguales, ya que, en caso contrario, realizará el mismo proceso anterior pero con el atributo 'nombre' (que es el nombre de la cancion)

