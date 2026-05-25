#include "Menu.h"
#include <GL/freeglut.h>
#include <iostream>


Menu::Menu() {

    ETSIDI::playMusica("assets/sonidos/menu.mp3", true);

    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 800, 800);
    boton_UnJugador = new ETSIDI::Sprite("assets/menu_imagenes/boton_UnJugador.png", 0, 0, 800, 800);
    boton_DosJugadores = new ETSIDI::Sprite("assets/menu_imagenes/boton_DosJugadores.png", 0, 0, 800, 800);
    boton_Ranking = new ETSIDI::Sprite("assets/menu_imagenes/boton_Ranking.png", 0, 0, 800, 800);
    indicador_UnJugador = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -97, 55, 30, 30);
    indicador_DosJugadores = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -97, 10, 30, 30);
    indicador_Ranking = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -97, -31, 30, 30);
    quit = new ETSIDI::Sprite("assets/menu_imagenes/quit.png", 0, 0, 800, 800);
    boton_activo = 0;
}

void Menu::dibuja() {
    fondo->draw();
    boton_UnJugador->draw();
    boton_DosJugadores->draw();
    boton_Ranking->draw();
    quit->draw();
    if (boton_activo == 1) indicador_UnJugador->draw();
    else if (boton_activo == 2) indicador_DosJugadores->draw();
    else if (boton_activo == 3) indicador_Ranking->draw();
}

void Menu::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= -82 && cx <= 107 && cy >= 39 && cy <= 65)
        boton_activo = 1;
    else if (cx >= -82 && cx <= 157 && cy >= -1 && cy <= 21)
        boton_activo = 2;
    else if (cx >= -82 && cx <= 76 && cy >= -46 && cy <= -20)
        boton_activo = 3;
    else if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328)
        boton_activo = 4;
    else
        boton_activo = 0;
}

Modos_juego Menu::click(int x, int y) {


    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;

    ETSIDI::play("assets/sonidos/click.mp3");

    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;


    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328)
        glutLeaveMainLoop();
    else if (cx >= -82 && cx <= 107 && cy >= 39 && cy <= 65)
        return Modos_juego::Eleccion_1jugador;
    else if (cx >= -82 && cx <= 157 && cy >= -1 && cy <= 21)
        return Modos_juego::Eleccion_2jugadores;
    else if (cx >= -82 && cx <= 76 && cy >= -46 && cy <= -20)
        return Modos_juego::Pantalla_Ranking;
    return Modos_juego::MENU;
}