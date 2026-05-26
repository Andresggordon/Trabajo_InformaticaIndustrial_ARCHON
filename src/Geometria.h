/**
 * @file Geometria.h
 * 
 * @brief Clase estática que gestiona las reglas lógicas y restricciones de movimiento del tablero.
 * 
 * * @details Modela la lógica espacial del juego abstrayendo al Tablero y a los Personajes de
 * los cálculos geométricos. Evalúa las trayectorias de los personajes según su tipo de
 * desplazamiento (Tierra, Aire, Teletransporte), calcula casillas disponibles y verifica
 * colisiones u obstáculos intermedios. Todos sus métodos son estáticos al carecer de estado propio.
 * 
 * */

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

