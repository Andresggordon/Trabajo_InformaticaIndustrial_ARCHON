#pragma once
#include "Personaje.h"
#include "habilidades_profes.h"
#include "Volador.h"
#include "Terreste.h"

// TURNO DE MAÑANA
class Profesor_SS : public Personaje {
public:
    Profesor_SS(int posX_, int posY_)
        : Personaje("SanSegundo", 75, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Ondas de sonido", 20, 4, 3)){
    }
    Menu_habilidades menu;

    int getRadioMovimiento() const override { return 4; }

};

class Microprocesador_M : public Personaje {
public:
    Microprocesador_M(int posX_, int posY_)
        : Personaje("Microprocesador", 110, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Cadena de bits", 30, 1, 1)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Multimetro : public Personaje {
public:
    Multimetro(int posX_, int posY_)
        : Personaje("Multimetro", 50, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza rayos", 15, 5, 5)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class PLC : public Personaje {
public:
    PLC(int posX_, int posY_)
        : Personaje("PLC", 60, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza tuercas", 18, 4, 3)) {
    }

    int getRadioMovimiento() const override { return 1; }
};

class Fuente_de_tension_de_bateria : public Personaje {
public:
    Fuente_de_tension_de_bateria(int posX_, int posY_)
        : Personaje("Fuente de tension de bateria", 35, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Arco electrico", 8, 1, 6)) {
    }

    int getRadioMovimiento() const override { return 5; }
};

class Moto_electrica : public Personaje {
public:
    Moto_electrica(int posX_, int posY_)
        : Personaje("Moto electrica", 75, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Rayo", 20, 4, 3)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Copilot : public Personaje {
public:
    Copilot(int posX_, int posY_)
        : Personaje("Copilot", 110, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("C", 30, 1, 1)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Circuito_integrado_M : public Personaje {
public:
    Circuito_integrado_M(int posX_, int posY_)
        : Personaje("Circuito integrado", 55, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2)) {
    }

    int getRadioMovimiento() const override { return 2; }
};

//TURNO DE TARDE 

class Profesor_MH : public Personaje {
public:
    Profesor_MH(int posX_, int posY_)
        : Personaje("MH", 35, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 8, 1, 6)) {
    }
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
};

class Microprocesador_T : public Personaje {
public:
    Microprocesador_T(int posX_, int posY_)
        : Personaje("Microprocesador", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Cadena de bits", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Osciloscopio : public Personaje{
public:
    Osciloscopio(int posX_, int posY_)
        : Personaje("Osciloscopio", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza senos", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Brazo_robot : public Personaje{
public:
    Brazo_robot(int posX_, int posY_)
        : Personaje("Brazo robot", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza tornillos", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 1; }
};

class Fuente_de_corriente : public Personaje{
public:
    Fuente_de_corriente(int posX_, int posY_)
        : Personaje("Fuente de corriente", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Arco eléctrico", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 5; }
};

class Moto_petrol : public Personaje{
public:
    Moto_petrol(int posX_, int posY_)
        : Personaje("Moto Petrol", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Gasolina", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Gemini : public Personaje {
public:
    Gemini(int posX_, int posY_)
        : Personaje("Gemini", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("C++", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Circuito_integrado_T : public Personaje {
public:
    Circuito_integrado_T(int posX_, int posY_)
        : Personaje("Circuito integrado", 55, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2)) {
    }

    int getRadioMovimiento() const override { return 2; }
};