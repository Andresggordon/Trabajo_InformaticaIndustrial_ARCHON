#pragma once
#include "Tablero.h"
#include <GL/freeglut.h>

class Tablero_vista {
public:
    Tablero_vista(Tablero* t);
    void dibuja();

private:
    Tablero* mi_tablero;
    float tam;      // tamaño de cada casilla
    float inicioX;  // donde empieza a dibujar en X
    float inicioY;  // donde empieza a dibujar en Y

    void dibujaCuadrado(float x, float y, float r, float g, float b);
};