#include "ranking.h"
#include <GL/freeglut.h>

Ranking::Ranking() {
    fondo2 = new ETSIDI::Sprite("assets/menu_imagenes/fondo2.png", 0, 0, 600, 600);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 600, 600);
    boton_activo = 0;
}

void Ranking::dibuja() {
    fondo2->draw();
    back->draw();
}

void Ranking::update(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 1;
    else
        boton_activo = 0;
}

Modos_juego Ranking::click(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        return Modos_juego::MENU;
    return Modos_juego::Pantalla_Ranking;
}