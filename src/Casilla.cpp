#include "Casilla.h"
#include "personaje.h"

Casilla::Casilla() : estado(EstadoCasilla::BLANCA_FIJA), personaje(nullptr), fila_(0), col_(0) {}

void Casilla::setPosicion(int fila, int col) {
	fila_ = fila;
	col_ = col;
}

int Casilla::getFila() const { return fila_; }
int Casilla::getCol() const { return col_; }

void Casilla::agregarCasillaVecina(Casilla* c, int dx, int dy) {
	casillasvecinas.push_back({ c, dx, dy });
	// push_back añade un nuevo elemento al final del vector.
	// Construye una CasillaVecina con la casilla y su desplazamiento.

}


//	----- LÓGICA DEL MOVIMIENTO -------

bool Casilla::puedeMoverseA(const Casilla& c_destino, const Personaje& p) const {
	int dx = abs(c_destino.getCol() - col_);
	int dy = abs(c_destino.getFila() - fila_);
	int radio = p.getRadioMovimiento();

	if (p.getMovimiento() == Movimiento::TIERRA) {
		//Movimiento terrestre solo horizontal o vertical
		return (dx == 0 || dy == 0) && (dx + dy <= radio);
	}
	else if (p.getMovimiento() == Movimiento::AIRE) {
		//Movimiento aéreo puede ser en cualquier dirección
		return ((dx <= radio) && (dy <= radio)); //Este debe moverse entre casillas de una en una, podiendo colisionar con otros aereos
	}
	else if (p.getMovimiento() == Movimiento::TELETRANSPORTE) {
		//Teletransporte puede moverse a cualquier casilla dentro de su radio
		return ((dx <= radio) && (dy <= radio)); //De momento igual pero, este debe atravesar los objetos
				
	}

	return false;
}

// ------ ESTADO DE LA CASILLA ---------

EstadoCasilla Casilla::getEstado() const { return estado; }
void Casilla::setEstado(EstadoCasilla e) { estado = e; }

// ------ PERSONAJE QUE OCUPA LA CASILLA ---------
Personaje* Casilla::getPersonaje() const { return personaje; }
void Casilla::setPersonaje(Personaje* p) { personaje = p; }