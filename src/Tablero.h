#pragma once

enum class EstadoCasilla {
    BLANCA_FIJA, //blanco
    AZUL_FIJA, // azul oscuro    
    DINAMICA // cambia
};

enum class FaseCiclo {
    MEDIODIA,// blanco
    ATARDECER,// azul muy claro
    ANOCHECER, // azul medio
MEDIANOCHE,// azul oscuro
MADRUGADA,// azul medio
AMANECER// azul muy claro
};

class Tablero {
public:
    Tablero(); //inicializa la matriz
    void avanzarCiclo(); // llama a los diferentes turnos
    EstadoCasilla getCasilla(int fila, int columna) const; //devuelve el tipo de casilla en esa posición
    FaseCiclo getFase() const; // devuelve la fase de ciclo
    void getColorDinamica(float& r, float& g, float& b) const;

    //tablero
    static const int FILAS = 9; 
    static const int COLUMNAS = 9;

private:
    EstadoCasilla matriz[FILAS][COLUMNAS]; //matriz guarda el tipo de casilla
    FaseCiclo fase_actual;//guarda fase ciclo
    void inicializarMatriz(); //rellena matriz
};