#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

class Eleccion_2jugadores {
public:
    Eleccion_2jugadores();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* tarde_primero;
    ETSIDI::Sprite* manana_primero;
    ETSIDI::Sprite* random;
    ETSIDI::Sprite* indicador_tarde;
    ETSIDI::Sprite* indicador_manana;
    ETSIDI::Sprite* indicador_random;
    ETSIDI::Sprite* back;
    int boton_activo = 0;
};