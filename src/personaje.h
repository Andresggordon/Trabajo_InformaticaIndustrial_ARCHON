#pragma once
#include <string>
#include "stats.h"
#include <vector>

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };

class Personaje {
public:
    // Constructor y Destructor
    Personaje(std::string nombre_, int vida_, int posX_, int posY_,
        Turno turno_, Movimiento movimiento_, stats arma_);
    virtual ~Personaje();

    // Métodos virtuales puros (obligan a las clases hijas a implementarlos)
    virtual int getRadioMovimiento() const = 0;

    // Movimiento inteligente
    std::vector<Casilla>> casillasValidas(int ancho, int largo) const; // Poner la estructura casilla aqui

    // Lógica de salud
    void recibirDano(int cantidad_);
    void curar(int cantidad_);
    bool estaVivo() const;

    // Getters para que otros consulten el estado (pero no lo modifiquen)
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

protected:
    std::string nombre;
    int vida_Max, vida_actual;
    int pos_x, pos_y;
    Turno turno;
    Movimiento movimiento;
    stats arma;
    bool encarcelado = false;
    bool inmovilizado = false;
};