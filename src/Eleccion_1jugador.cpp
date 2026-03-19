#include "Eleccion_1jugador.h"
#include "Eleccion2_1jugador.h"

Eleccion_1jugador::Eleccion_1jugador() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 600, 600);
    turno_tarde = new ETSIDI::Sprite("assets/menu_imagenes/turno_tarde.png", 0, 0, 600, 600);
    turno_manana = new ETSIDI::Sprite("assets/menu_imagenes/turno_manana.png", 0, 0, 600, 600);
    indicador_tarde = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -100, -5, 30, 30);
    indicador_manana = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -100, 30, 30, 30);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 600, 600);
    boton_activo = 0;
}

void Eleccion_1jugador::dibuja() {
    fondo->draw();
    turno_manana->draw();
    turno_tarde->draw();
    back->draw();
    if (boton_activo == 1) indicador_manana->draw();
    else if (boton_activo == 2) indicador_tarde->draw();
}

void Eleccion_1jugador::update(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= -80 && cx <= 70 && cy >= 15 && cy <= 45)
        boton_activo = 1;
    else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)
        boton_activo = 2;
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4;
    else
        boton_activo = 0;
}

Modos_juego Eleccion_1jugador::click(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        return Modos_juego::MENU;
    else if (cx >= -80 && cx <= 70 && cy >= 15 && cy <= 45)
        return Modos_juego::Eleccion2_1jugador;
    else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)
        return Modos_juego::Eleccion2_1jugador;
    return Modos_juego::Eleccion_1jugador;
}