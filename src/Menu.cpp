#include "Menu.h"

Menu::Menu() {
    // Fondo - toda la ventana
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 400, 400);

    // Logo a la izquierda de la cabecera (proporción 483x517 → ~48x51)
    logo = new ETSIDI::Sprite("assets/logo.png", 5, 4, 48, 51);

    // Cabecera (proporción 676x369 → ~342x47) pegada al logo
    cabecera = new ETSIDI::Sprite("assets/cabecera.png", 53, 4, 342, 47);

    // Cartel MENU (proporción 307x97 → ~200x63) centrado
    cartel_menu = new ETSIDI::Sprite("assets/cartel_menu.png", 100, 120, 200, 63);

    // Botones centrados (todos ~220x34)
    boton_UnJugador = new ETSIDI::Sprite("assets/boton_UnJugador.png", 90, 195, 220, 34);
    boton_DosJugadores = new ETSIDI::Sprite("assets/boton_DosJugadores.png", 90, 238, 220, 29);
    boton_Ranking = new ETSIDI::Sprite("assets/boton_Ranking.png", 90, 278, 220, 38);

    // Indicador (proporción 218x227 → ~22x23)
    indicador = new ETSIDI::Sprite("assets/indicador.png", 70, 197, 22, 23);

    boton_activo = 0;
}

void Menu::dibuja() {
    fondo->draw();
    logo->draw();
    cabecera->draw();
    cartel_menu->draw();
    boton_UnJugador->draw();
    boton_DosJugadores->draw();
    boton_Ranking->draw();
    indicador->draw();
}

void Menu::update(int x, int y) {
    if (y >= 195 && y <= 229) {
        boton_activo = 0;
        indicador->setPos(70, 197);
    }
    else if (y >= 238 && y <= 267) {
        boton_activo = 1;
        indicador->setPos(70, 240);
    }
    else if (y >= 278 && y <= 316) {
        boton_activo = 2;
        indicador->setPos(70, 280);
    }
}

Modos_juego Menu::click(int x, int y) {
    if (y >= 195 && y <= 229)
        return Modos_juego::Un_jugador;
    return Modos_juego::MENU;
}