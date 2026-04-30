#include "Casilla.h"

Casilla::Casilla() : estado(EstadoCasilla::BLANCA_FIJA), personaje(nullptr) {}

EstadoCasilla Casilla::getEstado() const { return estado; }
void Casilla::setEstado(EstadoCasilla e) { estado = e; }

Personaje* Casilla::getPersonaje() const { return personaje; }
void Casilla::setPersonaje(Personaje* p) { personaje = p; }