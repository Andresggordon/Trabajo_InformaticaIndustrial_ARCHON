#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

class Ranking {
public:
    Ranking();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo2;
    ETSIDI::Sprite* back;
    int boton_activo;
};