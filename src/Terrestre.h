#pragma once
#include "personaje.h"

class Terrestre : public Personaje {
public:
    // Igual que Volador: la geometría del movimiento en cruz
    // ya no vive aquí, vive en Casilla::puedeMoverseA().
    // Esta clase agrupa a los personajes que se mueven por tierra.
    using Personaje::Personaje;
};