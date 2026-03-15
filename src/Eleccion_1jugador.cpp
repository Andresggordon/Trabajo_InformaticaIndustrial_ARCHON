#include "Eleccion_1jugador.h"
#include "Eleccion2_1jugador.h"
Eleccion_1jugador::Eleccion_1jugador() {
    fondo = new ETSIDI::Sprite("assets/fondo.png", 0, 0, 600, 600);
    turno_tarde = new ETSIDI::Sprite("assets/turno_tarde.png", 20, -3, 200, 25);
    turno_manana = new ETSIDI::Sprite("assets/turno_manana.png", 17, 30, 200, 25);
    indicador_tarde = new ETSIDI::Sprite("assets/indicador.png", -100, -3, 30, 25);
    indicador_manana = new ETSIDI::Sprite("assets/indicador.png", -100, 30, 30, 30);
    logo = new ETSIDI::Sprite("assets/logo.png", -170, 210, 90, 90);
    cabecera = new ETSIDI::Sprite("assets/cabecera.png", -5, 210, 250, 180);
    logo2 = new ETSIDI::Sprite("assets/logo.png", 170, 210, 90, 90);
    back = new ETSIDI::Sprite("assets/back.png", 250, -250, 60, 40);
    cartel_menu = new ETSIDI::Sprite("assets/cartel_menu.png", 0, 80, 80, 30);
    boton_activo = 0;  // ← corregido, antes era "int boton_activo;"
}
void Eleccion_1jugador::dibuja() {
    fondo->draw();
    turno_manana->draw();
    turno_tarde->draw();
    logo->draw();
    cabecera->draw();
    logo2->draw();
    back->draw();
    cartel_menu->draw();
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
        return Modos_juego::Eleccion2_1jugador;  // turno mañana
  else if (cx >= -65 && cx <= 85 && cy >= -20 && cy <= 10)
      return Modos_juego::Eleccion2_1jugador;  // turno tarde

    return Modos_juego::Eleccion_1jugador;
}