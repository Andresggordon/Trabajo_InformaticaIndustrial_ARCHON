#include "dibujo_personajes.h"

//Llamada al constructor de ETSIDI.h
DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p),
    sprite(("assets/personajes_imagenes/" + p->getNombreSprite() + ".png").c_str()) //Conversión a string 
{
}

void DibujoPersonaje::dibujar(float x, float y) {
    float tam = modelo->getTamanoSprite();
    sprite.setPos(x, y);
    sprite.setSize(tam, tam);
    sprite.draw();
}