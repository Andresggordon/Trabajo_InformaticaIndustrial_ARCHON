/**
 * @file IAJugador.h
 * @brief Define el controlador principal de la Inteligencia Artificial del juego.
 *
 * @details Esta clase actúa como el "cerebro" en las partidas de un jugador. Su responsabilidad
 * es analizar el estado actual del `Tablero`, utilizar al `EvaluadorMovimiento` para puntuar
 * todas las combinaciones posibles de casillas origen y destino para sus piezas, y ejecutar
 * automáticamente el movimiento que obtenga la mayor puntuación lógica.
 */

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
