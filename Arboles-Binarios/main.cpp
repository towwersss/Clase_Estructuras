// retorna la rama mas larga de un arbol binario
#include <iostream>
#include <list>
using namespace std;
    class Nodo
    {
    public:
        char dato;
        Nodo *izq;
        Nodo *der;
        list<string> Daka;
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }
    int altura(Nodo *raiz)
    {
        if (raiz == NULL)
            return 0;
        return 1 + max(altura(raiz->izq), altura(raiz->der));
    }
    void insertar(Nodo *nodo, char a)
    {
        if(nodo==nullptr)
        {
            nodo->dato = a;
        }
        if(nodo->dato > a)
        {
            insertar(nodo->izq, a);
        }
        if(nodo->dato < a)
        {
            insertar(nodo, a);
        }
    }
    void imprimirInOrder(Nodo *nodo)
    {
        if (nodo == NULL)
            return;
        imprimirInOrder(nodo->izq);
        cout << nodo->dato << " ";
        imprimirInOrder(nodo->der);
    }
    };
    int main()
    {
        Nodo *nodo;
        nodo->insertar(nodo, 'a');
        nodo->insertar(nodo, 'c');
        nodo->insertar(nodo, 'b');
        nodo->insertar(nodo, 'h');
        nodo->insertar(nodo, 'e');
        nodo->imprimirInOrder(nodo);
    }