#pragma once
#include "ETSIDI.h"      // Dibujo de los sprites
#include "Casilla.h"
#include "personaje.h"  

class DibujoPersonaje {
public:
    // El constructor recibe el puntero al personaje lógico, para leer su posición
    DibujoPersonaje(Personaje* p);
	~DibujoPersonaje();

    // El método 
    void dibujar(float x, float y);
    void update() { sprite->loop(); }

    Personaje* getPersonaje() const { return modelo; }

private:
    Personaje* modelo;      // Puntero a la lógica del personaje
    ETSIDI::Sprite* sprite;    // usado si frames == 1
    ETSIDI::SpriteSequence* anim;    // usado si frames > 1

    //Para no resetear los frames y hacer la animación fluida de movimiento con las teclas
    int fila_actual_anim = -1;
};