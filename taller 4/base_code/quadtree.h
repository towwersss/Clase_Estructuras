#include <iostream>
using namespace std;
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#ifndef quadtree_h
#define quadtree_h

class Color{
    public:
    int color;
    Color *hijos[4];
    Color(int color){
        this->color = color;
        for(int i = 0; i < 4; i++){
            hijos[i] = NULL;
        }
    }
};

class Quadtree{
    public:
    int tamano[2]={0,0};
    Color *raiz = NULL;
     Quadtree() {};

public:
   vector<Color> leerArchivoQt(string nombre_archivo) {
        ifstream archivo(nombre_archivo);

        if(archivo.is_open()) {
            vector<Color> colores;

            // Leer tamaño de la imagen
            archivo >> tamano[0] >> tamano[1];

            // Leer números y guardarlos en colores
            int numero;
            while (archivo >> numero) {
                string numeroStr = to_string(numero);
                for (char digitChar : numeroStr) {
                    int digit = digitChar - '0';
                    Color nuevoColor(digit);
                    colores.push_back(nuevoColor);
                }
            }

            cout << "Tamaño de la imagen: " << tamano[0] << " " << tamano[1] << endl;
            cout << "Color: " << endl;
            
            for (const auto& color : colores) {
                cout <<color.color << " ";
            }
            cout << endl;
            this->tamano[0] = tamano[0];
            this->tamano[1] = tamano[1];
            return colores;
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo." << endl;
        }

        
    }

void insertarColores(vector<Color> colores){
    this->raiz = insertarColoresAux(colores, 0, colores.size());
}

Color* insertarColoresAux(vector<Color>& colores, int inicio, int fin){
    if(inicio >= fin){
        return NULL;
    }

    Color* nodo = new Color(colores[inicio].color);
    if(nodo->color == 2){
        int tamano = (fin - inicio - 1) / 4;
        for(int i = 0; i < 4; i++){
            nodo->hijos[i] = insertarColoresAux(colores, inicio + 1 + i*tamano, inicio + 1 + (i+1)*tamano);
        }
    }

    return nodo;
}

void imprimirPreorden(Color* nodo){
    if(nodo == NULL){
        return;
    }
    // Recorrer los hijos del nodo actual
    for(int i = 0; i < 4; i++){
        imprimirPreorden(nodo->hijos[i]);
    }
}
void DecodeQuadTree(unsigned short** image,istream& in,unsigned int w0, unsigned int h0,unsigned int w1, unsigned int h1
  )
{
  char val;
  in >> val;
  if( val != '2' )
  {
    for( unsigned int h = h0; h < h1; ++h )
      for( unsigned int w = w0; w < w1; ++w )
        image[ h ][ w ] = ( unsigned short )( val - '0' );
  }
  else
  {
    unsigned int hw = ( w1 + w0 ) >> 1;
    unsigned int hh = ( h1 + h0 ) >> 1;

    DecodeQuadTree( image, in, w0, h0, hw, hh );
    DecodeQuadTree( image, in, hw, h0, w1, hh );
    DecodeQuadTree( image, in, hw, hh, w1, h1     );
    DecodeQuadTree( image, in, w0, hh, hw, h1     );

  } // fi
}
void decodeImage(string nombre_archivo) {
    ifstream in(nombre_archivo);
    if (!in) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int w, h;
    in >> w >> h;

    unsigned short** image = new unsigned short*[h];
    for (int i = 0; i < h; i++) {
        image[i] = new unsigned short[w];
    }

    DecodeQuadTree(image, in, 0, 0, w, h);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < h; i++) {
        delete[] image[i];
    }
    delete[] image;

    in.close();
}

void escribirPBM(Color* nodo, ofstream& out, int w, int h){
    if(nodo == NULL){
        return;
    }
    out << nodo->color << " ";

    for(int i = 0; i < 4; i++){
        escribirPBM(nodo->hijos[i], out, w/2, h/2);
    }
}

void guardarEnPBM(Quadtree& qt){

    string nombre_archivo;
    cout << "Ingrese el nombre del archivo: " << endl;
    cin >> nombre_archivo;

    ofstream out(nombre_archivo);
    if (!out) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    out << "P1\n";
    cout << "Escribe un comentario sobre la imagen: ";
    string comentario;
    getline(cin, comentario);

    out << "# " << comentario << "\n";

    escribirPBM(qt.raiz, out, qt.tamano[0], qt.tamano[1]);

    out.close();
}



void quadtree(){
    bool continuar = true;
    while(continuar){
        string nombre_archivo;
        cout << "Ingrese el nombre del archivo: " << endl;
        cin >> nombre_archivo;

    Quadtree qt;
    vector<Color> colores = qt.leerArchivoQt(nombre_archivo);
    qt.insertarColores(colores);
    qt.imprimirPreorden(qt.raiz);
    qt.decodeImage(nombre_archivo);
    qt.guardarEnPBM(qt);
    cout << "Desea continuar? (y/n)" << endl;
    string opcion;
    cin >> opcion;
    if(opcion == "n"){
        continuar = false;
    }
    }
}
};

#endif /* quadtree_h */



