/**
 * @file Casilla.cpp
 * @brief Implementación de la clase Casilla. Define los métodos de acceso y modificación de su estado interno.
 */

#include "Casilla.h"
#include "personaje.h"

Casilla::Casilla() : estado(EstadoCasilla::BLANCA_FIJA), personaje(nullptr), fila_(0), col_(0) {}

void Casilla::setPosicion(int fila, int col) {
	fila_ = fila;
	col_ = col;
}

int Casilla::getFila() const { return fila_; }
int Casilla::getCol() const { return col_; }

EstadoCasilla Casilla::getEstado() const { return estado; }
void Casilla::setEstado(EstadoCasilla e) { estado = e; }

// ------ PERSONAJE QUE OCUPA LA CASILLA ---------
Personaje* Casilla::getPersonaje() const { return personaje; }
void Casilla::setPersonaje(Personaje* p) { personaje = p; }