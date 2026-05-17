// IAJugador es el cerebro de la maquina en el modo 1 jugador (tablero).
//
// Responsabilidad unica: elegir el mejor movimiento de su bando y ejecutarlo.
// NO conoce el estado de la interfaz (Modos_juego), ni la arena, ni los turnos
// del juego: solo razona sobre el Tablero. Quien orquesta el flujo (cambiar de
// turno, pasar a la arena tras un choque) sigue siendo Partida.
//
// Delega TODO el "cuanto vale un movimiento" en EvaluadorMovimiento: IAJugador
// solo sabe "probar todas las piezas y quedarme con la mejor jugada". Esa
// separacion mantiene cada clase con una unica razon para cambiar.


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
