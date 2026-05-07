#include "personaje.h"
#include "Casilla.h"

Personaje::Personaje(std::string nombre_, int vida_,
    Turno turno_, Movimiento movimiento_, stats arma_, Casilla& casillaInicial)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
    turno(turno_), movimiento(movimiento_), arma(arma_), casilla_actual(&casillaInicial)
{
	casilla_actual->setPersonaje(this);  // El personaje ocupa la casilla inicial
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

int Personaje::getPosX() const { return casilla_actual->getCol(); }
int Personaje::getPosY() const { return casilla_actual->getFila(); }
float Personaje::getPorcentajeVida() const { return (float)vida_actual / vida_Max; }
int Personaje::getVidaActual() const { return vida_actual; }
int Personaje::getVidaMax() const { return vida_Max; }
bool Personaje::getInmovilizado() const { return inmovilizado; }
Movimiento Personaje::getMovimiento() const { return movimiento; }
Casilla* Personaje::getCasillaActual() const { return casilla_actual;}

bool Personaje::mover(Casilla& destino) {  
    
    if (!estaVivo()) return false;
    if (inmovilizado) return false;
    if (encarcelado) return false;

    // La casilla de origen es la que decide si el movimiento es legal
    if (!casilla_actual->puedeMoverseA(destino, *this)) return false;

    //Limpiar la casilla de origen
    if (casilla_actual) casilla_actual->setPersonaje(nullptr);

    //Ocupar la casilla de destino
    casilla_actual->setPersonaje(nullptr);
    destino.setPersonaje(this);
    casilla_actual = &destino;
   

    return true;
}