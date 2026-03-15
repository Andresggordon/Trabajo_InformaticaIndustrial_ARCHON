#pragma once
#include "ETSIDI.h"
#include "Menu.h"

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
    ETSIDI::Sprite* logo;
    ETSIDI::Sprite* cabecera;
    ETSIDI::Sprite* logo2;
    ETSIDI::Sprite* back;
    ETSIDI::Sprite* cartel_menu;
    int boton_activo = 0;
    
};