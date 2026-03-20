#include "Partida.h"


Partida::Partida() {
    tablero = new Tablero();
    tablero_vista = new Tablero_vista(tablero);
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 600, 600);
}

void Partida::dibuja() {
    fondo->draw();
    tablero_vista->dibuja();
}

void Partida::update(int x, int y) {
}

Modos_juego Partida::click(int x, int y) {
    return Modos_juego::Partida;
}