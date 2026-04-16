#pragma once
#include "personaje.h"

enum class EstadoCasilla { BLANCA_FIJA, AZUL_FIJA, DINAMICA };

class Casilla {
public:
    Casilla();
    EstadoCasilla getEstado() const;
    void setEstado(EstadoCasilla e);
    Personaje* getPersonaje() const;
    void setPersonaje(Personaje* p);

private:
    EstadoCasilla estado;
    Personaje* personaje;  // puntero, no propietario
};