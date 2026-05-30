/**
 * @file Menu.h
 * @brief Define la pantalla principal del juego (Menú de Inicio).
 *
 * @details Gestiona la interfaz gráfica principal a la que accede el usuario tras la pantalla
 * de carga. Permite navegar entre las opciones fundamentales del juego: "1 Jugador" (contra IA),
 * "2 Jugadores" (multijugador local) y el acceso al "Ranking". Controla las animaciones de
 * hover sobre los botones y devuelve el siguiente estado del juego tras un clic válido.
 */

#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

class Menu {
public:
    Menu();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* boton_UnJugador;
    ETSIDI::Sprite* boton_DosJugadores;
    ETSIDI::Sprite* boton_Ranking;
    ETSIDI::Sprite* indicador_UnJugador;
    ETSIDI::Sprite* indicador_DosJugadores;
    ETSIDI::Sprite* indicador_Ranking;
    ETSIDI::Sprite* quit;
    int boton_activo;
};