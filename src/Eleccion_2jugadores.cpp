#include "Eleccion_2jugadores.h"
#include <GL/freeglut.h>

Eleccion_2jugadores::Eleccion_2jugadores() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 600, 600);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 600, 600);
    boton_activo = 0;
    indicador_manana = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, 40, 30, 30);
    indicador_tarde = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, 4, 30, 30);
    indicador_random = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, -30, 30, 30);
    manana_primero = new ETSIDI::Sprite("assets/menu_imagenes/manana_primero.png", 0, 0, 600, 600);
    tarde_primero = new ETSIDI::Sprite("assets/menu_imagenes/tarde_primero.png", 0, 0, 600, 600);
    random = new ETSIDI::Sprite("assets/menu_imagenes/random.png", 0, 0, 600, 600);
}

void Eleccion_2jugadores::dibuja() {
    fondo->draw();
    manana_primero->draw();
    tarde_primero->draw();
    back->draw();
    random->draw();
    if (boton_activo == 1) indicador_manana->draw();
    else if (boton_activo == 2) indicador_tarde->draw();
    else if (boton_activo == 3) indicador_random->draw();
}

void Eleccion_2jugadores::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= -88 && cx <= 106 && cy >= 31 && cy <= 51)
        boton_activo = 1;  // mañana primero
    else if (cx >= -65 && cx <= 85 && cy >= -5 && cy <= 14)
        boton_activo = 2;  // tarde primero
    else if (cx >= -89 && cx <= 2 && cy >= -39 && cy <= -20)
        boton_activo = 3;  // random
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


    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        return Modos_juego::MENU;  // back

    if (cx >= -88 && cx <= 106 && cy >= 31 && cy <= 51)
        return Modos_juego::Partida;  // mañana primero
    else if (cx >= -65 && cx <= 85 && cy >= -5 && cy <= 14)
        return Modos_juego::Partida;  // tarde primero
    else if (cx >= -89 && cx <= 2 && cy >= -39 && cy <= -20)
        return Modos_juego::Partida;  // random

    return Modos_juego::Eleccion_2jugadores;
}