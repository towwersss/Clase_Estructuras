#include "Curiosity.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <algorithm>

using namespace std;

sComando cargarComando(string linea, int &lineaActual){
    sComando comando;
    char* linea2= new char[linea.length()+1];
    strcpy(linea2, linea.c_str());
    int tipo= atoi(strtok(linea2, "|"));
    if(tipo !=0 && tipo !=1){
        cerr<<"Error en el tipo de comando"<<endl;
        return sComando();
    }
    if(tipo == 0){
        sComando::sMovimiento movimiento;
        char* token= strtok(NULL, "|");
        if(strcmp(token,"avanzar")!=0 && strcmp(token,"girar")!=0){
            cerr<<"Error en el tipo de movimiento en la linea: "<<lineaActual <<endl;
            return sComando();
        }
        movimiento.tipoMovimiento= token;
        token= strtok(NULL, "|");
        if(atof(token)==0){
            cerr<<"Error en la magnitud del movimiento en la linea "<<lineaActual <<endl;
        }
        movimiento.magnitud= atof(token);
        token= strtok(NULL, "|");
        if(strcmp(token,"metros")!=0 && strcmp(token,"grados")!=0){
            cerr<<"Error en la unidad de medida del movimiento en la linea "<<lineaActual <<endl;
            return sComando();
        }
        movimiento.unidadMedida = token;
        comando.movimiento = movimiento;
    }
    else if(tipo==1){
        sComando::sAnalisis analisis;
        char* token= strtok(NULL, "|");
        if(strcmp(token,"fotografiar")!=0 && strcmp(token,"perforar")!=0 && strcmp(token,"composicion")!=0){
            cerr<<"Error en el tipo de analisis en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.tipoAnalisis= token;
        token= strtok(NULL, "|");
        if(strcmp(token,"roca")!=0 && strcmp(token,"arena")!=0 && strcmp(token,"monticulo")!=0){
            cerr<<"Error en el objeto a analizar en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.objeto= token;
        token= strtok(NULL, "|");
        if(sizeof(token)==0){
            cerr<<"Error en el comentario del analisis en la linea "<<lineaActual <<endl;
            return sComando();
        }
        analisis.comentario= token;
        comando.analisis= analisis;
    }
    else{
        cerr<<"Error en el tipo de comando"<<endl;
        return sComando();
    }
    return comando;
}

sElemento cargarElemento(string linea, int &lineaActual){
    
    sElemento elemento;
    char* linea2= new char[linea.length()+1];
    strcpy(linea2, linea.c_str());
    char* token= strtok(linea2, "|");
    if(strcmp(token,"roca")!=0 && strcmp(token,"duna")!=0 && strcmp(token,"monticulo")!=0 && strcmp(token,"crater")!=0){
        cerr<<"Error en el tipo de elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.tipoElemento=token;
    token = strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en el tamaño del elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.tamanio=atof(token);
    token= strtok(NULL, "|");
    if(strcmp(token,"metros")!=0){
        cerr<<"Error en la unidad de medida del elemento en la linea: "<< lineaActual <<endl;
        return sElemento();
    }
    elemento.unidadMedida=token; 
    token= strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en la coordenada X del elemento en la linea: "<<lineaActual <<endl;
        return sElemento();
    }
    elemento.coorDx=atof(token);
    token= strtok(NULL, "|");
    if(atof(token)==0){
        cerr<<"Error en la coordenada Y del elemento en la linea: " <<lineaActual <<endl;
        return sElemento();
    }
    elemento.coorDy=atof(token);

    return elemento;
}


void imprimirComandos(list <sComando> comandos){
    for(auto it = comandos.begin(); it!= comandos.end(); it++){
        if(it->movimiento != sComando::sMovimiento()){
        cout<<it->movimiento.tipoMovimiento << ',';
        cout<<it->movimiento.magnitud << ',';
        cout<<it->movimiento.unidadMedida << endl;
        continue;
        }
        else{
        cout << it->analisis.tipoAnalisis <<',';
        cout << it->analisis.objeto << ',';
        cout << it->analisis.comentario <<endl;
        continue;
        }
    }
}


void imprimirElementos(list <sElemento> elementos){
    for(auto it=elementos.begin();it!=elementos.end();it++){
        cout<<"Elemento: "<<it->tipoElemento<<endl;
        cout<<"Tamaño: " <<it->tamanio << " "<<it->unidadMedida<<endl;
        cout<<"Coordenada X: "<<it->coorDx<<endl;
        cout<<"Coordenada Y: "<<it->coorDy<<endl;
    }
}


bool openInFile(string &n_a){
    ifstream archivo;
    if(strstr(n_a.c_str(),".txt")==NULL){
        n_a += ".txt";
    }
    archivo.open(n_a, ios::in);
    archivo.seekg(0, std::ios::end);
    streampos tamano = archivo.tellg();
    if(archivo.fail()){
        cerr<<"Error, '" <<n_a <<"' no se encuentra o no puede leerse" <<endl;
        return false;
    }
    else if(tamano == 0){
        cerr<<"Error, '" <<n_a <<"' esta vacio."<<endl;
        return false;
    }
    else{
        return true;
    }
}




void helpmenu(){
    cout<<"Lista de comandos: "<<endl;
        cout<<"cargar_elementos: Carga en memoria los datos de los elementos contenidos en el archivo"
            <<"identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar"
            <<"la información de los elementos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado"
            <<"otros archivos de puntos de interés (usando el comando cargar_elementos), la información debe"
            <<"sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes "
            <<"archivos.\n\n";
        cout<<"agregar_movimiento: Agrega el comando de movimiento descrito a la lista de comandos del robot “Curios-"
            <<"ity”. El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del"
            <<"movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados"
            <<"que debe girar. La unidad de medida corresponde a la convención con la que se mide la magnitud del"
            <<"movimiento (centimetros, metros, grados, ...). Si no se envía la información completa y adecuada"
            <<"del comando de movimiento, éste no puede agregarse a la lista de los comandos que se enviarán al robot "
            <<"desde la tierra.\n\n";
        cout<<"agregar_analisis: Agrega el comando de análisis descrito a la lista de comandos del robot “Curiosity”. El "
            <<"análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del "
            <<"elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar "
            <<"más información sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples "
            <<"(ejemplo: ’roca_cuadrante_32’). Si no se envía la información completa y adecuada del comando de "
            <<"análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra.\n\n";
        cout<<"agregar_elemento: Agrega el componente o elemento descrito a la lista de puntos de interés del robot “Cu-"
            <<"riosity”. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño "
            <<"es un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa "
            <<"este valor con la convención que se usó para su medición (centimetros, metros, ...). Finalmente, las "
            <<"coordenadas x y y corresponden a números reales que permiten conocer la ubicación del elemento en "
            <<"el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la información "
            <<"completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés que se enviarán "
            <<"al robot desde la tierra.\n\n";
        cout<<"guardar: Guarda en el archivo con el nombre proporcionado por el usuario la información solicitada de acuerdo al tipo de "
            <<"archivo: comandos almacena en el archivo la información de comandos de movimiento y de análisis que "
            <<"debe ejecutar el robot, elementos almacena en el archivo la información de los componentes o puntos "
            <<"de interés conocidos en el suelo marciano.\n\n";
        cout<<"simular_comandos: Permite simular el resultado de los comandos de movimiento que se enviarán al robot "
            <<"“Curiosity” desde la Tierra, facilitando asi la validación de la nueva posición en la que podría ubicarse. "
            <<"Para ejecutarse adecuadamente, requiere conocer la posición actual (coordenadas x y y) del vehículo. "
            <<"Hay que tener en cuenta que sólo los comandos de movimiento son necesarios, no los de análisis.\n\n";
        cout<<"ubicar_elementos: El comando debe utilizar la información de puntos de interés almacenada en memoria "
            <<"para ubicarlos en una estructura de datos jerárquica adecuada, que permita luego realizar consultas "
            <<"geográficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe "
            <<"generarse un mensaje de error, pero deben terminarse de procesar todos los elementos almacenados en "
            <<"memoria\n\n";
        cout<<"en_cuadrante:Permite utilizar la estructura creada con el comando anterior para retornar una lista de "
            <<"los componentes o elementos que están dentro del cuadrante geográfico descrito por los límites de co-"
            <<"ordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar "
            <<"la búsqueda por cuadrantes. Los límites de coordenadas deben garantizar que coordX1 <coordX2 y "
            <<"coordY1 <coordY2 \n\n";
        cout<<"crear_mapa: El comando debe utilizar la información de puntos de interés almacenada en memoria para "
            <<"ubicarlos en una estructura no lineal y conectarlos entre sí teniendo en cuenta el coeficiente de conec- "
            <<"tividad dado. El objetivo es que cada elemento esté conectado a los demás elementos más cercanos a "
            <<"el, midiendo la cercanía a través de la distancia euclidiana entre los elementos. Esta distancia euclidiana "
            <<"también se utiliza como el peso o etiqueta de la conexión entre los elementos. Con el coeficiente de "
            <<"conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el "
            <<"total de elementos que se ubicarán en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente "
            <<"de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14).\n\n";
        cout<<"ruta_mas_larga: Con el mapa ya creado, el comando permite identificar los dos componentes más alejados "
            <<"entre sí de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los ele- "
            <<"mentos más alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que "
            <<"estén a mayor distancia euclidiana entre sí. Al encontrar esa ruta más larga dentro del mapa, el comando "
            <<"imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de "
            <<"elementos que hay que seguir para ir del elemento origen al elemento destino.\n";
}

char* toLowerCase(char* str) {
    int i = 0;
    while (str[i]) {   // Recorrer la cadena hasta llegar al carácter nulo '\0'
        str[i] = tolower(str[i]);   // Convertir cada letra a minúscula
        i++;
    }
    return str;
}

void menu(Curiosity &Curiosity){
string archivo;
bool of;
list<char*> entrada;
    char* s = new char[200]; // Asignar memoria para s
    do{
    cout <<"$";
    fflush(stdin); // Ignorar el salto de línea
    cin.getline(s, 200, '\n');
    char* token = strtok(s, " ");
    while (token != NULL) {         
        entrada.push_back(token);    
        token = strtok(NULL, " ");           
    }
    }
    while(entrada.empty());
    list<char*>::iterator it = entrada.begin();
    char* comando = *it;
    comando = toLowerCase(comando);
    if(strcmp(comando,"help")==0){
        helpmenu();        
    }
    else if(strcmp(*it,"cargar_comandos") == 0){
        int i = 0;
        for(it = entrada.begin(); it != entrada.end(); it++){
            i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            archivo=entrada.back();
            of=openInFile(archivo);
            if(of==true){
            Curiosity.cargarComandos(archivo);
            }
            return;
        }
    }
    else if(strcmp(*it,"cargar_elementos") == 0){
        int i = 0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            archivo=entrada.back();
            of=openInFile(archivo);
            if(of==true){
            Curiosity.cargarElementos(archivo);
            }
            return;
        }
    }
    else if(strcmp(*it,"agregar_movimiento")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 4){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 4){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            auto it = entrada.begin();
            it++;
            sComando comando;
            sComando::sMovimiento movimiento;
            if(strcmp(*it,"avanzar")==0 ||strcmp(*it,"girar")==0){
                movimiento.tipoMovimiento = *it;
            }
            else{
                cerr << "Error: el tipo de movimiento no es válido\n";
                return;
            }
            it++;
            if(atof(*it)!=0){
                movimiento.magnitud = atof(*it);
            }
            else{
                cerr << "Error: la magnitud no es válida\n";
                return;
            }
            it++;
            if(strcmp(*it,"metros")==0 ||strcmp(*it,"grados")==0){
                movimiento.unidadMedida = *it;
            }
            else{
                cerr << "Error: la unidad de medida no es válida\n";
                return;
            }
            comando.movimiento = movimiento;
            Curiosity.agregarComando(comando);  
            cout << "Movimiento agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"agregar_analisis")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 4){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 4){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }    
        else {
            auto it = entrada.begin();
            it++;
            sComando comando;
            sComando::sAnalisis analisis;
            if(strcmp(*it,"fotografiar")==0 ||strcmp(*it,"perforar")==0 || strcmp(*it,"composicion")==0){
                analisis.tipoAnalisis = *it;
            }
            else{
                cerr << "Error: el tipo de análisis no es válido\n";
                return;
            }
            it++;
            if(strcmp(*it,"roca")==0 ||strcmp(*it,"arena")==0 || strcmp(*it,"monticulo")==0){
                analisis.objeto = *it;
            }
            else{
                cerr << "Error: el tipo de análisis no es válido\n";
                return;
            }
            it++;
            if(sizeof(*it)>0){
                analisis.comentario = *it;
            }
            else{
                cerr << "Error: el comentario no es válido\n";
                return;
            }
            comando.analisis = analisis;
            Curiosity.agregarComando(comando);
            cout << "Análisis agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"agregar_elemento")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 6){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 6){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            auto it = entrada.begin();
            it++;
            sElemento elemento;
            if(strcmp(*it,"roca")==0 || strcmp(*it,"duna")==0 || strcmp(*it,"monticulo")==0 || strcmp(*it,"crater")==0){
                elemento.tipoElemento = *it;
            }
            else{
                cerr << "Error: el tipo de elemento no es válido\n";
                return;
            }
            it++;
            if(atof(*it)>0){
                elemento.tamanio = atof(*it);
            }
            else{
                cerr << "Error: el tamaño no es válido\n";
                return;
            }
            it++;
            if(strcmp(*it,"metros")==0){
                elemento.unidadMedida = *it;
            }
            else{
                cerr << "Error: la unidad de medida no es válida\n";
                return;
            }
            it++;
            if(atof(*it) != 0){
                elemento.coorDx = atof(*it);
            }
            else{
                cerr << "Error: la posición en X no es válida\n";
                return;
            }
            it++;
            if(atof(*it) != 0){
                elemento.coorDy = atof(*it);
            }
            else{
                cerr << "Error: la posición en Y no es válida\n";
                return;
            }
            Curiosity.agregarElemento(elemento);
            cout << "Elemento agregado\n";
            return;
        }    
    }
    else if(strcmp(*it,"guardar")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            string t_a;
            archivo=entrada.back();
            list<char*>::iterator it = entrada.begin();
            advance(it, 1);
            t_a=*it;
            Curiosity.guardar(archivo,t_a);
            return;
        }    
    }
    else if(strcmp(*it,"simular_comandos")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else if(Curiosity.getComandos().size()==0){
            cerr << "Error: no hay comandos para simular\n";
            return;
        }
        else {
            auto it = entrada.begin();
            advance(it, 1);
            float x= atof(*it);
            advance(it,1);
            float y = atof(*it);
            Curiosity.setCoords(x,y);
            Curiosity.simularComandos();
            return;
        }    
    }
    else if(strcmp(*it,"ubicar_elementos")==0){
        
        if(Curiosity.getElementos().size()==0){
            cerr << "Error: no hay elementos para ubicar\n";
            return;
        }
        else {
            Curiosity.ubicarElementos();
            return;
        }
    }
    else if(strcmp(*it,"en_cuadrante")==0){
        int i=0;

        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 5){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 5){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else if(Curiosity.getQuadtree() == nullptr){
            cerr << "No se puede ubicar elementos, el Quadtree esta vacio\n";
            return;
        }

        else {
            auto it = entrada.begin();
            advance(it, 1);
            float x1= atof(*it);
            advance(it,1);
            float x2 = atof(*it);
            advance(it,1);
            float y1 = atof(*it);
            advance(it,1);
            float y2 = atof(*it);
            Curiosity.en_cuadrante(x1,x2,y1,y2);   
            return;
        }    
    }
    else if(strcmp(*it,"crear_mapa")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 2){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 2){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            cout<<"Descripción de la función:\nEl comando debe utilizar la información de puntos de interés almacenada en memoria para"
            <<"ubicarlos en una estructura no lineal y conectarlos entre sí teniendo en cuenta el coeficiente de conec-"
            <<"tividad dado. El objetivo es que cada elemento esté conectado a los demás elementos más cercanos a"
            <<"el, midiendo la cercanía a través de la distancia euclidiana entre los elementos. Esta distancia euclidiana"
            <<"también se utiliza como el peso o etiqueta de la conexión entre los elementos. Con el coeficiente de"
            <<"conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el"
            <<"total de elementos que se ubicarán en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente"
               <<"de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14).\n";
            return;
        }    
    }
    else if(strcmp(*it,"ruta_mas_larga")==0){
        int i=0;
        for(it = entrada.begin(); it != entrada.end(); it++){
                i++;
        }
        if(i < 3){
            cerr<<"Error: faltan argumentos\n";
            return;
        }
        else if(i > 3){
            cerr<<"Error: demasiados argumentos\n";
            return;
        }
        else {
            cout<<"Descripción de la función:\nCon el mapa ya creado, el comando permite identificar los dos componentes más alejados"
            <<"entre sí de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los ele-"
            <<"mentos más alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que"
            <<"estén a mayor distancia euclidiana entre sí. Al encontrar esa ruta más larga dentro del mapa, el comando"
            <<"imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de"
            <<"elementos que hay que seguir para ir del elemento origen al elemento destino.\n";
            
            return;
        }    
    }
    else if(strcmp(*it,"salir") ==0 || strcmp(*it,"exit")==0){
        exit(0);
    }
    else{
        cerr<<"Error: comando no reconocido\n";
        return;
    }
}