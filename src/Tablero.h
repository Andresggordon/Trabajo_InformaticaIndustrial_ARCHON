/**
 * @file Tablero.h
 * @brief Estructura de datos lógica que representa el campo de batalla y sus reglas de ciclo.
 *
 * @details Modela la cuadrícula 9x9 del juego instanciando y organizando una matriz bidimensional
 * de objetos `Casilla`. Centraliza el control espacial de las piezas, gestiona el sistema
 * de progresión de fases (`FaseCiclo`) que altera las condiciones de combate,
 * y maneja las transiciones lógicas (origen y destino) antes de enviar a las piezas colisionadas
 * a la Arena de Combate.
 */

#pragma once
#include "Casilla.h"
#include "ArenaCombate.h"

class Personaje;
class Casilla;
enum class ResultadoMover;

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

    ResultadoMover moverPersonaje(Personaje* p, Casilla& destino);

    void resolverCombate(ResultadoCombate resultado);
    void reset();

    // Ahora devuelven el objeto Casilla directamente
    Casilla& getCasilla(int fila, int col);
    const Casilla& getCasilla(int fila, int col) const;

    FaseCiclo getFase() const;
    void getColorDinamica(float& r, float& g, float& b) const;

    Personaje* getPendienteLocal()   const { return pendienteLocal_; }
    Personaje* getPendienteInvasor() const { return pendienteInvasor_; }
    void limpiarPendiente();

    static const int FILAS = 9;
    static const int COLUMNAS = 9;

private:
    Casilla matriz[FILAS][COLUMNAS];
    FaseCiclo fase_actual;

    void inicializarMatriz();

    Personaje* pendienteLocal_ = nullptr;
    Personaje* pendienteInvasor_ = nullptr;
};

