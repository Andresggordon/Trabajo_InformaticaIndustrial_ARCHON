#pragma once
#include "Personaje.h"
#include "habilidades_profes.h"
#include "Volador.h"
#include "Terrestre.h"

// TURNO DE MAÑANA
class Profesor_SS : public Volador {
public:
    Profesor_SS(Casilla& casillaInicial)
        : Volador("San Segundo", 225,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Ondas de sonido", 100, 6, 3),
            casillaInicial) {}
    Menu_habilidades menu;
    int getRadioMovimiento()  const override { return 4; }
    std::string getNombreSprite() const override { return "SanseAnimado1"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartass.png"; }

    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 0.0f; }

    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }

    int getFilasAnimacion() const override { return 2; }

    //virtual int getTiempoAnimacion() const override { return 45; } 

    Menu_habilidades* getMenu() override { return &menu; }
    bool esLider() const override { return true; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Risa.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }
};

class Microprocesador_M : public Volador {
public:
    Microprocesador_M(Casilla& casillaInicial)
        : Volador("Microprocesador", 225,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Cadena de bits", 75, 4, 1),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "MicroMAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamicrom.png"; }
    float getTamanoSprite() const override { return 90.0f; }
    float getOffsetX() const override { return 25.0f; }
    float getOffsetY() const override { return -12.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 200; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Microprocesadorcero.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }
};

class Multimetro : public Terrestre {
public:
    Multimetro(Casilla& casillaInicial)
        : Terrestre("Multimetro", 200,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza rayos", 50, 10, 5),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "MultimetroAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamulti.png"; }
 

    int getFramesIdle() const override { return 4; }
    float getOffsetX() const override { return 30.0f; }
    float getTamanoSprite() const override { return 70.0f; }
    int getTiempoAnimacion() const override { return 500; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/rayo.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class PLC : public Terrestre {
public:
    PLC(Casilla& casillaInicial)
        : Terrestre("PLC", 250,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza tuercas", 100, 1, 3),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 1; }
    std::string getNombreSprite() const override { return "PLCAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartaPLC.png"; }
 
    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }
    float getOffsetX() const override { return 95.0f; }
    float getOffsetY() const override { return 65.0f; }
    int getTiempoAnimacion() const override { return 1000; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Tuerca.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }


};

class Fuente_de_tension_de_bateria : public Volador {
public:
    Fuente_de_tension_de_bateria(Casilla& casillaInicial)
        : Volador("Fuente de tension de bateria", 250,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Arco electrico", 100, 2, 6),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 5; }
    std::string getNombreSprite() const override { return "Bateria"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteV.png"; }

    float getTamanoSprite() const override { return 60.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Descarga.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Moto_electrica : public Volador {
public:
    Moto_electrica(Casilla& casillaInicial)
        : Volador("Moto electrica", 225,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Rayo", 75, 4, 3),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MotoelectricAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamotoe.png"; }

    float getTamanoSprite() const override { return 60.0f; }

    int getFramesIdle() const override { return 8; }

    int getFilasAnimacion() const override { return 2; }

    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 0.0f; }
    int getTiempoAnimacion() const override { return 80; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/rayo.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }
};

class Copilot : public Volador {
public:
    Copilot(Casilla& casillaInicial)
        : Volador("Copilot", 250,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("C", 75, 6, 1),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "COPILOTAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartacopilot.png"; }
 
    int getFramesIdle() const override { return 8; }

    float getTamanoSprite() const override { return 60.0f; }
    float getOffsetY() const override { return -30.0f; }

    int getTiempoAnimacion() const override { return 150; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Ataqueletra.png";

        
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Circuito_integrado_M : public Volador {
public:
    Circuito_integrado_M(Casilla& casillaInicial)
        : Volador("Circuito integrado", 200,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Patas del micro", 50, 1, 2),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 2; }
    std::string getNombreSprite() const override { return "CIMAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartacim.png"; }

    float getTamanoSprite() const override { return 90.0f; }

    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 1200; }
    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return -20.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Pata.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }
};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(Casilla& casillaInicial)
        : Volador("MH", 225,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 75, 6, 6),
            casillaInicial) {}
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MHAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartamh.png"; }

    float getTamanoSprite() const override { return 80.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }

    int getFilasAnimacion() const override { return 2; }

    Menu_habilidades* getMenu() override { return &menu; }
    bool esLider() const override { return true; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/TizaVoladora.png";
    }
    float getVelocidadProyectil() const override { return 0.2f; }
};

class Microprocesador_T : public Volador {
public:
    Microprocesador_T(Casilla& casillaInicial)
        : Volador("Microprocesador", 225,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Cadena de bits", 75, 4, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "MicroTAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamicrot.png"; }
 
    float getTamanoSprite() const override { return 90.0f; }
    float getOffsetX() const override { return 25.0f; }
    float getOffsetY() const override { return -12.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 150; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/uno.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Osciloscopio : public Terrestre {
public:
    Osciloscopio(Casilla& casillaInicial)
        : Terrestre("Osciloscopio", 225,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza senos", 50, 10, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 3; }
    std::string getNombreSprite() const override { return "OsciloscopioAnimacion"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartaosci.png"; }
 
    int getFramesIdle() const override { return 8; }
    float getOffsetY() const override { return -15.0f; }
    int getTiempoAnimacion() const override { return 300; }

    float getTamanoSprite() const override { return 60.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Seno.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Brazo_robot : public Terrestre {
public:
    Brazo_robot(Casilla& casillaInicial)
        : Terrestre("Brazo robot", 250,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza tornillos", 100, 1, 4), casillaInicial) {
    }

    int getRadioMovimiento() const override { return 1; }
    std::string getNombreSprite() const override { return "BRAZOANIMADO3"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartarobot.png"; }


    int getFramesIdle() const override { return 17; }
    
    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return 30.0f; }

    int getTiempoAnimacion() const override {return 300;}

    float getTamanoSprite() const override { return 80.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Tornillo.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Fuente_de_corriente : public Volador {
public:
    Fuente_de_corriente(Casilla& casillaInicial)
        : Volador("Fuente de corriente", 250,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Arco eléctrico", 100, 2, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 5; }
    std::string getNombreSprite() const override { return "FuenteCorrienteAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteI.png"; }
 
    float getTamanoSprite() const override { return 70.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Descarga.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }

};

class Moto_petrol : public Terrestre {
public:
    Moto_petrol(Casilla& casillaInicial)
        : Terrestre("Moto Petrol", 200,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Gasolina", 100, 4, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MotopetrolAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamotop.png"; }


    float getTamanoSprite() const override { return 60.0f; }
    int getFramesIdle() const override { return 10; }

    int getFilasAnimacion() const override { return 2; }


    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 10.0f; }

    int getTiempoAnimacion() const override { return 100; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/gasolina.png";
    }

    float getVelocidadProyectil() const override { return 0.5f; }
};

class Gemini : public Volador {
public:
    Gemini(Casilla& casillaInicial)
        : Volador("Gemini", 250,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("C++", 75, 6, 4),
            casillaInicial) {
    }

    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "GEMINIAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartagemini.png"; }

    float getTamanoSprite() const override { return 55.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 150 ; }

    float getOffsetX() const override { return 5.0f; }
    float getOffsetY() const override { return -22.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/C++.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }



};

class Circuito_integrado_T : public Volador {
public:
    Circuito_integrado_T(Casilla& casillaInicial)
        : Volador("Circuito integrado", 200,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Patas del micro", 50, 1, 2),
            casillaInicial) {}

    int getRadioMovimiento() const override { return 2; }
    std::string getNombreSprite() const override { return "CITAnimado"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartacit.png"; }
    float getTamanoSprite() const override { return 90.0f; }

    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 1200; }
    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return -20.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Pata.png";
    }
    float getVelocidadProyectil() const override { return 0.5f; }
};