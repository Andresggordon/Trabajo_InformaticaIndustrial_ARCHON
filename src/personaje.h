#pragma once
#include <string>
#include "stats.h"
#include <vector>

// Declaración adelantada — no incluir Tablero.h aquí
class Tablero;

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };

class Personaje {
public:
    // Constructor y Destructor
    Personaje(std::string nombre_, int vida_, int posX_, int posY_,
        Turno turno_, Movimiento movimiento_, stats arma_, Tablero& tab);
    virtual ~Personaje();

    // Métodos virtuales puros
    virtual int getRadioMovimiento() const = 0;
    virtual bool esMovimientoLegal(int destinoX, int destinoY) const = 0;

    bool mover(int destinoX, int destinoY);

    // Lógica de salud
    void recibirDano(int cantidad_);
    void curar(int cantidad_);
    bool estaVivo() const;

    // Getters
    std::string getNombre() const;
    int getPosX() const;
    int getPosY() const;
    float getPorcentajeVida() const;
    int getVidaActual() const;
    int getVidaMax() const;
    bool getInmovilizado() const;
    Movimiento getMovimiento() const;

    // Setters
    void setPosicion(int x_, int y_);

    Turno getTurno()const; //Funcion para determinar los turnos de movimiento

protected:
    Tablero& tablero_;  // referencia al tablero compartido
    std::string nombre;
    int vida_Max, vida_actual;
    int pos_x, pos_y;
    Turno turno;
    Movimiento movimiento;
    stats arma;
    bool encarcelado = false;
    bool inmovilizado = false;
};