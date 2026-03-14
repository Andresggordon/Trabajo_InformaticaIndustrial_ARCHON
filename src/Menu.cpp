#include "Menu.h"

Menu::Menu() {
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 600, 600);
        boton_activo = 0;
}

void Menu::dibuja() {
    fondo->draw();
}

void Menu::update(int x, int y) {
}

Modos_juego Menu::click(int x, int y) {
    return Modos_juego::MENU;
}