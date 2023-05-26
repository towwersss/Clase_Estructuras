#include <iostream>
using namespace std;
#include <vector>
#ifndef funciones_h
#define funciones_h

class NodoAVL {
public:
    int valor;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(int valor) {
        this->valor = valor;
        izq = NULL;
        der = NULL;
        altura = 1;
    }
};

class ArbolAVL {
public:
    NodoAVL* raiz;
    ArbolAVL() {
    raiz = NULL;
}

    int altura(NodoAVL* nodoAVL);
    int factorEquilibrio(NodoAVL* nodoAVL);
    NodoAVL* rotacionIzquierda(NodoAVL* nodoAVL);
    NodoAVL* rotacionDerecha(NodoAVL* nodoAVL);
    NodoAVL* rotacionIzqDer(NodoAVL* nodoAVL);
    NodoAVL* rotacionDerIzq(NodoAVL* nodoAVL);
    NodoAVL* balancear(NodoAVL* nodoAVL);
    NodoAVL* buscar(NodoAVL* nodoAVL, int valor);
    NodoAVL* eliminar(NodoAVL* nodoAVL, int valor);
    void preOrden(NodoAVL* nodoAVL);
    void inOrden(NodoAVL* nodoAVL);
    void postOrden(NodoAVL* nodoAVL);
    void imprimirOrdenes(ArbolAVL& arbolito);
    NodoAVL* insertar(NodoAVL* nodoAVL, int valor);
    NodoAVL* nodoMinimo(NodoAVL* nodoAVL);
    void PostOrdenAVL(NodoAVL* nodoAVL);
    void PreOrdenAVL(NodoAVL* nodoAVL);
    vector <int> InOrdenAVL(NodoAVL* nodoAVL);
    void insertar(int valor);
    void eliminar(int valor);
    ArbolAVL& cargarArbol(string nombre_archivo, ArbolAVL &arbol);
    float calcularMediana(vector<int> v);
    int contar_nodos(ArbolAVL arbol);
    int contar_nodos_aux(NodoAVL* nodoAVL);

};

#endif

