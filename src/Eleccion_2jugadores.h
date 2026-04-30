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