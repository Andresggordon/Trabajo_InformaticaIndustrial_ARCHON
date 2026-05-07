#pragma once
#include "Personaje.h"
#include "habilidades_profes.h"
#include "Volador.h"
#include "Terrestre.h"

// TURNO DE MAÑANA
class Profesor_SS : public Volador {
public:
    Profesor_SS(Casilla& casillaInicial)
        : Volador("San Segundo", 75,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Ondas de sonido", 20, 4, 3),
            casillaInicial) {}
    Menu_habilidades menu;
    int getRadioMovimiento()  const override { return 4; }
    std::string getNombreSprite() const override { return "SanSegundo"; }
};

class Microprocesador_M : public Volador {
public:
    Microprocesador_M(Casilla& casillaInicial)
        : Volador("Microprocesador", 110,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Cadena de bits", 30, 1, 1),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "MicroprocesadorM"; }


};

class Multimetro : public Terrestre {
public:
    Multimetro(Casilla& casillaInicial)
        : Terrestre("Multimetro", 50,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza rayos", 15, 5, 5),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "Multimetro"; }

};

class PLC : public Terrestre {
public:
    PLC(Casilla& casillaInicial)
        : Terrestre("PLC", 60,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza tuercas", 18, 4, 3),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 1; }
    std::string getNombreSprite() const override { return "PLC"; }

};

class Fuente_de_tension_de_bateria : public Volador {
public:
    Fuente_de_tension_de_bateria(Casilla& casillaInicial)
        : Volador("Fuente de tension de bateria", 35,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Arco electrico", 8, 1, 6),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 5; }
    std::string getNombreSprite() const override { return "Bateria"; }

};

class Moto_electrica : public Volador {
public:
    Moto_electrica(Casilla& casillaInicial)
        : Volador("Moto electrica", 75,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Rayo", 20, 4, 3),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MOTOELECTRIC"; }

};

class Copilot : public Volador {
public:
    Copilot(Casilla& casillaInicial)
        : Volador("Copilot", 110,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("C", 30, 1, 1),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "COPILOT"; }

};

class Circuito_integrado_M : public Volador {
public:
    Circuito_integrado_M(Casilla& casillaInicial)
        : Volador("Circuito integrado", 55,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 2; }
    std::string getNombreSprite() const override { return "CINTEGRADOM"; }

};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(Casilla& casillaInicial)
        : Volador("MH", 35,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 8, 1, 6), 
            casillaInicial) {
    }
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MH"; }

};

class Microprocesador_T : public Volador {
public:
    Microprocesador_T(Casilla& casillaInicial)
        : Volador("Microprocesador", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Cadena de bits", 16, 3, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "MicroprocesadorT"; }

};

class Osciloscopio : public Terrestre {
public:
    Osciloscopio(Casilla& casillaInicial)
        : Terrestre("Osciloscopio", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza senos", 16, 3, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "OSCILOSCOPIO"; }

};

class Brazo_robot : public Terrestre {
public:
    Brazo_robot(Casilla& casillaInicial)
        : Terrestre("Brazo robot", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza tornillos", 16, 3, 4), casillaInicial) {
    }

    int getRadioMovimiento() const override { return 1; }
    std::string getNombreSprite() const override { return "BRAZOROBOT"; }

};

class Fuente_de_corriente : public Volador {
public:
    Fuente_de_corriente(Casilla& casillaInicial)
        : Volador("Fuente de corriente", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Arco eléctrico", 16, 3, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 5; }
    std::string getNombreSprite() const override { return "FUENTECORRIENTE"; }

};

class Moto_petrol : public Terrestre {
public:
    Moto_petrol(Casilla& casillaInicial)
        : Terrestre("Moto Petrol", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Gasolina", 16, 3, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MOTOPETROL"; }

};

class Gemini : public Volador {
public:
    Gemini(Casilla& casillaInicial)
        : Volador("Gemini", 60,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("C++", 16, 3, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "GEMINI"; }

};

class Circuito_integrado_T : public Volador {
public:
    Circuito_integrado_T(Casilla& casillaInicial)
        : Volador("Circuito integrado", 55,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Patas del micro", 22, 6, 2),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 2; }
    std::string getNombreSprite() const override { return "CINTEGRADOT"; }

};