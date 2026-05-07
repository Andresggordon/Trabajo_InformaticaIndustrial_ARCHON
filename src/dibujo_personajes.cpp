#include "dibujo_personajes.h"

//Llamada al constructor de ETSIDI.h
DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p),
    sprite(("assets/personajes_imagenes/" + p->getNombreSprite() + ".png").c_str()) //Conversión a string 
{
}

void DibujoPersonaje::dibujar() {
    // Mismos datos que para la vista del tablero
    float tam = 45.0f;
    float inicioX = -202.5f;
    float inicioY = -202.5f;

    // Posición en pantalla
    // y sumar (tam / 2.0f) para que el personaje quede centrado en la casilla
    float visualX = inicioX + (modelo->getPosX() * tam); //  + (tam / 2.0f)
    float visualY = inicioY + (modelo->getPosY() * tam); // + (tam / 2.0f)


    sprite.setPos(visualX, visualY);
    sprite.setSize(tam, tam);
    sprite.draw();
}