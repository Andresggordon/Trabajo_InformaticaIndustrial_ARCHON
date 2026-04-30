#include "Partida.h"
#include "MotorGrafico.h"
#include <GL/freeglut.h>



Partida::Partida() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 600, 600);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 600, 600);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 600, 600);
    mostrar_popup = false;
    boton_activo = 0;
}

void Partida::dibuja() {
    fondo->draw();  // solo el fondo
}

void Partida::dibujaextra() {
    abandonar_partida->draw();  // exit encima de todo
    if (mostrar_popup)
        popup_salir->draw();
}

void Partida::dibujaPersonajes() {
    if (PSS_prueba) PSS_prueba->dibujar();
    if (MH_prueba) MH_prueba->dibujar();
}


void Partida::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (!mostrar_popup) {
        if (cx >= 209 && cx <= 289 && cy >= -275 && cy <= -252)
            boton_activo = 1;
        else
            boton_activo = 0;
    }
    else {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5)
            boton_activo = 2;
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            boton_activo = 3;
        else
            boton_activo = 0;
    }
}

Modos_juego Partida::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    ETSIDI::play("assets/sonidos/click.mp3");
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (!mostrar_popup) {
        if (cx >= 209 && cx <= 289 && cy >= -275 && cy <= -252)
            mostrar_popup = true;
    }
    else {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
            return Modos_juego::MENU;
        }
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            mostrar_popup = false;
    }
    return Modos_juego::Partida;
}

void Partida::teclado(unsigned char key) {
    if (key == 32)
        tab_.avanzarCiclo();
    if (key == 27)
        mostrar_popup = false;
}

void Partida::reset() {
    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false;
    boton_activo = 0;

<<<<<<< HEAD
=======
    modo_actual = modo_juego;      // 1=1jugador, 2=2jugadores
    turno_actual = turno_inicio;   // 1=mañana primero, 2=tarde primero

>>>>>>> Esther_1
    // PRUEBA PARA PERSONAJES -- BORRADOR
    if (modo_actual == 1 && turno_actual == 0) {
        Personaje* pss = new Profesor_SS(-4, 0, tab_);
        Personaje* mh = new Profesor_MH(3, 2, tab_);
        PSS_prueba = new DibujoPersonaje(pss);
        MH_prueba = new DibujoPersonaje(mh);
    }
}