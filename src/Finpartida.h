#pragma once
#include "personaje.h"
#include "Tablero.h"
#include <vector>

// ============================================================
//  Enum que indica el estado de la partida
// ============================================================
enum class CondicionVictoria {
    NINGUNA,                  // partida en curso
    GANA_MANANA_POR_PIEZAS,   // manana elimino todas las piezas de tarde
    GANA_TARDE_POR_PIEZAS,    // tarde elimino todas las piezas de manana
    GANA_MANANA_POR_PUNTOS,   // manana controla los 5 puntos de poder
    GANA_TARDE_POR_PUNTOS,    // tarde controla los 5 puntos de poder
};

// ============================================================
//  Clase FinPartida  
//
//  RESPONSABILIDAD UNICA: detectar si la partida ha terminado
//  y por que razon.
//
//  Es logica pura: no dibuja, no conoce el ratón ni el teclado.
//  Solo lee datos del Tablero y del vector de personajes.
//  Esto cumple alta cohesion / bajo acoplamiento.
// ============================================================
class FinPartida {
public:
    // Comprueba el estado actual de la partida.
    // Devuelve la condicion de victoria detectada (o NINGUNA).
    static CondicionVictoria comprobar(
        const std::vector<Personaje*>& personajes,
        const Tablero& tablero);

    // Helpers para saber rapidamente quien ha ganado a partir del resultado
    static bool ganaManana(CondicionVictoria c);
    static bool ganaTarde(CondicionVictoria c);
    static bool partidaTerminada(CondicionVictoria c);

    // Posiciones de los 5 puntos de poder del tablero 9x9
    // Formato: {fila, columna}
    static const int NUM_PUNTOS_PODER = 5;
    static const int PUNTOS_PODER[5][2];

private:
    // Cuenta cuantas piezas vivas tiene un bando concreto
    static int contarVivas(
        const std::vector<Personaje*>& personajes,
        Turno bando);

    // Cuenta cuantos puntos de poder controla un bando
    static int puntosDePoderControlados(
        const std::vector<Personaje*>& personajes,
        Turno bando);
};