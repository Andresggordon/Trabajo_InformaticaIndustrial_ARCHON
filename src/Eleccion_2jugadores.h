/**
 * @file Eleccion_2jugadores.h
 * @brief Define la pantalla de configuración previa para el modo multijugador local.
 *
 * @details Maneja la interfaz mostrada cuando dos usuarios deciden jugar en el mismo
 * equipo (1 vs 1). Se encarga de renderizar la información pertinente, capturar la
 * interacción del ratón y asegurar que los identificadores de equipo se establecen
 * correctamente para un enfrentamiento humano contra humano antes de iniciar el tablero.
 */

#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

extern int equipo_j1;
extern int equipo_j2;

class Eleccion_2jugadores {
public:
    Eleccion_2jugadores();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* back;
    int boton_activo = 0;
    
};