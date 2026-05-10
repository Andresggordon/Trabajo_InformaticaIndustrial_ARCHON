#pragma once
#include <string>
#include "stats.h"
#include <vector>
#include "dibujo_personajes.h"
#include "habilidades_profes.h"

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
    virtual float getTamanoSprite() const = 0; //Modificar el tamaño de cada sprite individualmente
    virtual Menu_habilidades* getMenu() { return nullptr; } //Metodo virtual para abrir el menu de habilidades

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
    bool getInmovilizado() const { return turnos_inmovilizado > 0; }
    Movimiento getMovimiento() const;

    Turno getTurno() const { return turno; }

    // Setters
    /*void setPosicion(int x_, int y_);*/
    void setCasillaActual(Casilla* c);
    void setVida(int v) { vida_actual = v; }
    void setInmovilizado(bool b) { turnos_inmovilizado = b ? 1 : 0; } // La imnovilización dura 1 turno
    void decrementarInmovilizacion() { if (turnos_inmovilizado > 0) turnos_inmovilizado--; }

protected:
    std::string nombre;
    int vida_Max, vida_actual; 
    Turno turno;
    Movimiento movimiento;
    stats arma;
    bool encarcelado = false;
    int turnos_inmovilizado = 0;
    Casilla * casilla_actual;

};
