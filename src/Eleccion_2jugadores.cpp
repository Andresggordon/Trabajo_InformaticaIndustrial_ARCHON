#include "Eleccion_2jugadores.h"
#include <GL/freeglut.h>
#include <iostream>

Eleccion_2jugadores::Eleccion_2jugadores() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/eleccion2jugador.png", 0, 0, 600, 600);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 600, 600);
    boton_activo = 0;
   }

void Eleccion_2jugadores::dibuja() {
    fondo->draw();
    back->draw();
}

void Eleccion_2jugadores::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;
    

    if (cx >= -239 && cx <= -51 && cy >= -73 && cy <= 100)
        boton_activo = 1;  // mañana primero
    else if (cx >= 54 && cx <= 240 && cy >= -73 && cy <= 100)
        boton_activo = 2;  // tarde primero
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4;  // back
    else
        boton_activo = 0;
}

Modos_juego Eleccion_2jugadores::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235) {
        ETSIDI::play("assets/sonidos/click.mp3");
        return Modos_juego::MENU;  // back
    }
    else if (cx >= -239 && cx <= -51 && cy >= -73 && cy <= 100) {
        ETSIDI::play("assets/sonidos/click.mp3");
        equipo_j1 = 1;  // j1 = mañana
        equipo_j2 = 2;  // j2 = tarde
        return Modos_juego::Partida;
    }
    else if (cx >= 54 && cx <= 240 && cy >= -73 && cy <= 100) {
        ETSIDI::play("assets/sonidos/click.mp3");
        equipo_j1 = 2;  // j1 = tarde
        equipo_j2 = 1;  // j2 = mañana
        return Modos_juego::Partida;
    }

    return Modos_juego::Eleccion_2jugadores;


}