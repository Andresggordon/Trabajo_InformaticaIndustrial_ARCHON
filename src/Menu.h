#pragma once
#include "ETSIDI.h"

enum class Modos_juego {
    Pantalla_carga, MENU, Un_jugador, Dos_jugadores, Pantalla_Ranking,
    Eleccion_1jugador, Eleccion_2jugadores, Eleccion2_1jugador
};

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