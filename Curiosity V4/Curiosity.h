#ifndef CURIOSITY_H
#define CURIOSITY_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>

using namespace std;


struct sComando {
    struct sMovimiento {
        string tipoMovimiento;
        float magnitud;
        string unidadMedida;
        bool operator != (const sMovimiento &movimiento) const {
            return (tipoMovimiento != movimiento.tipoMovimiento) || (magnitud != movimiento.magnitud) || (unidadMedida != movimiento.unidadMedida);
        }
    };
    sMovimiento movimiento = sMovimiento();
    struct sAnalisis {
        string tipoAnalisis;
        string objeto;
        string comentario;
        bool operator != (const sAnalisis &analisis) const {
            return (tipoAnalisis != analisis.tipoAnalisis) || (objeto != analisis.objeto) || (comentario != analisis.comentario);
        }
    };
    sAnalisis analisis = sAnalisis();
    bool operator != (const sComando &comando) const {
        return (movimiento != comando.movimiento) || (analisis != comando.analisis);
    }
};

struct sElemento {
    string tipoElemento;
    float tamanio;
    string unidadMedida;
    float coorDx;
    float coorDy;
    bool operator != (const sElemento &elemento) const {
        return (tipoElemento != elemento.tipoElemento) || (tamanio != elemento.tamanio) || (unidadMedida != elemento.unidadMedida) || (coorDx != elemento.coorDx) || (coorDy != elemento.coorDy);
    }
};


class Punto {
public:
    float cord_x;
    float cord_y;
    float tamanio;
    bool operator != (const Punto &punto) const {
        return (cord_x != punto.cord_x) || (cord_y != punto.cord_y) || (tamanio != punto.tamanio);
    }
    bool operator < (const Punto &punto) const {
        return (cord_x < punto.cord_x) || (cord_y < punto.cord_y) || (tamanio < punto.tamanio);
    }
};

class Quadtree {
private:
    set<Punto> puntos; 
    Punto punto;
    bool hoja = true;

    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;

    Quadtree *ul;
    Quadtree *dl;
    Quadtree *ur;
    Quadtree *dr;

public:

    bool vacio = true;

    Quadtree() = default;
    Quadtree(int min_x, int max_x, int min_y, int max_y){
        this->min_x = min_x;
        this->max_x = max_x;
        this->min_y = min_y;
        this->max_y = max_y;
        ul = nullptr;
        dl = nullptr;
        ur = nullptr;
        dr = nullptr;
    }


void dividir() {
        int mid_x = (min_x + max_x) / 2;
        int mid_y = (min_y + max_y) / 2;

        ul = new Quadtree(min_x, mid_x, mid_y + 1, max_y);
        dl = new Quadtree(min_x, mid_x, min_y, mid_y);
        ur = new Quadtree(mid_x + 1, max_x, mid_y + 1, max_y);
        dr = new Quadtree(mid_x + 1, max_x, min_y, mid_y);

        hoja = false;
    }

Quadtree* cuadrante(const Punto& p) {
        int mid_x = (min_x + max_x) / 2;
        int mid_y = (min_y + max_y) / 2;

        if (p.cord_x <= mid_x && p.cord_y > mid_y) return ul;
        if (p.cord_x <= mid_x && p.cord_y <= mid_y) return dl;
        if (p.cord_x > mid_x && p.cord_y > mid_y) return ur;
        return dr;
    }


    void insertar(const Punto& p) {

        if (!en_rango(p)) {
            return;
        }

        // Verificar si el punto ya está en el árbol
        if (vacio) {
            punto = p;
            vacio = false;
            puntos.insert(p); // Agregar el nuevo punto a la lista de puntos
            return;
        }

        if (hoja) {
            Punto punto_anterior = punto;
            dividir();
            cuadrante(punto_anterior)->insertar(punto_anterior);
        }

        // Verificar si el punto ya está en el árbol
        if (puntos.count(p) == 0) {
            puntos.insert(p); // Agregar el nuevo punto a la lista de puntos
            cuadrante(p)->insertar(p);
        }
    }


int contarPuntos(){
    if(vacio)
        return 0;
    if(hoja)
        return 1;
    return ul->contarPuntos() + dl->contarPuntos() + ur->contarPuntos() + dr->contarPuntos();
}

    bool en_rango(const Punto& p) const {
        return p.cord_x >= min_x && p.cord_x <= max_x && p.cord_y >= min_y && p.cord_y <= max_y;
        }


bool buscar(Punto p,float x1,float x2,float y1,float y2){
    if(vacio)
        return false;
    if(hoja)
        return p.cord_x >= x1 && p.cord_x <= x2 && p.cord_y >= y1 && p.cord_y <= y2;
    return ul->buscar(p,x1,x2,y1,y2) || dl->buscar(p,x1,x2,y1,y2) || ur->buscar(p,x1,x2,y1,y2) || dr->buscar(p,x1,x2,y1,y2);
}


void preorden(Quadtree *arbol) {
    if (arbol != nullptr && !arbol->vacio) {
        if (arbol->hoja) {
            cout << arbol->punto.cord_x << " " << arbol->punto.cord_y << endl;
        }
        preorden(arbol->ul);
        preorden(arbol->dl);
        preorden(arbol->ur);
        preorden(arbol->dr);
    }
}

};


class Curiosity {
private:
    list<sComando> comandos;
    list<sElemento> elementos;
    Quadtree *quadtree;

    float orientacion=0;
    //X es la posicion 0 y Y es la posicion 1
    float coords[2] = {1,1};

public:
    Curiosity();
    Curiosity(list<sComando> comandos, list<sElemento> elementos);
    list<sComando> getComandos();
    list<sElemento> getElementos();
    Quadtree* getQuadtree();
    void cargarComandos(string namefile);
    void agregarComando(sComando &comando);
    void cargarElementos(string namefile);
    void agregarElemento(sElemento &elemento);
    void actualizarOrientacion(float nuevaorientacion);
    void simularComandos();
    void setComandos(list<sComando> comandos);
    void setElementos(list<sElemento> elementos);
    void setOrientacion(float orientacion);
    void setCoords(float cordX, float cordY);
    void guardar(string &namefile, string typefile);
    void insertarElementos();
    void ubicarElementos();
    vector<int> Limites(list<sElemento> elementos);
    Quadtree* crearQuadtree();
    void insertarElementosQuadtree(Quadtree* quadtree,list<sElemento> elementos);
    list<sElemento> en_cuadrante(float x1, float y1,float x2,float y2);
};



#endif //CURIOSITY_H

