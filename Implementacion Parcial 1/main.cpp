#include<iostream>

class Persona {
public:
    std::string nombre;
    Persona* padre;
    Persona* madre;

    Persona(std::string nombre) {
        this->nombre = nombre;
        this->padre = nullptr;
        this->madre = nullptr;
    }
};

// 1. Complementar la información del árbol con un ascendiente nuevo.
void agregarAscendiente(Persona* persona, Persona* padre, Persona* madre) {
    if (persona != nullptr) {
        persona->padre = padre;
        persona->madre = madre;
    }
}

// 2. Contar las generaciones de las cuales se tiene noticia.
int contarGeneraciones(Persona* persona) {
    if (persona == nullptr) {
        return 0;
    } else {
        return 1 + std::max(contarGeneraciones(persona->padre), contarGeneraciones(persona->madre));
    }
}

// 3. Comparar dos árboles genealógicos para saber si dos personas son hermanas.
bool compararArboles(Persona* p1, Persona* p2) {
    if (p1 == nullptr && p2 == nullptr)
        return true;

    if (p1 == nullptr || p2 == nullptr)
        return false;

    return p1->nombre == p2->nombre 
        && compararArboles(p1->padre, p2->padre)
        && compararArboles(p1->madre, p2->madre);
}

bool sonHermanos(Persona* p1, Persona* p2) {
    return compararArboles(p1->padre, p2->padre) 
        && compararArboles(p1->madre, p2->madre);
}

int main() {
    // Crear las personas
    Persona* juan = new Persona("Juan");
    Persona* jose = new Persona("Jose");
    Persona* maria = new Persona("Maria");
    Persona* pedro = new Persona("Pedro");

    // Agregar ascendientes
    agregarAscendiente(juan, jose, maria);
    agregarAscendiente(pedro, jose, maria);

    // Contar generaciones
    std::cout << "Generaciones de Juan: " << contarGeneraciones(juan) << std::endl;

    // Comparar si son hermanos
    std::cout << "¿Juan y Pedro son hermanos? " << (sonHermanos(juan, pedro) ? "Si" : "No") << std::endl;

    return 0;
}
