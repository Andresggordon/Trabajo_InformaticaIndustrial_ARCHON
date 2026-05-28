#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"

class ComoJugar {
public:
    ComoJugar();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* boton_volver;
    int boton_activo;
    int pagina;
};