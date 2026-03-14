#pragma once
#include "ETSIDI.h"

enum class Modos_juego {
	MENU, Un_jugador, Dos_jugadores, Ranking
};

class Menu {
public:
    Menu(); // Encargado de cargar las iamgenes
    void dibuja();  // dibuja el menú                   
    void update(int x, int y);   // Posición ratón    
    Modos_juego click(int x, int y);  // devulve lo que ha cliqueado

private:
    ETSIDI::Sprite* fondo;

    // Logo y decoración
    ETSIDI::Sprite* logo;
    ETSIDI::Sprite* cabecera;
    ETSIDI::Sprite* cartel_menu;

    // Botones
    ETSIDI::Sprite* boton_UnJugador;
    ETSIDI::Sprite* boton_DosJugadores;
    ETSIDI::Sprite* boton_Ranking;

    ETSIDI::Sprite* indicador;

    int boton_activo;
};
