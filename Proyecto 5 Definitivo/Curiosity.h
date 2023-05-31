#ifndef CURIOSITY_H
#define CURIOSITY_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <math.h>
#include <queue>


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

class Nodo {
public:
    string nombre;
    float cord_x;
    float cord_y;
    vector<class Arista*> aristas;
    bool visitado=false;

    Nodo(string nombre, float cord_x, float cord_y): nombre(nombre), cord_x(cord_x), cord_y(cord_y) {}
};

class Arista {
public:
    Nodo* nodo;
    float peso;

    Arista( Nodo* nodo, float peso):nodo(nodo), peso(peso) {}
};

class grafo {
public:
    vector<Nodo*> nodos;
    bool vacio() {
        return nodos.empty();
    }


    int cantVecinos (int elementos, float coeficienteDeConectividad){
        return elementos * coeficienteDeConectividad;
    }


    Nodo* agregarNodo(string nombre, float cord_x, float cord_y) {
        Nodo* nodo = new Nodo(nombre, cord_x, cord_y);
        nodos.push_back(nodo);
        return nodo;
    }

    void agregarArista(Nodo* nodo1, Nodo* nodo2, float coeficienteDeConectividad) {
        Arista* arista1 = new Arista(nodo2, peso(*nodo1,*nodo2));
        Arista* arista2 = new Arista(nodo1, peso(*nodo1,*nodo2));
        nodo1->aristas.push_back(arista1);
        nodo2->aristas.push_back(arista2);
    }

    float peso(Nodo nodo1, Nodo nodo2) {
        float x1 = nodo1.cord_x;
        float y1 = nodo1.cord_y;
        float x2 = nodo2.cord_x;
        float y2 = nodo2.cord_y;
        float dist = sqrt(pow(x2-x1,2) + pow(y2-y1,2));

        float minDistancia = 0;  // considerando que la mínima distancia puede ser 0
        float maxDistancia = sqrt(pow(100.0 - (-100), 2) + pow(100.0 - (-100), 2));  // máxima distancia posible en el mapa (-100 a 100 en ambas direcciones)

        return (dist - minDistancia) / (maxDistancia - minDistancia);
    }

void imprimirGrafo() {
    cout << "Lista de Adyacencia:\n";
    for (Nodo* nodo : nodos) {
        cout << "\nNodo: " << nodo->nombre << " [" << nodo->cord_x << ", " << nodo->cord_y << "]\n";
        cout << "Aristas:\n";
        for (Arista* arista : nodo->aristas) {
            cout << "\tHacia: " << arista->nodo->nombre << " [" << arista->nodo->cord_x << ", " << arista->nodo->cord_y << "], Peso: " << arista->peso << "\n";
        }
    }
    cout << "\n";
}

    vector<vector<float>> distancias;
    vector<vector<Nodo*>> ruta;

    // En la clase grafo
vector<Nodo*> rutaLargaDFS() {
    if (vacio()) {
        cout << "(No hay información) El mapa no ha sido generado todavía (con el comando crear_mapa)." << endl;
        return {};
    }

    Nodo *inicio = nullptr, *fin = nullptr;
    vector<Nodo*> rutaLarga; // 
    for (auto& nodo : nodos) {
        vector<Nodo*> rutaActual;
        rutaLargaDFSUtil(nodo, rutaActual);
        if (rutaActual.size() > rutaLarga.size()) {
            rutaLarga = rutaActual;
            inicio = rutaLarga.front();
            fin = rutaLarga.back();
        }
    }
    
    if (inicio != nullptr && fin != nullptr) {
        cout << "(Resultado exitoso) Los puntos de interés más alejados entre sí son " 
             << inicio->nombre << " y " << fin->nombre << ". "
             << "La ruta que los conecta tiene una longitud total de " << rutaLarga.size()
             << " y pasa por los siguientes elementos:\n";
        int count = 1;
        for (auto& nodo : rutaLarga) {
            cout << count << ". " << nodo->nombre  << " x: "<<nodo->cord_x << " y: "<<nodo->cord_y<< endl;
            count++;
        }
    }
    return rutaLarga;
}

void rutaLargaDFSUtil(Nodo* nodo, vector<Nodo*>& rutaActual) {
    nodo->visitado = true;
    rutaActual.push_back(nodo);

    for (auto& arista : nodo->aristas) {
        if (!arista->nodo->visitado) {
            rutaLargaDFSUtil(arista->nodo, rutaActual);
        }
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
    grafo *mapa;
    Curiosity();
    Curiosity(list<sComando> comandos, list<sElemento> elementos);
    list<sComando> getComandos();
    list<sElemento> getElementos();
    Quadtree* getQuadtree();
    grafo* getGrafo();
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
    int cantElementos();
    vector<int> Limites(list<sElemento> elementos);
    Quadtree* crearQuadtree();
    void insertarElementosQuadtree(Quadtree* quadtree,list<sElemento> elementos);
    list<sElemento> en_cuadrante(float x1, float y1,float x2,float y2);
    void crear_Mapa(float coeficienteDeConectividad);
    void crearConexiones(grafo& grafo,float coeficienteDeConectividad);
    void borrarAristas(vector<Nodo*>nodos,int cantVecinos);
    void ruta_mas_larga(grafo* g);
    grafo* getMapa();
};


void organizarAristasPesos(vector<Nodo*>&nodos);


#endif //CURIOSITY_H
