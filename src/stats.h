#pragma once
#include <string>
using std::string;

class stats {
public:
    stats(string nombre, int dano, int alcance, int velocidad)
        : nombre(nombre), dano(dano), alcance(alcance), velocidad(velocidad) {
    }
    string getNombre() const { return nombre; }
    int getDanio() const { return dano; }
    int getAlcance() const { return alcance; }
    int getVelocidad() const { return velocidad; }

private:
    string nombre;
    int dano;
    int alcance;
    int velocidad;
};
