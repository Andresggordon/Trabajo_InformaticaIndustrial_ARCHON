#pragma once
#include "ETSIDI.h"
#include "Menu.h"

class Pantalla_carga {
public:
    Pantalla_carga();
    void dibuja();
    void update();
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    bool carga_completa;

private:
    ETSIDI::Sprite* fondo_carga;
    ETSIDI::Sprite* titulo_carga;
    ETSIDI::Sprite* logo1;
    ETSIDI::Sprite* logo2;
    bool esperando_enter;
    float timer;
};