#pragma once
#include "ETSIDI.h"      // Dibujo de los sprites
#include "personaje.h"  

class DibujoPersonaje {
public:
    // El constructor recibe el puntero al personaje lógico, para leer su posición
    DibujoPersonaje(Personaje* p);

    // El método 
    void dibujar();

private:
    Personaje* modelo;      // Puntero a la lógica del personaje
    ETSIDI::Sprite sprite;  
};