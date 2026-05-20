#include "Proyectil.h"
#include <GL/freeglut.h>
#include <cmath>

Proyectil::Proyectil(float origenX, float origenY,
    float destinoX, float destinoY,
    int dano, float velocidad,
    const std::string& rutaSprite, bool disparadoPorLocal)
    : x_(origenX), y_(origenY)
    , destinoX_(destinoX), destinoY_(destinoY)
    , dano_(dano), velocidad_(velocidad)
     , disparadoPorLocal_(disparadoPorLocal)
{
    if (!rutaSprite.empty()) {
        sprite_ = new ETSIDI::Sprite(rutaSprite.c_str(), x_, y_, 50, 50);
        tieneSprite_ = true;
    }
}

Proyectil::~Proyectil() {
    delete sprite_;
}

void Proyectil::actualizar() {
    if (llegado_) return;

    float dx = destinoX_ - x_;
    float dy = destinoY_ - y_;
    float distancia = sqrt(dx * dx + dy * dy);

    if (distancia <= velocidad_) {
        llegado_ = true;
        return;
    }

    x_ += (dx / distancia) * velocidad_;
    y_ += (dy / distancia) * velocidad_;
    if (tieneSprite_)
        sprite_->setPos(x_, y_);
}

void Proyectil::dibujar() const {
    if (llegado_) return;

    if (tieneSprite_) {
        sprite_->draw();
        return;
    }

}

bool Proyectil::ColisionaCon(float x, float y, float radio) const {
    float dx = x_ - x;
    float dy = y_ - y;
    return sqrt(dx * dx + dy * dy) <= radio;
}