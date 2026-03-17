#include "Tablero.h"

Tablero::Tablero() {
    fase_actual = FaseCiclo::ATARDECER; //empezamos con atardecer
    inicializarMatriz();
}

void Tablero::inicializarMatriz() {
    EstadoCasilla B = EstadoCasilla::BLANCA_FIJA;
    EstadoCasilla A = EstadoCasilla::AZUL_FIJA;
    EstadoCasilla D = EstadoCasilla::DINAMICA;

    EstadoCasilla patron[FILAS][COLUMNAS] = {
        {A, B, A, D, D, D, B, A, B}, //fila 0
        {B, A, D, B, D, A, D, B, A},
        {A, D, B, A, D, B, A, D, B},
        {D, B, A, B, D, A, B, A, D},
        {B, D, D, D, D, D, D, D, A},
        {D, B, A, B, D, A, B, A, D},
        {A, D, B, A, D, B, A, D, B},
        {B, A, D, B, D, A, D, B, A},
        {A, B, A, D, D, D, B, A, B}, //fila 8
    };
   
    //copia patrón a la matriz
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            matriz[i][j] = patron[i][j];
}

//Ciclo cerrado que avanza las fases
void Tablero::avanzarCiclo() {
    switch (fase_actual) {
    case FaseCiclo::MEDIODIA:   fase_actual = FaseCiclo::ATARDECER;  break;
    case FaseCiclo::ATARDECER:  fase_actual = FaseCiclo::ANOCHECER;  break;
    case FaseCiclo::ANOCHECER:  fase_actual = FaseCiclo::MEDIANOCHE; break;
    case FaseCiclo::MEDIANOCHE: fase_actual = FaseCiclo::MADRUGADA;  break;
    case FaseCiclo::MADRUGADA:  fase_actual = FaseCiclo::AMANECER;   break;
    case FaseCiclo::AMANECER:   fase_actual = FaseCiclo::MEDIODIA;   break;
    }
}

//Saber que colores
EstadoCasilla Tablero::getCasilla(int fila, int col) const {
    return matriz[fila][col];
}

//Escala de azules
void Tablero::getColorDinamica(float& r, float& g, float& b) const {
    switch (fase_actual) {
    case FaseCiclo::MEDIODIA:   r = 1.0f; g = 1.0f; b = 1.0f; 
        break; // blanco puro
    case FaseCiclo::ATARDECER:  r = 0.6f; g = 0.7f; b = 0.9f; 
        break; // azul muy claro
    case FaseCiclo::ANOCHECER:  r = 0.2f; g = 0.4f; b = 0.7f;
        break; // azul medio
    case FaseCiclo::MEDIANOCHE: r = 0.0f; g = 0.0f; b = 0.3f; 
        break; // azul oscuro
    case FaseCiclo::MADRUGADA:  r = 0.2f; g = 0.4f; b = 0.7f; 
        break; // azul medio
    case FaseCiclo::AMANECER:   r = 0.6f; g = 0.7f; b = 0.9f; 
        break; // azul muy claro
    }
}
