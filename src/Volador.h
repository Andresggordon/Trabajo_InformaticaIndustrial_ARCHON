/**
 * @file Volador.h
 * @brief Clase intermedia para la categorización de personajes aéreos.
 *
 * @details Hereda directamente de `Personaje` y agrupa semánticamente a todas las unidades
 * que tienen el atributo de movimiento definido como `AIRE`. Aunque no
 * implementa lógica propia, sirve como estructura de clasificación para facilitar el polimorfismo
 * y permitir futuras especializaciones exclusivas de las unidades voladoras.
 */

#pragma once
#include "personaje.h"

class Volador : public Personaje {
public:
	//Constructor heredado porque no es específico
	// luego en cada personaje sí
	using Personaje::Personaje; 
};