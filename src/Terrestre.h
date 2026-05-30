/**
 * @file Terrestre.h
 * @brief Clase intermedia para la categorización de personajes terrestres.
 *
 * @details Hereda de `Personaje` y agrupa semánticamente a las unidades
 * con movimiento `TIERRA` (limitadas por obstáculos en la cuadrícula). Mantiene un constructor
 * transparente hacia la clase base, sirviendo como etiqueta de clasificación estructural en la jerarquía.
 */

#pragma once
#include "personaje.h"

class Terrestre : public Personaje {
public:
    // Igual que Volador: la geometría del movimiento en cruz
    // ya no vive aquí, vive en Casilla::puedeMoverseA().
    // Esta clase agrupa a los personajes que se mueven por tierra.
    using Personaje::Personaje;
};

