#include "Menu.h"

Menu::Menu() {
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 600, 600); 
    logo = new ETSIDI::Sprite("assets/logo.png",-170, 210, 90, 90);
    cabecera = new ETSIDI::Sprite("assets/cabecera.png", -5, 210, 250, 180);
    logo2 = new ETSIDI::Sprite("assets/logo.png", 170, 210, 90, 90);
    cartel_menu= new ETSIDI::Sprite("assets/cartel_menu.png", 0, 80, 80, 30);
    boton_UnJugador= new ETSIDI::Sprite("assets/boton_UnJugador.png", -5, 30, 150, 30);
    boton_DosJugadores = new ETSIDI::Sprite("assets/boton_DosJugadores.png", 10, -5, 150, 30);
    boton_Ranking = new ETSIDI::Sprite("assets/boton_Ranking.png", 10, -40, 150, 30);
    indicador_UnJugador = new ETSIDI::Sprite("assets/indicador.png", -100, 30, 30, 30);
    indicador_DosJugadores = new ETSIDI::Sprite("assets/indicador.png", -100, -3, 30, 30);
    indicador_Ranking = new ETSIDI::Sprite("assets/indicador.png", -100, -35, 30, 30);
    boton_activo = 0;
}

void Menu::dibuja() {
    fondo->draw();
    logo->draw();
    cabecera->draw();
    logo2->draw();
    cartel_menu->draw();
    boton_UnJugador->draw();
    boton_DosJugadores->draw();
    boton_Ranking->draw();

    if (boton_activo == 1) indicador_UnJugador->draw();
    else if (boton_activo == 2) indicador_DosJugadores->draw();
    else if (boton_activo == 3) indicador_Ranking->draw();
}

void Menu::update(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400; // convierte la x del ratón a OpenGL
    float cy = 400 - (y / 1000.0f) * 800; //convierte la y del ratón a OpenGL

    if (cx >= -80 && cx <= 70 && cy >= 15 && cy <= 45) // area del 1 jugador
        boton_activo = 1;
    else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)// area del 2 jugador
        boton_activo = 2;
    else if (cx >= -65 && cx <= 85 && cy >= -55 && cy <= -25)// area del ranking
        boton_activo = 3;
    else
        boton_activo = 0; 
}

Modos_juego Menu::click(int x, int y) {
    return Modos_juego::MENU;
}