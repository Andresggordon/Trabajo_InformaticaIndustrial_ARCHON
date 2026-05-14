<<<<<<< HEAD
#pragma once
#include "personaje.h"

class Terrestre : public Personaje {
public:
    // Igual que Volador: la geometría del movimiento en cruz
    // ya no vive aquí, vive en Casilla::puedeMoverseA().
    // Esta clase agrupa a los personajes que se mueven por tierra.
    using Personaje::Personaje;
};

=======
#pragma once
#include "personaje.h"

class Terrestre : public Personaje {
public:
    // Igual que Volador: la geometría del movimiento en cruz
    // ya no vive aquí, vive en Casilla::puedeMoverseA().
    // Esta clase agrupa a los personajes que se mueven por tierra.
    using Personaje::Personaje;
};

>>>>>>> 998d517d5d95f105c647aea597064eaa6853373e
//Esta clase deberia ser private porque no se va a usar fuera de esta jerarquia, pero la dejamos public para poder hacer pruebas unitarias