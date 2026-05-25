


#pragma once
#include "EvaluadorMovimiento.h"

class Tablero;
enum class Turno;
enum class ResultadoMover;

class IAJugador {
public:
    IAJugador();

    // Elige y EJECUTA el mejor movimiento para `turnoMaquina` sobre `tablero`.
    // Devuelve que paso (OK / ILEGAL / CHOQUE) para que Partida gestione el
    // flujo igual que con un humano: OK -> cambia turno, CHOQUE -> arena.
    ResultadoMover jugarTurno(Tablero& tablero, Turno turnoMaquina);

private:
    EvaluadorMovimiento evaluador_;
};
