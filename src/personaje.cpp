#include "personaje.h"

// Implementación del constructor
Personaje::Personaje(std::string nombre_, int vida_, int posX_, int posY_,
    Turno turno_, Movimiento movimiento_, stats arma_)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
    pos_x(posX_), pos_y(posY_), turno(turno_),
    movimiento(movimiento_), arma(arma_) {}

Personaje::~Personaje() {}

void Personaje::recibirDano(int cantidad_) {
    vida_actual -= cantidad_;
    if (vida_actual < 0) vida_actual = 0;
}

void Personaje::curar(int cantidad_) {
    vida_actual += cantidad_;
    if (vida_actual > vida_Max) vida_actual = vida_Max;
}

bool Personaje::estaVivo() const {
    return vida_actual > 0;
}

// Implementación de Getters
std::string Personaje::getNombre() const { return nombre; }
int Personaje::getPosX() const { return pos_x; }
int Personaje::getPosY() const { return pos_y; }
float Personaje::getPorcentajeVida() const { return (float)vida_actual / vida_Max; }

void Personaje::setPosicion(int x_, int y_) {
    pos_x = x_;
    pos_y = y_;
}