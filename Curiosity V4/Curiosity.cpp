#include "Curiosity.h"
#include "archivoFunciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <list>
#include <string.h>
#include <math.h>
#include <vector>
#ifndef M_Pi
#define M_Pi 3.14159265359  
#endif

using namespace std;
//CREAR LA IMPLEMENTACION DE LAS FUNCIONES DE CURIOSITY

Curiosity::Curiosity(){}

Curiosity::Curiosity(list<sComando> comandos, list<sElemento> elementos) {
    this->comandos = comandos;
    this->elementos = elementos;
    this->orientacion = 0;
    quadtree = nullptr;
}

list<sComando> Curiosity::getComandos() {
    return this->comandos;
}

list<sElemento> Curiosity::getElementos() {
    return this->elementos;
}

void Curiosity::agregarComando(sComando &comando) {
    this->comandos.push_back(comando);
}

void Curiosity::agregarElemento(sElemento &elemento){
    this->elementos.push_back(elemento);

}

void Curiosity::cargarComandos(string namefile) {
    int numLinea = 1;
    ifstream archivo;
    archivo.open(namefile);
    string linea;
    while (getline(archivo, linea)) { 
        sComando comando = cargarComando(linea, numLinea);
        if(!(comando != sComando())){
            comandos.clear();
        break; // ROMPE EL CICLO, YA QUE NO TIENE NADA MAS QUE LEER
        }
        else {
            this->agregarComando(comando);
        }
        numLinea++;
    }
    if(comandos.empty()==false){
    cout << "Comandos cargados: " << endl;
    imprimirComandos(this->comandos);
    }
    archivo.close();
}

void Curiosity::cargarElementos(string namefile){
    int numLinea = 1;
    ifstream archivo;
    archivo.open(namefile);
    string linea;
    while (getline(archivo, linea)) {
        sElemento elemento = cargarElemento(linea, numLinea);
        if(!(elemento != sElemento())){
            elementos.clear();
            break;
        }
        else{
        this->agregarElemento(elemento);
        }
        numLinea++;
    }
    if(elementos.empty()==false){
    cout << "Elementos cargados: " << endl;
    imprimirElementos(this->elementos);
    }
    archivo.close();
}

