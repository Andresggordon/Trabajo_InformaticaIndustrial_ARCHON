#pragma once
#include "personaje.h"
#include "Tablero.h"
#include <vector>

// -----------------------------------------------------------------------------------
//  FinPartida
//
//  RESPONSABILIDAD UNICA: decir si la partida ha terminado y por que.
//  Es logica pura: no dibuja, no conoce raton ni teclado, no cambia estados.
//  Solo CONSULTA el Tablero y el vector de personajes (todo const).
//  Alta cohesion, bajo acoplamiento.
// -----------------------------------------------------------------------------------

// Razon por la que ha terminado (o NINGUNA si sigue).
enum class CondicionVictoria {
    NINGUNA,

    GANA_MANANA_POR_LIDER,        // ha caido el mago de tarde
    GANA_TARDE_POR_LIDER,         // ha caido el mago de manana

    GANA_MANANA_POR_PIEZAS,       // tarde se ha quedado sin piezas
    GANA_TARDE_POR_PIEZAS,        // manana se ha quedado sin piezas

    GANA_MANANA_POR_ENCARCELADO,  // tarde queda con 1 pieza y encarcelada
    GANA_TARDE_POR_ENCARCELADO,   // manana queda con 1 pieza y encarcelada

    GANA_MANANA_POR_PUNTOS,       // manana controla los 5 puntos de poder
    GANA_TARDE_POR_PUNTOS,        // tarde controla los 5 puntos de poder
};

class FinPartida {
public:
    // Estado actual de la partida. Devuelve la condicion detectada (o NINGUNA).
    static CondicionVictoria comprobar(
        const std::vector<Personaje*>& personajes,
        const Tablero& tablero);

    static bool ganaManana(CondicionVictoria c);
    static bool ganaTarde(CondicionVictoria c);
    static bool partidaTerminada(CondicionVictoria c);

    // Los 5 puntos de poder del tablero 9x9: {fila, columna}
    static const int NUM_PUNTOS_PODER = 5;
    static const int PUNTOS_PODER[5][2];

private:
    // Una pieza esta "en juego" si esta viva Y colocada en el tablero.
    static bool enJuego(const Personaje* p);

    // Piezas en juego de un bando.
    static int contarEnJuego(const std::vector<Personaje*>& personajes, Turno bando);

    // ¿Sigue el mago/lider del bando en juego?
    static bool liderEnJuego(const std::vector<Personaje*>& personajes, Turno bando);

    // Piezas en juego del bando que NO estan encarceladas.
    static int contarNoEncarceladas(const std::vector<Personaje*>& personajes, Turno bando);

    // Puntos de poder ocupados por una pieza viva del bando (se lee del tablero).
    static int puntosDePoderControlados(Turno bando, const Tablero& tablero);
};
