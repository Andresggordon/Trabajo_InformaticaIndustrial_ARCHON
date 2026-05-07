#pragma once
#include "Casilla.h"


enum class FaseCiclo {
    MEDIODIA,
    ATARDECER,
    ANOCHECER,
    MEDIANOCHE,
    MADRUGADA,
    AMANECER
};

class Tablero {
public:
    Tablero();
    void avanzarCiclo();

    bool moverPersonaje(Personaje* p, Casilla& destino);


    // Ahora devuelven el objeto Casilla directamente
    Casilla& getCasilla(int fila, int col);
    const Casilla& getCasilla(int fila, int col) const;

    FaseCiclo getFase() const;
    void getColorDinamica(float& r, float& g, float& b) const;

    static const int FILAS = 9;
    static const int COLUMNAS = 9;

private:
    Casilla matriz[FILAS][COLUMNAS];
    FaseCiclo fase_actual;

    void inicializarMatriz();
};

