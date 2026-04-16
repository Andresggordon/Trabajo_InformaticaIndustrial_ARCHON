#pragma once
#include "Personaje.h"
#include "habilidades_profes.h"
#include "Volador.h"
#include "Terrestre.h"

// TURNO DE MAÑANA
class Profesor_SS : public Volador {
public:
    Profesor_SS(int posX_, int posY_)
        : Volador("SanSegundo", 75, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Ondas de sonido", 20, 4, 3)){
    }
    Menu_habilidades menu;

    int getRadioMovimiento() const override { return 4; }

};

class Microprocesador_M : public Volador {
public:
    Microprocesador_M(int posX_, int posY_)
        : Volador("Microprocesador", 110, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Cadena de bits", 30, 1, 1)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Multimetro : public Terrestre {
public:
    Multimetro(int posX_, int posY_)
        : Terrestre("Multimetro", 50, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza rayos", 15, 5, 5)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class PLC : public Terrestre {
public:
    PLC(int posX_, int posY_)
        : Terrestre("PLC", 60, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza tuercas", 18, 4, 3)) {
    }

    int getRadioMovimiento() const override { return 1; }
};

class Fuente_de_tension_de_bateria : public Volador {
public:
    Fuente_de_tension_de_bateria(int posX_, int posY_)
        : Volador("Fuente de tension de bateria", 35, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Arco electrico", 8, 1, 6)) {
    }

    int getRadioMovimiento() const override { return 5; }
};

class Moto_electrica : public Volador {
public:
    Moto_electrica(int posX_, int posY_)
        : Volador("Moto electrica", 75, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Rayo", 20, 4, 3)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Copilot : public Volador {
public:
    Copilot(int posX_, int posY_)
        : Volador("Copilot", 110, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("C", 30, 1, 1)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Circuito_integrado_M : public Volador {
public:
    Circuito_integrado_M(int posX_, int posY_)
        : Volador("Circuito integrado", 55, posX_, posY_,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2)) {
    }

    int getRadioMovimiento() const override { return 2; }
};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(int posX_, int posY_)
        : Volador("MH", 35, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 8, 1, 6)) {
    }
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
};

class Microprocesador_T : public Volador {
public:
    Microprocesador_T(int posX_, int posY_)
        : Volador("Microprocesador", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Cadena de bits", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Osciloscopio : public Terrestre {
public:
    Osciloscopio(int posX_, int posY_)
        : Terrestre("Osciloscopio", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza senos", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 3; }
};

class Brazo_robot : public Terrestre {
public:
    Brazo_robot(int posX_, int posY_)
        : Terrestre("Brazo robot", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza tornillos", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 1; }
};

class Fuente_de_corriente : public Volador {
public:
    Fuente_de_corriente(int posX_, int posY_)
        : Volador("Fuente de corriente", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Arco eléctrico", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 5; }
};

class Moto_petrol : public Terrestre {
public:
    Moto_petrol(int posX_, int posY_)
        : Terrestre("Moto Petrol", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Gasolina", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Gemini : public Volador {
public:
    Gemini(int posX_, int posY_)
        : Volador("Gemini", 60, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("C++", 16, 3, 4)) {
    }

    int getRadioMovimiento() const override { return 4; }
};

class Circuito_integrado_T : public Volador {
public:
    Circuito_integrado_T(int posX_, int posY_)
        : Volador("Circuito integrado", 55, posX_, posY_,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2)) {
    }

    int getRadioMovimiento() const override { return 2; }
};