#include "MotorGrafico.h"
#include "Partida.h"

MotorGrafico::MotorGrafico() {
    tam = 60.0f;
    inicioX = -270.0f;
    inicioY = -270.0f;
}

void MotorGrafico::dibujar() {
    const Tablero& t = Partida::get_instance().tablero();  // accede al tablero via Singleton
    dibujarTablero(t);
    dibujarPersonajes(t);
}

void MotorGrafico::dibujarTablero(const Tablero& t) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            float x = inicioX + col * tam;
            float y = inicioY + fila * tam;
            EstadoCasilla tipo = t.getCasilla(fila, col).getEstado();

            if (tipo == EstadoCasilla::BLANCA_FIJA) {
                dibujaCuadrado(x, y, 1.0f, 1.0f, 1.0f);
            }
            else if (tipo == EstadoCasilla::AZUL_FIJA) {
                dibujaCuadrado(x, y, 0.0f, 0.0f, 0.3f);
            }
            else {
                float r, g, b;
                t.getColorDinamica(r, g, b);
                dibujaCuadrado(x, y, r, g, b);
            }
        }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujarPersonajes(const Tablero& t) {
    // TODO: cuando tengamos los sprites de personajes, dibujarlos aquí
    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            Personaje* p = t.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
                // TODO: elegir sprite según tipo de personaje y dibujarlo
            }
        }
    }
}

void MotorGrafico::dibujaCuadrado(float x, float y, float r, float g, float b) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + tam, y);
    glVertex2f(x + tam, y + tam);
    glVertex2f(x, y + tam);
    glEnd();
}