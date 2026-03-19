#include "Tablero_vista.h"

Tablero_vista::Tablero_vista(Tablero* t) {
    mi_tablero = t;
    tam = 45.0f;
    inicioX = -202.5f;
    inicioY = -202.5f;
}

void Tablero_vista::dibujaCuadrado(float x, float y, float r, float g, float b) {
    glDisable(GL_TEXTURE_2D); 
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + tam, y);
    glVertex2f(x + tam, y + tam);
    glVertex2f(x, y + tam);
    glEnd();
}

void Tablero_vista::dibuja() {
    //hemos añadido esto primero por que ETSIDI Sprite modofixa internamente como esta OpenGL
    //Por eso hemos añadido estas lineas antes de dibujar
    glPushAttrib(GL_ALL_ATTRIB_BITS); //guarda el estado de OpenGL
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); //guarda la matriz que hice para el tablero
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400); //la reseta
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D); //quita texturas
    glDisable(GL_BLEND);//quita transparencias
    glDisable(GL_LIGHTING);//quita iluminación

    for (int fila = 0; fila < 9; fila++) {
        for (int col = 0; col < 9; col++) {
            float x = inicioX + col * tam;
            float y = inicioY + fila * tam;
            EstadoCasilla tipo = mi_tablero->getCasilla(fila, col);
            if (tipo == EstadoCasilla::BLANCA_FIJA) {
                dibujaCuadrado(x, y, 1.0f, 1.0f, 1.0f);
            }
            else if (tipo == EstadoCasilla::AZUL_FIJA) {
                dibujaCuadrado(x, y, 0.0f, 0.0f, 0.3f);
            }
            else {
                float r, g, b;
                mi_tablero->getColorDinamica(r, g, b);
                dibujaCuadrado(x, y, r, g, b);
            }
        }
    }

    //despues de todo el texto de dibujarlo lo restauro
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); //restaura matriz de proyeccion
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib(); //restaura todo el estado de OpenGL
}