#include "Eleccion_2jugadores.h"

Eleccion_2jugadores::Eleccion_2jugadores() {
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 600, 600);
    logo = new ETSIDI::Sprite("assets/logo.png", -170, 210, 90, 90);
    cabecera = new ETSIDI::Sprite("assets/cabecera.png", -5, 210, 250, 180);
    logo2 = new ETSIDI::Sprite("assets/logo.png", 170, 210, 90, 90);
    back = new ETSIDI::Sprite("assets/back.png", 250, -250, 60, 40);
    cartel_menu = new ETSIDI::Sprite("assets/cartel_menu.png", 0, 80, 80, 30);
    boton_activo = 0;
    indicador_manana = new ETSIDI::Sprite("assets/indicador.png", -110, 30, 30, 30); 
    indicador_tarde = new ETSIDI::Sprite("assets/indicador.png", -110, -5, 30, 30);    
    indicador_random = new ETSIDI::Sprite("assets/indicador.png", -110, -40, 30, 30);
    manana_primero = new ETSIDI::Sprite("assets/manana_primero.png", 10, 30, 200, 25);
    tarde_primero = new ETSIDI::Sprite("assets/tarde_primero.png", 10, -5, 200, 25);
    random = new ETSIDI::Sprite("assets/random.png", 10, -40, 200, 25);
}

void Eleccion_2jugadores::dibuja() {
    fondo->draw();
    manana_primero->draw();
    tarde_primero->draw();
    logo->draw();
    cabecera->draw();
    logo2->draw();
    back->draw();
    cartel_menu->draw();
    random->draw();


    if (boton_activo == 1) indicador_manana->draw();
    else if (boton_activo == 2) indicador_tarde->draw();
    else if (boton_activo == 3) indicador_random->draw();
}

void Eleccion_2jugadores::update(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400; // convierte la x del ratón a OpenGL
    float cy = 400 - (y / 1000.0f) * 800; //convierte la y del ratón a OpenGL

    if (cx >= -80 && cx <= 70 && cy >= 15 && cy <= 45) // area mañana primero
        boton_activo = 1;
    else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)// area tarde primero
        boton_activo = 2;
    else if (cx >= -65 && cx <= 85 && cy >= -55 && cy <= -25)// area random
        boton_activo = 3;
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4; //back
    else
        boton_activo = 0;
}

Modos_juego Eleccion_2jugadores::click(int x, int y) {
    float cx = (x / 1000.0f) * 800 - 400;
    float cy = 400 - (y / 1000.0f) * 800;

    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235) //si le das a back
        return Modos_juego::MENU;

    return Modos_juego::Eleccion_2jugadores;
}