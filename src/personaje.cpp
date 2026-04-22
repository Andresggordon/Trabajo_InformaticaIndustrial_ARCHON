#include "personaje.h"
#include "Tablero.h"
#include "Casilla.h"

Personaje::Personaje(std::string nombre_, int vida_, int posX_, int posY_,
    Turno turno_, Movimiento movimiento_, stats arma_, Tablero& tab)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
    pos_x(posX_), pos_y(posY_), turno(turno_),
    movimiento(movimiento_), arma(arma_), tablero_(tab) {
}  // ← tablero_ no tablero

Personaje::~Personaje() {}

void Personaje::recibirDano(int cantidad_) {
    vida_actual -= cantidad_;
    if (vida_actual < 0) vida_actual = 0;
}

void Personaje::curar(int cantidad_) {
    vida_actual += cantidad_;
    if (vida_actual > vida_Max) vida_actual = vida_Max;
}

bool Personaje::estaVivo() const { return vida_actual > 0; }

std::string Personaje::getNombre() const { return nombre; }
int Personaje::getPosX() const { return pos_x; }
int Personaje::getPosY() const { return pos_y; }
float Personaje::getPorcentajeVida() const { return (float)vida_actual / vida_Max; }
int Personaje::getVidaActual() const { return vida_actual; }
int Personaje::getVidaMax() const { return vida_Max; }
bool Personaje::getInmovilizado() const { return inmovilizado; }
Movimiento Personaje::getMovimiento() const { return movimiento; }

void Personaje::setPosicion(int x_, int y_) {
    pos_x = x_;
    pos_y = y_;
}

bool Personaje::mover(int destinoX, int destinoY) {  // ← sin Tablero& como parámetro
    if (inmovilizado) return false;
    if (!esMovimientoLegal(destinoX, destinoY)) return false;

    Casilla& destino = tablero_.getCasilla(destinoY, destinoX);

    destino.setPersonaje(this);
    pos_x = destinoX;
    pos_y = destinoY;

    return true;
}

Turno Personaje::getTurno() const //Determinar los turnos de movimiento
{
    return turno;
}