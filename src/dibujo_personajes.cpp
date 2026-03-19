#include "dibujo_personajes.h"

//Llamada al constructor de ETSIDI.h
DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p),
    sprite(("bin/assets//" + p->getNombre() + ".png").c_str()) //Conversión a string 
{
    
}

void DibujoPersonaje::dibujar() {
    // Sincronizar posición y dibujar
    sprite.setPos(modelo->getPosX(), modelo->getPosY());
    sprite.draw();
}