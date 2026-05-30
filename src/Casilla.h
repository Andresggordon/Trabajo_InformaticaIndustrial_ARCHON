/**
 * @file Casilla.h
 * @brief Define la clase Casilla, que representa cada una de las celdas individuales del tablero de juego.
 *
 * @details Actúa como el contenedor principal para la posición estructural (fila, columna) y el
 * estado lógico de la celda (BLANCA_FIJA, AZUL_FIJA o DINAMICA, lo cual influye en los bonus de combate).
 * Además, almacena una referencia (puntero) al objeto `Personaje` que la ocupa en cada momento,
 * sirviendo como nexo de información bidireccional entre el sistema de coordenadas del `Tablero`
 * y las entidades que interactúan sobre él.
 */

#pragma once
#include <vector>

enum class EstadoCasilla { BLANCA_FIJA, AZUL_FIJA, DINAMICA };
class Personaje;

class Casilla {
public:
    Casilla();

    EstadoCasilla getEstado() const;
    void setEstado(EstadoCasilla e);
    Personaje* getPersonaje() const;
    void setPersonaje(Personaje* p);
    int getFila() const;
    int getCol() const;
    void setPosicion(int fila, int col);

private:
    EstadoCasilla estado;
    Personaje* personaje;
    int fila_, col_;

};