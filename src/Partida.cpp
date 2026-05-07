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
    for (auto d : dibujos)
        d->dibujar();
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


    modo_actual = modo_juego;      // 1=1jugador, 2=2jugadores
    turno_actual = turno_inicio;   // 1=mañana primero, 2=tarde primero


    // Limpiar listas por si reset() se llama más de una vez
    for (auto p : personajes) delete p;
    for (auto d : dibujos)    delete d;
    personajes.clear();
    dibujos.clear();

    // ── Equipo mañana  ──
    personajes.push_back(new Profesor_SS(tab_.getCasilla(0, 0)));
    personajes.push_back(new Microprocesador_M(tab_.getCasilla(0, 1)));
    personajes.push_back(new Multimetro(tab_.getCasilla(0, 2)));
    personajes.push_back(new PLC(tab_.getCasilla(0, 3)));
    personajes.push_back(new Fuente_de_tension_de_bateria(tab_.getCasilla(0, 4)));
    personajes.push_back(new Moto_electrica(tab_.getCasilla(0, 5)));
    personajes.push_back(new Copilot(tab_.getCasilla(0, 6)));
    personajes.push_back(new Circuito_integrado_M(tab_.getCasilla(0, 7)));
    // ── Equipo tarde ── 
    personajes.push_back(new Profesor_MH(tab_.getCasilla(0, 8)));
    personajes.push_back(new Microprocesador_T(tab_.getCasilla(0, 9)));
    personajes.push_back(new Osciloscopio(tab_.getCasilla(1, 0)));

    personajes.push_back(new Brazo_robot(tab_.getCasilla(1, 2)));
    personajes.push_back(new Fuente_de_corriente(tab_.getCasilla(1, 3)));
    personajes.push_back(new Moto_petrol(tab_.getCasilla(1, 4)));
    personajes.push_back(new Gemini(tab_.getCasilla(1, 5)));
    personajes.push_back(new Circuito_integrado_T(tab_.getCasilla(1, 6)));

    // Crear un DibujoPersonaje por cada personaje
    for (auto p : personajes)
        dibujos.push_back(new DibujoPersonaje(p));
}