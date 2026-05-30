/**
 * @file Tablero_vista.h
 * @brief Clase auxiliar para el renderizado básico del campo de batalla.
 *
 * @details Actúa como una sub-vista utilizada por el `MotorGrafico`. Su única responsabilidad
 * es leer las dimensiones, estado y fase dinámica del objeto `Tablero` (modelo) y traducirlo a
 * instrucciones de dibujo primitivas de OpenGL (cuadrados y colores) para pintar
 * sin preocuparse por la lógica de los personajes o las interfaces de usuario.
 */

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