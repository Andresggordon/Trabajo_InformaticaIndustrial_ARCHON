#include "dibujo_personajes.h"

//Llamada al constructor de ETSIDI.h
DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p),
    sprite(("assets/personajes_imagenes/" + p->getNombre() + ".png").c_str()) //Conversión a string 
{
    
}

void DibujoPersonaje::dibujar() {
    // Mismos datos que para la vista del tablero
    float tam = 60.0f;
    float inicio = -270.0f;

    // Posición en pantalla
    // y sumar (tam / 2.0f) para que el personaje quede centrado en la casilla
    float visualX = inicio + (modelo->getPosX() * tam) + (tam / 2.0f);
    float visualY = inicio + (modelo->getPosY() * tam) + (tam / 2.0f);

    sprite.setPos(visualX, visualY);
    sprite.setSize(60.0f, 60.0f);
    sprite.draw();
}