void Curiosity::guardar(string &namefile, string typefile){ 
    if(strstr(namefile.c_str(),".txt")==NULL){
        namefile += ".txt";
    }
    if(typefile=="comandos" && comandos.size()==0){
        cerr<<"Error: No hay comandos para guardar" << endl;
        return;
    }
    else if(typefile=="elementos" && elementos.size()==0){
        cerr<<"Error: No hay elementos para guardar" << endl;
        return;
    }
    fstream archivo;
    int opt=0;
    archivo.open(namefile, ios::in);
    if(archivo.fail()){
        cout << "El archivo no existe, desea crearlo? 1. Si 2. No" << endl;
        cin >> opt;
        if(opt==1){
            archivo.open(namefile, ios::out);
            archivo.close();
        }
        else{
            return;
        }
    }
    archivo.open(namefile, ios::out);
    archivo.seekg(0, std::ios::end);
    streampos tamano = archivo.tellg();
    archivo.close();
    if(tamano==0){
        archivo.open(namefile, ios::out);
        if(typefile == "comandos"){
            for(auto it = comandos.begin();it!=comandos.end();it++){
                if (it->movimiento != sComando::sMovimiento()){
                    archivo <<"0"<<"|"<< it->movimiento.tipoMovimiento << "|" << it->movimiento.magnitud << "|" << it->movimiento.unidadMedida;
                }
                else{
                    archivo<<"1"<<"|"<< it->analisis.tipoAnalisis << "|" << it->analisis.objeto << "|" << it->analisis.comentario;
                }
                if(it!=comandos.end()){
                    archivo << endl;
                }
            }
        }
        else if(typefile=="elementos"){
            for(auto it = elementos.begin();it!=elementos.end();it++){
                archivo <<it->tipoElemento << "|" << it->tamanio << "|" << it->unidadMedida << "|" << it->coorDx << "|" << it->coorDy<< endl;
            }  
        }
        archivo.close();
        cout<<"Archivo guardado con exito"<<endl;
    }
    else{
        cout << "Desea sobreescribir o reescribir el archivo? 1. Reescribir 2. Sobreescribir" << endl;
    cin >> opt;
    if(opt==1){
        archivo.open(namefile, ios::out);
        if(typefile == "comandos"){
            int i=0;
            for(auto it = comandos.begin();it!=comandos.end();it++){
                if (it->movimiento != sComando::sMovimiento()){
                    archivo <<"0"<<"|"<< it->movimiento.tipoMovimiento << "|" << it->movimiento.magnitud << "|" << it->movimiento.unidadMedida;
                }
                else{
                    archivo<<"1"<<"|"<< it->analisis.tipoAnalisis << "|" << it->analisis.objeto << "|" << it->analisis.comentario;
                }
                if(i<comandos.size()-1){
                    archivo << endl;
                    }
                i++;
            }
        }
        else if(typefile=="elementos"){
            if(elementos.size()==0){
                cerr<<"Error: No hay elementos para guardar";
                return;
            }
            for(auto it = elementos.begin();it!=elementos.end();it++){
                archivo <<it->tipoElemento << "|" << it->tamanio << "|" << it->unidadMedida << "|" << it->coorDx << "|" << it->coorDy<< endl;
            }  
        }
        archivo.close();
        cout<<"Archivo reescrito con exito"<<endl;
    }
    else if(opt==2){
        archivo.open(namefile, ios::app);
        if(typefile == "comandos"){
            for(auto it = comandos.begin();it!=comandos.end();it++){
                if (it->movimiento != sComando::sMovimiento()){
                archivo <<endl <<"0"<<"|"<< it->movimiento.tipoMovimiento << "|" << it->movimiento.magnitud << "|" << it->movimiento.unidadMedida;
            }
            else{
                archivo <<endl <<"1"<<"|"<< it->analisis.tipoAnalisis << "|" << it->analisis.objeto << "|" << it->analisis.comentario;
            }
            }
        }
        else if(typefile=="elementos"){
            for(auto it = elementos.begin();it!=elementos.end();it++){
                archivo << endl <<it->tipoElemento << "|" << it->tamanio << "|" << it->unidadMedida << "|" << it->coorDx << "|" << it->coorDy;
            }
        }
        archivo.close();
        cout<<"Archivo sobrescrito con exito"<<endl;
    }
    else{
        cerr<<"Error: Opcion no valida";
        return;
    }
    }
    
}



void Curiosity::setCoords(float cordX, float cordY) {
    this->coords[0] = cordX;
    this->coords[1] = cordY;
}

