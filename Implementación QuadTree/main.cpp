#include <iostream>
using namespace std;

class Point{
int cord_x;
int cord_y;
};
// primero se crean los cuatro cuadrantes del QuadTree.
// simpre que un quad tree tiene algo va a ser una hoja. De lo conteario no lo es.

class Quadtree{
 // se declaran los puntos máximos de cuadrado mas grande
 bool empty = true;
 Point point;
 bool leaf=true; // 

 int min_x = 0;
 int max_x= 0;
 int min_y = 0;
 int max_y = 0;

 Quadtree *ul;
 Quadtree *dl;
 Quadtree *ur;
 Quadtree *dr;

void insert(const Point &p){
  
  }
void buscac()
};



int main() {
  std::cout << "Hello World!\n";
}