#pragma once
#include "ETSIDI.h"

enum class Modos_juego {
    MENU, Un_jugador, Dos_jugadores, Ranking
};

class Menu {
public:
    Menu();
 
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo;
    //ETSIDI::Sprite* logo;
    //ETSIDI::Sprite* cabecera;
    //ETSIDI::Sprite* cartel_menu;
    //ETSIDI::Sprite* boton_UnJugador;
    //ETSIDI::Sprite* boton_DosJugadores;
   // ETSIDI::Sprite* boton_Ranking;
   // ETSIDI::Sprite* indicador;

    int boton_activo;
};