void Curiosity::simularComandos(){
    for(auto it = this->comandos.begin();it!=this->comandos.end();it++){
        if(it->movimiento != sComando::sMovimiento()){
            if(it->movimiento.tipoMovimiento == "avanzar"){
                if(it->movimiento.unidadMedida == "metros"){
                    this->coords[0] += it->movimiento.magnitud * cos(this->orientacion*M_Pi/180);
                    this->coords[0] = round(this->coords[0] * 100) / 100;
                    this->coords[1] += it->movimiento.magnitud * sin(this->orientacion*M_Pi/180);
                    this->coords[1] = round(this->coords[1] * 100) / 100;
                cout << "Coordenadas actuales: " << this->coords[0] << " " << this->coords[1] << endl;
                }
            }
            else if(it->movimiento.tipoMovimiento == "girar"){
                if(it->movimiento.unidadMedida == "grados"){
                    this->orientacion += it->movimiento.magnitud;
                        if(orientacion>360){
                            orientacion = orientacion - 360;
                        }
                        else if(orientacion<0){
                            orientacion = orientacion + 360;
                        }
                    this->orientacion = round(this->orientacion * 100) / 100;
                    cout << "Orientacion actual: " << this->orientacion << endl;
                }
            }
        }
        if(it->analisis != sComando::sAnalisis()){
            if(it->analisis.tipoAnalisis == "tomar foto"){
                if(it->analisis.objeto == "roca"){
                    for(auto it2 = this->elementos.begin();it2!=this->elementos.end();it2++){
                        if(it2->coorDx == this->coords[0] && it2->coorDy == this->coords[1]){
                            cout << "Elemento encontrado: " << it2->tipoElemento << " " << it2->tamanio << " " << it2->unidadMedida << endl;
                        }
                    }
                }
            }
            if(it->analisis.tipoAnalisis == "perforar"){
                if(it->analisis.objeto == "roca"){
                    for(auto it2 = this->elementos.begin();it2!=this->elementos.end();it2++){
                        if(it2->coorDx == this->coords[0] && it2->coorDy == this->coords[1]){
                            cout << "Elemento encontrado: " << it2->tipoElemento << " " << it2->tamanio << " " << it2->unidadMedida << endl;
                        }
                    }
                }
            }
        }
    }
}


vector<int> Curiosity::Limites(list<sElemento> elementos) {
    vector<int> limites = {INT_MIN, INT_MIN, INT_MAX, INT_MAX};

    for (auto it = elementos.begin(); it != elementos.end(); it++) {
        if (it->coorDx < limites[0]) {
            limites[0] = it->coorDx;
        }
        if (it->coorDy < limites[1]) {
            limites[1] = it->coorDy;
        }
        if (it->coorDx > limites[2]) {
            limites[2] = it->coorDx;
        }
        if (it->coorDy > limites[3]) {
            limites[3] = it->coorDy;
        }
    }
    return limites;
}


Quadtree* Curiosity::crearQuadtree() {
        vector<int> limites = Limites(elementos);
        return new Quadtree(limites[2] + 10, limites[0] - 10, limites[3] + 10, limites[1] - 10);
    }


void Curiosity::insertarElementosQuadtree(Quadtree* quadtree, list<sElemento> elementos) {
    for (const auto& elemento : elementos) {
        Punto punto;
        punto.cord_x = elemento.coorDx;
        punto.cord_y = elemento.coorDy;
        punto.tamanio = elemento.tamanio;
        quadtree->insertar(punto);
        cout << "Elemento insertado: " << elemento.tipoElemento << " " << elemento.tamanio << " " << elemento.unidadMedida << "coord X " << punto.cord_x << " " << "coord Y " << punto.cord_y <<  endl;
    }
}

Quadtree* Curiosity::getQuadtree(){
    return this->quadtree;
}


void Curiosity::ubicarElementos(){ 
    this->quadtree = crearQuadtree();
    insertarElementosQuadtree(quadtree, elementos);
    cout << "Quadtree creado" << endl;
    cout << "Preorden: " << endl;
    quadtree->preorden(quadtree);
}




list<sElemento> Curiosity::en_cuadrante(float x1, float x2, float y1, float y2) {
    list<sElemento> elementos_en_cuadrante;
    int i=0;
    if(this->quadtree->vacio){
        cout<<"No hay elementos cargados en memoria"<<endl;
        return elementos_en_cuadrante;
    }
    Punto p;
    for (auto it = elementos.begin(); it != elementos.end(); it++) {
        p.cord_x = it->coorDx;
        p.cord_y = it->coorDy;
        p.tamanio = it->tamanio;
        if (quadtree->buscar(p, x1, x2, y1, y2)) {
            elementos_en_cuadrante.push_back(*it);
            cout << it->tipoElemento << " " << it->tamanio << " " << it->unidadMedida << endl;
            i++;
        }
    }
    if(i==0){
        cout<<"No hay elementos en el cuadrante"<<endl;
    }
    return elementos_en_cuadrante;
}

