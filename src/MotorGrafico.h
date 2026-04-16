#pragma once
#include "Tablero.h"
#include "ETSIDI.h"
#include <GL/freeglut.h> // Necesario para opengl

class MotorGrafico {
public:
    MotorGrafico(Tablero& tablero);
    void dibujar();

private:
    Tablero& tablero;   // Referencia, no propietario
    ETSIDI::Sprite* fondo;

    void dibujarTablero();
    void dibujarPersonajes();
    void dibujaCuadrado(float x, float y, float r, float g, float b);

    float casillaPosX(int col) const;
    float casillaPosY(int fila) const;

    float tam;      // tamaño de cada casilla
    float inicioX;  // donde empieza a dibujar en X
    float inicioY;  // donde empieza a dibujar en Y
};