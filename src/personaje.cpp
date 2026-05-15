#include "personaje.h"
#include "Casilla.h"
#include "Geometria.h"
#include "Tablero.h"
#include "Partida.h"

Personaje::Personaje(std::string nombre_, int vida_,
    Turno turno_, Movimiento movimiento_, stats arma_, Casilla& casillaInicial)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
    turno(turno_), movimiento(movimiento_), arma(arma_), casilla_actual(&casillaInicial)
{
	casilla_actual->setPersonaje(this);  // El personaje ocupa la casilla inicial
}  

void Personaje::setCasillaActual(Casilla* c) {
    casilla_actual = c; // Si tu variable privada se llama distinto, pon su nombre aquí
}
Personaje::~Personaje() {}


// SALUD

void Personaje::recibirDano(int cantidad_) {
    vida_actual -= cantidad_;
    if (vida_actual < 0) vida_actual = 0;
}

void Personaje::curar(int cantidad_) {
    vida_actual += cantidad_;
    if (vida_actual > vida_Max) vida_actual = vida_Max;
}

bool Personaje::estaVivo() const { return vida_actual > 0; }

// GETTERS
std::string Personaje::getNombre() const { return nombre; }
int Personaje::getPosX() const { return casilla_actual ? casilla_actual->getCol():-1; }
int Personaje::getPosY() const { return casilla_actual ? casilla_actual->getFila():-1; }
float Personaje::getPorcentajeVida() const { return (float)vida_actual / vida_Max; }
int Personaje::getVidaActual() const { return vida_actual; }
int Personaje::getVidaMax() const { return vida_Max; }
Movimiento Personaje::getMovimiento() const { return movimiento; }
Casilla* Personaje::getCasillaActual() const { return casilla_actual;}



// MOVIMIENTO 
ResultadoMover Personaje::mover(Casilla& destino) {

    // 1. Condiciones del estado del personaje 
    if (!estaVivo()) return ResultadoMover::ILEGAL;
    if (getInmovilizado()) return ResultadoMover::ILEGAL;
    if (encarcelado) return ResultadoMover::ILEGAL;

    const Tablero& t = Partida::get_instance().tablero();
    // 2. Geometría decide si el movimiento es válido
    if (!Geometria::esMovimientoLegal(*casilla_actual, destino, *this, t)) return ResultadoMover::ILEGAL;

    // Quién ocupa el destino
    Personaje* ocupante = destino.getPersonaje();
    if (ocupante != nullptr && ocupante->getTurno() == turno) //No se puede mover 
        return ResultadoMover::ILEGAL;
    if (ocupante != nullptr && ocupante->getTurno() != turno) //Hay un choque
        return ResultadoMover::CHOQUE;

    // Ejecutar movimiento
    casilla_actual->setPersonaje(nullptr);
    destino.setPersonaje(this);
    casilla_actual = &destino;

    return ResultadoMover::OK;

}