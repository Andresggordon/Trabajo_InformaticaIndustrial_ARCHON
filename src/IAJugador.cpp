/**
 * @file IAJugador.cpp
 * @brief Implementación del cerebro de la máquina. Calcula y ejecuta el movimiento con mayor puntuación táctica.
 */

#include "IAJugador.h"
#include "personaje.h"
#include "Casilla.h"
#include "Tablero.h"
#include "Geometria.h"
#include <vector>

IAJugador::IAJugador() {
}

ResultadoMover IAJugador::jugarTurno(Tablero& tablero, Turno turnoMaquina) {
    Personaje* mejorPieza = nullptr;
    Casilla*   mejorDestino = nullptr;
    int        mejorPuntuacion = 0;
    bool       hayMejor = false;   // evita un valor centinela artificial

    // Recorremos el tablero buscando piezas propias que puedan moverse y,
    // para cada destino legal, preguntamos al evaluador cuanto vale la jugada.
    for (int f = 0; f < Tablero::FILAS; f++) {
        for (int c = 0; c < Tablero::COLUMNAS; c++) {
            Personaje* pieza = tablero.getCasilla(f, c).getPersonaje();

            if (pieza == nullptr) continue;
            if (!pieza->estaVivo()) continue;
            if (pieza->getTurno() != turnoMaquina) continue;
            if (pieza->getInmovilizado()) continue;   // este turno no se mueve

            std::vector<Casilla*> destinos =
                Geometria::getCasillasAccesibles(*pieza, tablero);

            for (Casilla* destino : destinos) {
                int puntos = evaluador_.evaluar(*pieza, *destino, tablero);
                if (!hayMejor || puntos > mejorPuntuacion) {
                    hayMejor = true;
                    mejorPuntuacion = puntos;
                    mejorPieza = pieza;
                    mejorDestino = destino;
                }
            }
        }
    }

    // Sin ningun movimiento posible (todas inmovilizadas o sin piezas):
    // devolvemos ILEGAL para que Partida no cambie el turno a ciegas.
    if (!hayMejor)
        return ResultadoMover::ILEGAL;

    return tablero.moverPersonaje(mejorPieza, *mejorDestino);
}
