#include "Eleccion2_1jugador.h"

Eleccion2_1jugador::Eleccion2_1jugador() {
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 600, 600);
    back = new ETSIDI::Sprite("assets/back.png", 0, 0, 600, 600);
    boton_activo = 0;
    indicador_manana = new ETSIDI::Sprite("assets/indicador.png", -110, 40, 30, 30);
    indicador_tarde = new ETSIDI::Sprite("assets/indicador.png", -110, 4, 30, 30);
    indicador_random = new ETSIDI::Sprite("assets/indicador.png", -110, -30, 30, 30);
    manana_primero = new ETSIDI::Sprite("assets/manana_primero.png", 0, 0, 600, 600);
    tarde_primero = new ETSIDI::Sprite("assets/tarde_primero.png", 0, 0, 600, 600);
    random = new ETSIDI::Sprite("assets/random.png", 0, 0, 600, 600);
}

void Eleccion2_1jugador::dibuja() {
    fondo->draw();
    manana_primero->draw();
    tarde_primero->draw();
    random->draw();
    back->draw();
    if (boton_activo == 1) indicador_manana->draw();
    else if (boton_activo == 2) indicador_tarde->draw();
    else if (boton_activo == 3) indicador_random->draw();
}

void Eleccion2_1jugador::update(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= -80 && cx <= 70 && cy >= 15 && cy <= 45)
        boton_activo = 1;
    else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)
        boton_activo = 2;
    else if (cx >= -65 && cx <= 85 && cy >= -55 && cy <= -25)
        boton_activo = 3;
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4;
    else
        boton_activo = 0;
}

Modos_juego Eleccion2_1jugador::click(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;
    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        return Modos_juego::Eleccion_1jugador;
    return Modos_juego::Eleccion2_1jugador;
}