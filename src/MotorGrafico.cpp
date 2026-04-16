#include "MotorGrafico.h"

MotorGrafico::MotorGrafico(Tablero& t) : tablero(t) {
    //fondo = new ETSIDI::Sprite("assets/fondo.png", ...); // Descomentar cuando tengas el sprite

    tam = 60.0f;
    inicioX = -270.0f;
    inicioY = -270.0f;
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

void MotorGrafico::dibujar() {
    // if(fondo) fondo->draw();
    dibujarTablero();
    dibujarPersonajes();
}

void MotorGrafico::dibujarTablero() {
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

            // Fíjate que ahora extraemos el ESTADO de la casilla
            EstadoCasilla tipo = tablero.getCasilla(fila, col).getEstado();

            if (tipo == EstadoCasilla::BLANCA_FIJA) {
                dibujaCuadrado(x, y, 1.0f, 1.0f, 1.0f);
            }
            else if (tipo == EstadoCasilla::AZUL_FIJA) {
                dibujaCuadrado(x, y, 0.0f, 0.0f, 0.3f);
            }
            else {
                float r, g, b;
                tablero.getColorDinamica(r, g, b);
                dibujaCuadrado(x, y, r, g, b);
            }
        }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujarPersonajes() {
    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            Personaje* p = tablero.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
                // Aquí calculamos la posición y le diremos al personaje que se dibuje
                float x = casillaPosX(col);
                float y = casillaPosY(fila);
                // p->dibuja(x, y); 
            }
        }
    }
}

float MotorGrafico::casillaPosX(int col) const {
    return inicioX + col * tam;
}

float MotorGrafico::casillaPosY(int fila) const {
    return inicioY + fila * tam;
}
