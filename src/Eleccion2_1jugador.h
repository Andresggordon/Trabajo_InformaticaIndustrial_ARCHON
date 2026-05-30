/**
 * @file Eleccion2_1jugador.h
 * @brief Define el menú secundario del modo de un jugador, centrado en el orden de iniciativa.
 *
 * @details Representa la interfaz final de configuración antes de la partida. Permite al
 * usuario decidir qué bando realizará el primer movimiento en el tablero, ofreciendo las
 * opciones de empezar con el "Turno de Mañana", "Turno de Tarde" o de forma aleatoria.
 * Tras procesar el clic, ajusta la variable global `turno_inicio` y transiciona al juego.
 */

#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

extern int equipo_j1;
extern int equipo_j2;
extern int modo_juego;
extern int turno_inicio;

class Eleccion2_1jugador {
public:
    Eleccion2_1jugador();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* tarde_primero;
    ETSIDI::Sprite* manana_primero;
    ETSIDI::Sprite* random;
    ETSIDI::Sprite* indicador_tarde;
    ETSIDI::Sprite* indicador_manana;
    ETSIDI::Sprite* indicador_random;
    ETSIDI::Sprite* back;
    int boton_activo = 0;
};