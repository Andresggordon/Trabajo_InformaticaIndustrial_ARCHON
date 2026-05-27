


#pragma once
#include "EvaluadorMovimiento.h"

class Tablero;
enum class Turno;
enum class ResultadoMover;

class IAJugador {
public:
    IAJugador();
    ResultadoMover jugarTurno(Tablero& tablero, Turno turnoMaquina);

private:
    EvaluadorMovimiento evaluador_;
};
