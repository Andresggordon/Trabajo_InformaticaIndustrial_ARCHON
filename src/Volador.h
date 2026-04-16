#pragma once
#include "Personaje.h"

class Volador : public Personaje {
public:
    using Personaje::Personaje;

    bool esMovimientoLegal(int destinoX, int destinoY) const override {
        int dx = abs(destinoX - pos_x);
        int dy = abs(destinoY - pos_y);
        return dx <= getRadioMovimiento() && dy <= getRadioMovimiento();
    }
};