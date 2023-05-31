#include <iostream>
#include "Curiosity.h"
#include "archivoFunciones.h"

int main() {
    setlocale(LC_ALL, "es_US.UTF-8");
    sComando c;
    Curiosity curiosity=Curiosity();
    do{
        menu(curiosity);
    }
    while(true);
    return 0;
}
