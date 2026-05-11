#pragma once
#include <string>
#include "stats.h"
#include "habilidades_profes.h"

class Casilla;

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE, TELETRANSPORTE };
enum class ResultadoMover { OK,ILEGAL,CHOQUE};

class Personaje {
public:
    Personaje(std::string nombre_, int vida_,
        Turno turno_, Movimiento movimiento_,
        stats arma_, Casilla& casillaInicial);

    virtual ~Personaje();


    // Métodos virtuales puros — cada subclase los implementa
    virtual int         getRadioMovimiento() const = 0;
    virtual std::string getNombreSprite()    const = 0;
    virtual float       getTamanoSprite()    const = 0;
   

    virtual Menu_habilidades* getMenu() { return nullptr; }

    virtual int getFramesIdle() const { return 1; } // por defecto 1, no es puro

    // Offset de cada sprite
    virtual float getOffsetX() const { return 0.0f; }
    virtual float getOffsetY() const { return 0.0f; }

    ResultadoMover mover(Casilla& destino);

    void recibirDano(int cantidad_);
    void curar(int cantidad_);
    bool estaVivo() const;

    std::string getNombre()          const;
    int         getPosX()            const;
    int         getPosY()            const;
    Casilla* getCasillaActual()   const;
    float       getPorcentajeVida()  const;
    int         getVidaActual()      const;
    int         getVidaMax()         const;
    bool        getInmovilizado()    const { return turnos_inmovilizado > 0; }
    Movimiento  getMovimiento()      const;
    Turno       getTurno()           const { return turno; }

    void setCasillaActual(Casilla* c);
    void setVida(int v) { vida_actual = v; }
    void setInmovilizado(bool b) { turnos_inmovilizado = b ? 1 : 0; }
    void decrementarInmovilizacion() { if (turnos_inmovilizado > 0) turnos_inmovilizado--; }

protected:
    std::string nombre;
    int         vida_Max, vida_actual;
    Turno       turno;
    Movimiento  movimiento;
    stats       arma;
    bool        encarcelado = false;
    int         turnos_inmovilizado = 0;
    Casilla* casilla_actual;
};