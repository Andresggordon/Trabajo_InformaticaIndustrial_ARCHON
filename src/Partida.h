#pragma once
#include "Menu.h"
#include "Tablero.h"
#include "Tablero_vista.h"
#include "ETSIDI.h"

class Partida {
public:
    Partida();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    void reset();

private:
    Tablero* tablero;
    Tablero_vista* tablero_vista;
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* abandonar_partida;
    ETSIDI::Sprite* popup_salir;
    
    bool mostrar_popup;
    int boton_activo;
};