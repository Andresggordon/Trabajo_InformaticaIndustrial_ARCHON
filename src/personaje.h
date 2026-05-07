#pragma once
#include <string>
#include "stats.h"
#include <vector>
#include "dibujo_personajes.h"

// Declaración adelantada — no incluir Tablero.h aquí
class Tablero;
class Casilla;

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };

class Personaje {

public:
    // Constructor y Destructor
    Personaje(std::string nombre_, int vida_,
        Turno turno_, Movimiento movimiento_, stats arma_, Casilla& casillaInicial);
        
    virtual ~Personaje();

    // Método virtual puro
    virtual int getRadioMovimiento() const = 0;

    bool mover(Casilla& destino);

    // Lógica de salud
    void recibirDano(int cantidad_);
    void curar(int cantidad_);
    bool estaVivo() const;

    // Getters
    std::string getNombre() const;
    
    virtual std::string getNombreSprite() const = 0; // Es virtual puro porque cada personaje concreto sabe cuál es su PNG

    int getPosX() const;
    int getPosY() const;
    Casilla* getCasillaActual() const;

    float getPorcentajeVida() const;
    int getVidaActual() const;
    int getVidaMax() const;
    bool getInmovilizado() const;
    Movimiento getMovimiento() const;

    // Setters
    /*void setPosicion(int x_, int y_);
    void setCasillaActual(Casilla* c);*/

protected:
    std::string nombre;
    int vida_Max, vida_actual; 
    Turno turno;
    Movimiento movimiento;
    stats arma;
    bool encarcelado = false;
    bool inmovilizado = false;
    Casilla * casilla_actual;

};
