// primera implementacion de calculo de efectividad considerando la distancia euclidiana
float Jugador::CalcularEfectividadHasta(const Jugador& otro) const {
    float deltaX = otro.m_PosX - m_PosX;
    float deltaY = otro.m_PosY - m_PosY;

    float distancia = sqrt(deltaX * deltaX + deltaY * deltaY);

    return 1 - distancia / m_TamanoTerreno;
}

// Esta función se encarga de obtener todas las secuencias óptimas de pases entre los jugadores
// Dependiendo de si se quiere realizar una jugada de ataque o defensa
SituacionDeJuego::SecuenciasOptimas SituacionDeJuego::ObtenerSecuenciasOptimas(int numero, bool esAtaque) const {
    SecuenciasOptimas secuencias;

    // Iteramos sobre todos los jugadores en la cancha
    for (const Jugador& jugador : m_Jugadores) {
        // Calculamos la efectividad del pase desde el jugador activo al jugador actual en la iteración
        float efectividadPase = m_Jugadores[numero].CalcularEfectividadHasta(jugador);

        // Creamos un nuevo nodo para esta secuencia
        NodoSecuenciasOptimas nodo;
        nodo.ElPaseVieneDesde = numero;

        // Agregamos el nodo a las secuencias óptimas
        secuencias.push_back(nodo);
    }

    // Finalmente, devolvemos las secuencias óptimas
    return secuencias;
}

// Esta función se encarga de obtener la secuencia óptima de pases para una estrategia de juego determinada (ataque o defensa)
SituacionDeJuego::SecuenciaOptima SituacionDeJuego::ObtenerSecuenciaOptima(int numero, bool esAtaque) const {
    SecuenciaOptima secuenciaOptima;

    // Primero, obtenemos todas las secuencias óptimas
    SecuenciasOptimas secuencias = ObtenerSecuenciasOptimas(numero, esAtaque);

    // Iteramos sobre todas las secuencias óptimas para encontrar la más efectiva
    float maxEfectividad = -1.0;
    for (const NodoSecuenciasOptimas& nodo : secuencias) {
        // Calculamos la efectividad de esta secuencia
        float efectividad = m_Jugadores[numero].CalcularEfectividadHasta(m_Jugadores[nodo.ElPaseVieneDesde]);

        // Si la efectividad de esta secuencia es mayor que la máxima efectividad encontrada hasta ahora
        if (efectividad > maxEfectividad) {
            // Actualizamos la máxima efectividad y la secuencia óptima
            maxEfectividad = efectividad;
            secuenciaOptima.Secuencia = { numero, nodo.ElPaseVieneDesde };
            secuenciaOptima.ProbabilidadFinal = efectividad;
            secuenciaOptima.TodosLosJugadores = false; // Suponemos que no todos los jugadores participan en la secuencia
        }
    }

    // Finalmente, devolvemos la secuencia óptima
    return secuenciaOptima;
}
