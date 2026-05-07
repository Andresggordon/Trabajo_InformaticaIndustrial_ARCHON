#include "dibujo_personajes.h"

//Llamada al constructor de ETSIDI.h
DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p),
    sprite(("assets/personajes_imagenes/" + p->getNombreSprite() + ".png").c_str()) //Conversión a string 
{
}

void DibujoPersonaje::dibujar(float x, float y) {
    sprite.setPos(x, y);
    sprite.setSize(45.0f, 45.0f);
    sprite.draw();
}