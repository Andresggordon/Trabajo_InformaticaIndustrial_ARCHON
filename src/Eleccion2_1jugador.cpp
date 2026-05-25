#include "Eleccion2_1jugador.h"
#include <GL/freeglut.h>ç
#include<iostream>

Eleccion2_1jugador::Eleccion2_1jugador() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 800, 800);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 800, 800);
    boton_activo = 0;
    indicador_manana = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -131, 58, 30, 30);
    indicador_tarde = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -131, 8, 30, 30);
    indicador_random = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -131, -34, 30, 30);
    manana_primero = new ETSIDI::Sprite("assets/menu_imagenes/manana_primero.png", 0, 0, 800, 800);
    tarde_primero = new ETSIDI::Sprite("assets/menu_imagenes/tarde_primero.png", 0, 0, 800, 800);
    random = new ETSIDI::Sprite("assets/menu_imagenes/random.png", 0, 0, 800, 800);
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
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;

    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= -177 && cx <= 140 && cy >= 45 && cy <= 64)
        boton_activo = 1;
    else if (cx >= -177 && cx <= 124 && cy >= -2 && cy <= 16)
        boton_activo = 2;
    else if (cx >= -177 && cx <= -1 && cy >= -48 && cy <= -30)
        boton_activo = 3;
    else if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235)
        boton_activo = 4;
    else
        boton_activo = 0;
}

Modos_juego Eleccion2_1jugador::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;


    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328) {
        ETSIDI::play("assets/sonidos/click.mp3");
        return Modos_juego::Eleccion_1jugador;
    }
    else if (cx >= -177 && cx <= 140 && cy >= 45 && cy <= 64) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = 0;  // mañana primero (0 = mañana, misma codificacion que turno_actual)
        return Modos_juego::Partida;
    }
    else if (cx >= -177 && cx <= 124 && cy >= -2 && cy <= 16) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = 1;  // tarde primero (1 = tarde, misma codificacion que turno_actual)
        return Modos_juego::Partida;
    }
    else if (cx >= -177 && cx <= -1 && cy >= -48 && cy <= -30) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = ETSIDI::lanzaMoneda() ? 0 : 1;  // aleatorio
        return Modos_juego::Partida;
    }
    return Modos_juego::Eleccion2_1jugador;
}