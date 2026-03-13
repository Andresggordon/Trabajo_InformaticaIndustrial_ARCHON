#pragma once
#include <string>
#include "stats.h"
using namespace std;

enum class Turno { TURNO_DE_MAÑANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };

class Personaje {

public:
    Personaje(string nombre, int vida, int posX, int posY,
        Turno Turno, Movimiento movimiento, stats stats)
        : nombre(nombre), vida_Max(vida), vida_actual(vida),
        pos_x(pos_x), pos_y(pos_y), Turno(Turno),
        Movimiento(Movimiento), stats(stats), encarcelado(false) {
    }

    virtual ~Personaje() {}

    virtual void dibujarEnTablero() = 0;
    virtual void dibujarEnArena() = 0;
    virtual int  getRadioMovimiento() const = 0;

    void recibirDano(int cantidad) {
        vida_actual -= cantidad;
        if (vida_actual < 0) vida_actual = 0;
    }

    void curar(int cantidad) {
        vida_actual += cantidad;
        if (vida_actual > vida_Max) vida_actual = vida_Max;
    }

    bool estaVivo()        const { return vida_actual > 0; }
    bool estaEncarcelado() const { return encarcelado; }
    void setEncarcelado(bool v) { encarcelado = v; }


    string getNombre() const { return nombre; }
    int getVidaActual() const { return vida_actual; }
    int getVidaMax() const { return vida_Max; }
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }
    Turno getBando() const { return Turno; }
    Movimiento getMovimiento() const { return Movimiento; }
    stats getArma() const { return stats; }

    void setPosicion(int x, int y) { pos_x = x; pos_y = y; }

private:
    string nombre;
    Turno Turno;
    Movimiento Movimiento;
    stats stats;
    int vida_Max, vida_actual, pos_x, pos_y;
    bool encarcelado;

};

