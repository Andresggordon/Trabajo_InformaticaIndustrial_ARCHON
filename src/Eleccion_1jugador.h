/**
 * @file Eleccion_1jugador.h
 * @brief Define el menú de selección de bando para el modo de un jugador (Humano vs IA).
 *
 * @details Gestiona la interfaz gráfica donde el usuario decide si desea controlar al equipo
 * del "Turno de Mañana" o al "Turno de Tarde". Se encarga de procesar las interacciones del
 * ratón y actualiza las variables globales de configuración
 * (`equipo_j1` y `equipo_j2`) antes de pasar al siguiente menú.
 */

#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

extern int equipo_j1;
extern int equipo_j2;
extern int modo_juego;
extern int turno_inicio;

class Eleccion_1jugador {
public:
    Eleccion_1jugador();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* turno_tarde;
    ETSIDI::Sprite* turno_manana;
    ETSIDI::Sprite* indicador_tarde;
    ETSIDI::Sprite* indicador_manana;
    ETSIDI::Sprite* back;
    int boton_activo = 0;
    
};