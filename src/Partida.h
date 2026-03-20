#pragma once
#include "Menu.h"
#include "Tablero.h"
#include "Tablero_vista.h"

class Partida {
public:
    Partida();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    Tablero* tablero;
    Tablero_vista* tablero_vista;
    ETSIDI::Sprite* fondo;
};