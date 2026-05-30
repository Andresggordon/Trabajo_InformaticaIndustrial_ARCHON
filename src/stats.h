/**
 * @file stats.h
 * @brief Contenedor ligero para los atributos de combate de las piezas.
 *
 * @details Define un paquete inmutable de estadísticas de combate (Daño, Alcance,
 * Velocidad del proyectil y Nombre del ataque). Se utiliza principalmente para separar
 * los parámetros del arma de los atributos inherentes al personaje, permitiendo una
 * arquitectura más modular a la hora de resolver los enfrentamientos en la Arena de Combate.
 */

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
