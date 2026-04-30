#include "Eleccion2_1jugador.h"
#include <GL/freeglut.h>

Eleccion2_1jugador::Eleccion2_1jugador() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 600, 600);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 600, 600);
    boton_activo = 0;
    indicador_manana = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, 40, 30, 30);
    indicador_tarde = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, 4, 30, 30);
    indicador_random = new ETSIDI::Sprite("assets/menu_imagenes/indicador.png", -110, -30, 30, 30);
    manana_primero = new ETSIDI::Sprite("assets/menu_imagenes/manana_primero.png", 0, 0, 600, 600);
    tarde_primero = new ETSIDI::Sprite("assets/menu_imagenes/tarde_primero.png", 0, 0, 600, 600);
    random = new ETSIDI::Sprite("assets/menu_imagenes/random.png", 0, 0, 600, 600);
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

    if (cx >= -88 && cx <= 106 && cy >= 31 && cy <= 51)
        boton_activo = 1;
    else if (cx >= -65 && cx <= 85 && cy >= -5 && cy <= 14)
        boton_activo = 2;
    else if (cx >= -89 && cx <= 2 && cy >= -39 && cy <= -20)
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

    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235) {
        ETSIDI::play("assets/sonidos/click.mp3");
        return Modos_juego::Eleccion_1jugador;
<<<<<<< HEAD

    }
    else if (cx >= -88 && cx <= 106 && cy >= 31 && cy <= 51) {
            ETSIDI::play("assets/sonidos/click.mp3");
            return Modos_juego::Partida;
    }
        else if (cx >= -65 && cx <= 85 && cy >= -5 && cy <= 14) {
            ETSIDI::play("assets/sonidos/click.mp3");
            return Modos_juego::Partida;
        }
        else if (cx >= -89 && cx <= 2 && cy >= -39 && cy <= -20) {
            ETSIDI::play("assets/sonidos/click.mp3");
            return Modos_juego::Partida;
        }
=======
    }
    else if (cx >= -88 && cx <= 106 && cy >= 31 && cy <= 51) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = 1;  // mañana primero
        return Modos_juego::Partida;
    }
    else if (cx >= -65 && cx <= 85 && cy >= -5 && cy <= 14) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = 2;  // tarde primero
        return Modos_juego::Partida;
    }
    else if (cx >= -89 && cx <= 2 && cy >= -39 && cy <= -20) {
        ETSIDI::play("assets/sonidos/click.mp3");
        turno_inicio = ETSIDI::lanzaMoneda() ? 1 : 2;  // random
        return Modos_juego::Partida;
    }
>>>>>>> Esther_1
    return Modos_juego::Eleccion2_1jugador;
}