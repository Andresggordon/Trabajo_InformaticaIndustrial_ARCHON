#pragma once
#include "Tablero.h"
#include "ETSIDI.h"
#include <GL/freeglut.h>

class MotorGrafico {
public:
    // Singleton
    static MotorGrafico& get_instance() {
        static MotorGrafico instance;
        return instance;
    }

    void dibujar();

private:
    MotorGrafico();
	MotorGrafico(const MotorGrafico&) = delete; //Esto elimina el constructor de copia. Impide que se cree un nuevo objeto a partir de un objeto ya existente.
	MotorGrafico& operator=(const MotorGrafico&) = delete; // Modifica el operador asignación para no permitir asignar un objeto a otro de motor gráfico.

    // Parámetros del tablero
    float tam;      // tamaño de cada casilla
    float inicioX;  // donde empieza a dibujar en X
    float inicioY;  // donde empieza a dibujar en Y

    void dibujarTablero(const Tablero& t);
    void dibujarPersonajes(const Tablero& t);
    void dibujaCuadrado(float x, float y, float r, float g, float b);
};