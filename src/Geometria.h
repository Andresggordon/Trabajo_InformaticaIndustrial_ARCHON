// -----------------------------------------------------------------------------------
// Geometria es el ente que conoce las reglas de movimiento del tablero.
// Ni Casilla ni Personaje saben de geometría: eso es responsabilidad de esta clase.
// Todos sus métodos son estáticos porque no necesita estado propio,
// solo trabaja con los datos del tablero y del personaje.
// -----------------------------------------------------------------------------------

#pragma once
#include <vector>

class Casilla;
class Personaje;
class Tablero;

class Geometria
{
public:

	//Devuelve las casillas a las que se puede mover el personaje dependiendo de su tipo, su radio y las casillas ya ocupadas 
	static std::vector<Casilla*> getCasillasAccesibles(
		const Personaje& p, const Tablero& t);

	//Determina si el movimiento que se va a hacer es legal
	static bool esMovimientoLegal(
		const Casilla& origen, const Casilla& destino, const Personaje& p,
		const Tablero& t);
private:

	//Sin tener en cuenta los obstáculos 
	static bool desplazamientoValido(
		const Casilla& origen, const Casilla& destino, const Personaje& p);

	//Para los terrestres 
	static bool caminoLibre(
		const Casilla& origen, const Casilla& destino, const Tablero& t);


};

