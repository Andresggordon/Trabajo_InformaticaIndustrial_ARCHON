#pragma once
#include <string>
#include "stats.h"
using std::string;

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };

class Personaje {

public:

    Personaje(string nombre_, int vida_, int posX_, int posY_,
        Turno turno_, Movimiento movimiento_, stats arma_)
        : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
        pos_x(posX_), pos_y(posY_), turno(turno_),
        movimiento(movimiento_), arma(arma_), encarcelado(false) {
    }

    virtual ~Personaje() {}
    // Destructor virtual — obligatorio cuando se usa herencia con punteros

    virtual int getRadioMovimiento() const = 0;

    void recibirDano(int cantidad_) {
        vida_actual -= cantidad_;
        if (vida_actual < 0) vida_actual = 0;
    }

    void curar(int cantidad_) {
        vida_actual += cantidad_;
        if (vida_actual > vida_Max) vida_actual = vida_Max;
    }

    bool estaVivo() const { return vida_actual > 0; }
    bool estaEncarcelado() const { return encarcelado; }
    void setEncarcelado(bool v) { encarcelado = v; }

    string getNombre() const { return nombre; }
    int getVidaActual() const { return vida_actual; }
    int getVidaMax() const { return vida_Max; }
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }
    Turno getTurno() const { return turno; }
    Movimiento  getMovimiento() const { return movimiento; }
    stats getArma() const { return arma; }

    void setPosicion(int x_, int y_) { pos_x = x_; pos_y = y_; }

protected:
    string nombre;
    int         vida_Max, vida_actual;
    int         pos_x, pos_y;
    Turno       turno;      
    Movimiento  movimiento;  
    stats       arma;
    bool        encarcelado;
};