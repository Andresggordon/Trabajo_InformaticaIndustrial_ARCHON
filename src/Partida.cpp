#include "Partida.h"
#include <GL/freeglut.h>

Partida::Partida() {
    tablero = new Tablero();

    // El motor gráfico recibe el tablero por referencia (*)
    motor_grafico = new MotorGrafico(*tablero);

    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 600, 600);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 600, 600);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 600, 600);
    mostrar_popup = false;
    boton_activo = 0;
}

void Partida::dibuja() {
    fondo->draw();

    motor_grafico->dibujar(); // <-- EL MOTOR SE ENCARGA DE TABLERO Y PERSONAJES

    abandonar_partida->draw();
    if (mostrar_popup)
        popup_salir->draw();

    //PRUEBA PARA PERSONAJES -- BORRADOR
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
            boton_activo = 2;  // si
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            boton_activo = 3;  // no
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
            // Sí → volver al menú: cambiar música
            ETSIDI::stopMusica();
            ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
            return Modos_juego::MENU;
        }
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            mostrar_popup = false;  // No → cerrar popup
    }
    return Modos_juego::Partida;
}

void Partida::teclado(unsigned char key) {
    if (key == 32)
        tablero->avanzarCiclo();
    if (key == 27)
        mostrar_popup = false;

    // PRUEBA MOVIMIENTO — borrar después
    if (key == 'w' && PSS_prueba)
        PSS_prueba->getPersonaje()->mover(
            PSS_prueba->getPersonaje()->getPosX(),
            PSS_prueba->getPersonaje()->getPosY() + 1
        );
    if (key == 's' && PSS_prueba)
        PSS_prueba->getPersonaje()->mover(
            PSS_prueba->getPersonaje()->getPosX(),
            PSS_prueba->getPersonaje()->getPosY() - 1
        );
    if (key == 'a' && PSS_prueba)
        PSS_prueba->getPersonaje()->mover(
            PSS_prueba->getPersonaje()->getPosX() - 1,
            PSS_prueba->getPersonaje()->getPosY()
        );
    if (key == 'd' && PSS_prueba)
        PSS_prueba->getPersonaje()->mover(
            PSS_prueba->getPersonaje()->getPosX() + 1,
            PSS_prueba->getPersonaje()->getPosY()
        );
}

void Partida::reset() {
    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false;
    boton_activo = 0;

    //PRUEBA PARA PERSONAJES -- BORRADOR

    if (modo_actual == 1 && turno_actual == 0) {
        Personaje* pss = new Profesor_SS(-4, 0, *tablero);
        Personaje* mh = new Profesor_MH(3, 2, *tablero);
    
        PSS_prueba = new DibujoPersonaje(pss);
        MH_prueba = new DibujoPersonaje(mh);
    };
}