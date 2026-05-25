#include "ranking.h"
#include <GL/freeglut.h>

Ranking::Ranking() {
    fondo2 = new ETSIDI::Sprite("assets/menu_imagenes/fondo2.png", 0, 0, 800, 800);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 800, 800);
    boton_activo = 0;
}

void Ranking::dibuja() {
    fondo2->draw();
    back->draw();
}

void Ranking::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (x >= 297 && cx <= 386 && cy >= -352 && cy <= -328)
        boton_activo = 1;
    else
        boton_activo = 0;
}

Modos_juego Ranking::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;


    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328) {
        ETSIDI::play("assets/sonidos/click.mp3");
        return Modos_juego::MENU;
    }
    return Modos_juego::Pantalla_Ranking;
}