#pragma once
#include "personaje.h"

class Volador : public Personaje {
public:
	//Constructor heredado porque no es específico
	// luego en cada personaje sí
	using Personaje::Personaje; 
};