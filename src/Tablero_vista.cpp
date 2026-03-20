#include "Tablero_vista.h"

TableroVista::TableroVista(Tablero* t) {
    mi_tablero = t;
    tam = 30.0f;
    inicioX = -135.0f;
    inicioY = -135.0f;
}

void TableroVista::dibujaCuadrado(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + tam, y);
    glVertex2f(x + tam, y + tam);
    glVertex2f(x, y + tam);
    glEnd();
}

void TableroVista::dibuja() {
    for (int fila = 0; fila < 9; fila++) {
        for (int col = 0; col < 9; col++) {

            float x = inicioX + col * tam;
            float y = inicioY + fila * tam;

            EstadoCasilla tipo = mi_tablero->getCasilla(fila, col);

            if (tipo == EstadoCasilla::BLANCA_FIJA) {
                dibujaCuadrado(x, y, 1.0f, 1.0f, 1.0f);  // blanco

            }
            else if (tipo == EstadoCasilla::AZUL_FIJA) {
                dibujaCuadrado(x, y, 0.0f, 0.0f, 0.3f);  // azul oscuro

            }
            else {
                float r, g, b;
                mi_tablero->getColorDinamica(r, g, b);
                dibujaCuadrado(x, y, r, g, b);  // color segun fase
            }
        }
    }
}