#include "Menu.h"
#include <GL/freeglut.h>

Menu::Menu() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 600, 600);
    boton_UnJugador = new ETSIDI::Sprite("assets/menu_imagenes/boton_UnJugador.png", 0, 0, 600, 600);
    boton_DosJugadores = new ETSIDI::Sprite("assets/menu_imagenes/boton_DosJugadores.png", 0, 0, 600, 600);
    boton_Ranking = new ETSIDI::Sprite("assets/menu_imagenes/boton_Ranking.png", 0, 0, 600, 600);
    indicador_UnJugador = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -100, 40, 30, 30);
    indicador_DosJugadores = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -100, 5, 30, 30);
    indicador_Ranking = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -100, -26, 30, 30);
    quit = new ETSIDI::Sprite("assets/menu_imagenes/quit.png", 0, 0, 600, 600);
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
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= -66 && cx <= 82 && cy >= 28 && cy <= 55)
        boton_activo = 1;
    else if (cx >= -66 && cx <= 85 && cy >= 0 && cy <= 20)
        boton_activo = 2;
    else if (cx >= -63 && cx <= 65 && cy >= -30 && cy <= -14)
        boton_activo = 3;
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4;
    else
        boton_activo = 0;
}

Modos_juego Menu::click(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        glutLeaveMainLoop();
    else if (cx >= -66 && cx <= 82 && cy >= 28 && cy <= 55)
        return Modos_juego::Eleccion_1jugador;
    else if (cx >= -66 && cx <= 85 && cy >= 0 && cy <= 20)
        return Modos_juego::Eleccion_2jugadores;
    else if (cx >= -63 && cx <= 65 && cy >= -30 && cy <= -14)
        return Modos_juego::Pantalla_Ranking;
    return Modos_juego::MENU;
}