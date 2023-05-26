#include <iostream>
using namespace std;
#ifndef funciones_h
#define funciones_h
#include <vector>

struct javeMusic{
 string nombre;
 string autor;
 string genero;
 string album;
 int year;
};

void menu();

void leer_archivo(string nombreArchivo, vector<javeMusic>& musica);
//1.
void autores_presentes_alfabeticamente(vector<javeMusic>& musica);
//2.
void canciones_autor_alfabeticamente(vector<javeMusic>& musica, string nombreAutor);
//3.
void cronologicamente(vector<javeMusic>& musica);
//4.
void listado_de_album_alfabeticamente(vector<javeMusic>& musica, string nombreAlbum);
//5.
void canciones_y_album_alfabeticamente(vector<javeMusic>& musica);

//funciones comparadoras
bool Autor(const javeMusic &a, const javeMusic& b);
bool Canciones(const javeMusic &a, const javeMusic& b);
bool compararPorYear(const javeMusic &a, const javeMusic& b);
bool Album(const javeMusic &a, const javeMusic& b);

#endif