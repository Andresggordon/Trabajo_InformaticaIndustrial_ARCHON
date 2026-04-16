#pragma once
#include "Personaje.h"

class Terrestre : public Personaje {
public:
    using Personaje::Personaje;

    bool esMovimientoLegal(int destinoX, int destinoY) const override {
        int dx = abs(destinoX - pos_x);
        int dy = abs(destinoY - pos_y);
        // Sin diagonales y dentro del radio
        return (dx == 0 || dy == 0) && (dx + dy) <= getRadioMovimiento();
    }
};
