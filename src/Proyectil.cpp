/**
 * @file Proyectil.cpp
 * @brief Clase para el control de los proyectiles para la arena
 *
 * @details Crea y destruye los proyectiles de cada personaje.
 * Implementa cada proyectil con su información específica de velocidad, daño y alcance, y su sprite único.
 * 
 *
 */

#include "Proyectil.h"
#include <GL/freeglut.h>
#include <cmath>
#include "ArenaCombate.h"

//El constructor de la clase donde tiene la información necesaria para utilizar los proyectiles.
//Teniendo por ejemplo, la información de la posición de origen, la posición final dependiendo del alcance, etc...
Proyectil::Proyectil(float origenX, float origenY,
    float destinoX, float destinoY,
    int dano, float velocidad,
    const std::string& rutaSprite, bool disparadoPorLocal,int alcance)
    : x_(origenX), y_(origenY)
    , destinoX_(destinoX), destinoY_(destinoY)
    , dano_(dano), velocidad_(velocidad)
     , disparadoPorLocal_(disparadoPorLocal)
{
    if (!rutaSprite.empty()) {
        sprite_ = new ETSIDI::Sprite(rutaSprite.c_str(), x_, y_, 50, 50);
        tieneSprite_ = true;
    }

    origenX_ = origenX;
    origenY_ = origenY;
    distanciaMaxima_ = alcance * ArenaCombate::TAM_CASILLA;
}
//Borra el proyectil al final
Proyectil::~Proyectil() {
   // delete sprite_;
}
//Actualiza en tiempo real el proyectil en la pantalla, controlando la trayectoria y la velocidad.
//Y cuando llega al final lo destruye si no detecta la colisión.
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

    if (tieneSprite_) sprite_->setPos(x_, y_);

    
    float recorrido = sqrt((x_ - origenX_) * (x_ - origenX_) +
        (y_ - origenY_) * (y_ - origenY_));
    if (recorrido >= distanciaMaxima_) {
        llegado_ = true;  
    }
}
//Dibuja el proyectil correspondiente
void Proyectil::dibujar() const {
    if (llegado_) return;

    if (tieneSprite_) {
        
        sprite_->setPos(x_, y_);

        
        sprite_->draw();
        return;
    }
}
//Detecta la colisión con el otro personaje si se encuentra en el radio de alcance del proyectil.
bool Proyectil::ColisionaCon(float x, float y, float radio) const {
    float dx = x_ - x;
    float dy = y_ - y;
    return sqrt(dx * dx + dy * dy) <= radio;
}