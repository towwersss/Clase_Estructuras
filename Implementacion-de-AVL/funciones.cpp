#include <iostream>
using namespace std;
#include "funciones.h"
#include <fstream>
#include <vector>

/*Altura: Longitud del camino mas largo hasta una hoja. Lo que permitirá conocer más adelante el factor de balance.

Su valor se actualiza gracias a funciones como:
- Eliminar
-Insertar
-Balacear
*/
    int  ArbolAVL::altura(NodoAVL* nodoAVL) {
        if (nodoAVL == NULL) {
            return 0;
        }
        else {
            return nodoAVL->altura;
        }
    }

    // El factor de equilibrio es la diferencia de las alturas. Si
    // factor = 0 -> perfectamente balanceado
    // factor = +1 -> tiene mas nodos a la derecha
    // factor = -1 -> tiene mas nodos a la izquierda
    // Si es mayor no es un arbol AVL
    int  ArbolAVL::factorEquilibrio(NodoAVL* nodoAVL) {
        if (nodoAVL == NULL) {
            return 0;
        }
        else {
            return altura(nodoAVL->izq) - altura(nodoAVL->der);
        }
    }

    // ROTACIONES SIMPLES 

    // Rotación a la izquierda en la que la hoja para a ser hija del nodo raiz y su padre pasa a ser hoja.
    NodoAVL*  ArbolAVL::rotacionIzquierda(NodoAVL* nodoAVL) {
        NodoAVL* nodoAVL1 = nodoAVL->der;
        NodoAVL* nodoAVL2 = nodoAVL1->izq;
        nodoAVL1->izq = nodoAVL;
        nodoAVL->der = nodoAVL2;
        nodoAVL->altura = 1 + max(altura(nodoAVL->izq), altura(nodoAVL->der));
        nodoAVL1->altura = 1 + max(altura(nodoAVL1->izq), altura(nodoAVL1->der));
        return nodoAVL1;
    }

    // Rotación a la derecha en la que la hoja para a ser hija del nodo raiz y su padre pasa a ser hoja.
    NodoAVL*  ArbolAVL::rotacionDerecha(NodoAVL* nodoAVL) {
        NodoAVL* nodoAVL1 = nodoAVL->izq;
        NodoAVL* nodoAVL2 = nodoAVL1->der;
        nodoAVL1->der = nodoAVL;
        nodoAVL->izq = nodoAVL2;
        nodoAVL->altura = 1 + max(altura(nodoAVL->izq), altura(nodoAVL->der));
        nodoAVL1->altura = 1 + max(altura(nodoAVL1->izq), altura(nodoAVL1->der));
        return nodoAVL1;
    }

    // ROTACIONES COMPUESTAS

    // Rotación izquierda-derecha (doble rotación)
    // Si un nodo está desequilibrado a la izquierda y su hijo tiene otro sentido y viceversa se debe hacer una rotacion compuesta.
    // 1. Rotación a la izquierda en la que la hoja para a ser hija del nodo raiz y su padre pasa a ser hoja.
   // 2. Rotacion en la derecha en la que el nodo raiz es quien inicialmente era hoja y sus hijos son los que inicialmente eran su padre y la raiz.
    NodoAVL*  ArbolAVL::rotacionIzqDer(NodoAVL* nodoAVL) {
    nodoAVL->izq = rotacionIzquierda(nodoAVL->izq);
    return rotacionDerecha(nodoAVL);
}
// Rotación derecha-izquierda (doble rotación)
// Se realiza el mismo proceso anterior considerando que la primera rotación es derecha y la segunda izquierda.
    NodoAVL*  ArbolAVL::rotacionDerIzq(NodoAVL* nodoAVL) {
    nodoAVL->der = rotacionDerecha(nodoAVL->der);
    return rotacionIzquierda(nodoAVL);
}
// Se encarga de verificar continuamente si el factor de balanceo está entre los límites correspondientes.
// Para así conocer si se debe hacer una rotación.
    NodoAVL*  ArbolAVL::balancear(NodoAVL* nodoAVL) {
    if (factorEquilibrio(nodoAVL) > 1) {
        if (factorEquilibrio(nodoAVL->izq) < 0) {
            nodoAVL->izq = rotacionIzquierda(nodoAVL->izq);
        }
        return rotacionDerecha(nodoAVL);
    }
    else if (factorEquilibrio(nodoAVL) < -1) {
        if (factorEquilibrio(nodoAVL->der) > 0) {
            nodoAVL->der = rotacionDerecha(nodoAVL->der);
        }
        return rotacionIzquierda(nodoAVL);
    }
    return nodoAVL;
}
// Método para insertar un valor en el árbol AVL.
    NodoAVL*  ArbolAVL::insertar(NodoAVL* nodoAVL, int valor) {
    // Insertar el valor como en un árbol BST.
    if (nodoAVL == NULL) {
        return new NodoAVL(valor);
    }
    if (valor < nodoAVL->valor) {
        nodoAVL->izq = insertar(nodoAVL->izq, valor);
    }
    else if (valor > nodoAVL->valor) {
        nodoAVL->der = insertar(nodoAVL->der, valor);
    }
    else {
        return nodoAVL; // El valor ya existe en el árbol.
    }

    // Actualizar la altura del nodo actual.
    nodoAVL->altura = 1 + max(altura(nodoAVL->izq), altura(nodoAVL->der));

    // Balancear el árbol AVL.
    return balancear(nodoAVL);
}
// Método para eliminar un valor del árbol AVL.
    NodoAVL*  ArbolAVL::eliminar(NodoAVL* nodoAVL, int valor) {
    // Eliminar el valor como en un árbol BST.
    if (nodoAVL == NULL) {
        return nodoAVL;
    }
    if (valor < nodoAVL->valor) {
        nodoAVL->izq = eliminar(nodoAVL->izq, valor);
    }
    else if (valor > nodoAVL->valor) {
        nodoAVL->der = eliminar(nodoAVL->der, valor);
    }
    else {
        // El valor fue encontrado en el árbol, proceder a eliminarlo
      // Caso 1: nodo con 0 o 1 hijo.
        if ((nodoAVL->izq == NULL) || (nodoAVL->der == NULL)) {
            NodoAVL* temp = nodoAVL->izq ? nodoAVL->izq : nodoAVL->der;
            if (temp == NULL) {
                temp = nodoAVL;
                nodoAVL = NULL;
            }
            else {
                *nodoAVL = *temp;
            }
            delete temp;
        }
        // Caso 2: nodo con 2 hijos.
        else {
            NodoAVL* temp = nodoMinimo(nodoAVL->der);
            nodoAVL->valor = temp->valor;
            nodoAVL->der = eliminar(nodoAVL->der, temp->valor);
        }
    }

    // Si el árbol tenía solo un nodo, retornar.
    if (nodoAVL == NULL) {
        return nodoAVL;
    }

    // Actualizar la altura del nodo actual.
    nodoAVL->altura = 1 + max(altura(nodoAVL->izq), altura(nodoAVL->der));

    // Balancear el árbol AVL.
    return balancear(nodoAVL);
}
    NodoAVL*  ArbolAVL::nodoMinimo(NodoAVL* nodoAVL) {
    NodoAVL* actual = nodoAVL;

    while (actual->izq != NULL) {
        actual = actual->izq;
    }

    return actual;
    }

    int ArbolAVL::contar_nodos(ArbolAVL arbol) {
    return contar_nodos_aux(arbol.raiz);
}
    int ArbolAVL::contar_nodos_aux(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return 1 + contar_nodos_aux(nodo->izq) + contar_nodos_aux(nodo->der);
}

    vector <int> ArbolAVL::InOrdenAVL(NodoAVL* nodoAVL) {
      vector<int> vector;
    if (nodoAVL == nullptr) {
        return vector  ;
     }
    InOrdenAVL(nodoAVL->izq);
      vector.push_back(nodoAVL->valor);
    InOrdenAVL(nodoAVL->der);

      return vector;
}
  
    void ArbolAVL::insertar(int valor) {
        raiz = insertar(raiz, valor);
    }
    void ArbolAVL::eliminar(int valor) {
        raiz = eliminar(raiz, valor);
    }
    ArbolAVL& ArbolAVL::cargarArbol(string nombre_archivo, ArbolAVL &arbol){
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << std::endl;
        return arbol;
    }
    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.length() < 2) {
            continue; // Ignorar líneas vacías o incompletas
        }
        char operacion = linea[0];
        int valor = stoi(linea.substr(2));
        if (operacion == 'A') {
            arbol.insertar(valor);
        } else if (operacion == 'E') {
            arbol.eliminar(valor);
        } else {
            std::cout << "Operación no válida: " << operacion << std::endl;
        }
    }
    archivo.close(); 
      return arbol;
};
    float ArbolAVL::calcularMediana(vector<int> v){
      int size=v.size();
      float mediana;
      if(size%2==0){
        mediana=(v[size/2]+v[(size/2)+1])/2;
      }else{
        mediana=v[size/2];
      }
      return mediana;
    };
