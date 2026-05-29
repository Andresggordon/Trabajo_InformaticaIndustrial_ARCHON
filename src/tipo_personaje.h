#pragma once
#include "Personaje.h"
#include "habilidades_profes.h"
#include "Volador.h"
#include "Terrestre.h"

// TURNO DE MAÑANA
class Profesor_SS : public Volador {
public:
    // Un personaje se define como TIPO -> Nombre, Vida max, Turno, Movimiento, STATS (ataque), Velocidad de movimiento,
    Profesor_SS(Casilla& casillaInicial)
        : Volador("San Segundo", 250,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Ondas de sonido", 100, 6, 2),  
            5, // Velocidad de movimiento en la arena
            2, //Radio de alcance en el tablero
            casillaInicial) {}
    Menu_habilidades menu;

    std::string getNombreSprite() const override { return "SanseAnimado1"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartass.png"; }

    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 0.0f; }

    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }

    int getFilasAnimacion() const override { return 2; }


    Menu_habilidades* getMenu() override { return &menu; }
    bool esLider() const override { return true; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Risa.png";
    }
};

class Microprocesador_M : public Volador {
public:
    Microprocesador_M(Casilla& casillaInicial)
        : Volador("Microprocesador", 200,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Cadena de bits", 75, 4, 2),
            6, // Velocidad de movimiento
            2, //Radio de movimiento
            casillaInicial) {}

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
    
};

class Multimetro : public Terrestre {
public:
    Multimetro(Casilla& casillaInicial)
        : Terrestre("Multimetro", 100,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza rayos", 50, 10, 2),
            2, // Velocidad de movimiento
            3, //Radio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "MultimetroAnimado"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartamulti.png"; }


    int getFramesIdle() const override { return 4; }
    float getOffsetX() const override { return 30.0f; }
    float getTamanoSprite() const override { return 70.0f; }
    int getTiempoAnimacion() const override { return 500; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/rayo.png";
    }
    

};

class PLC : public Terrestre {
public:
    PLC(Casilla& casillaInicial)
        : Terrestre("PLC", 500,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Lanza tuercas", 100, 1, 1),
            3, // Velocidad de movimiento
            1, //Radio de movimiento
            casillaInicial) {}

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
    
};

class Fuente_de_tension_de_bateria : public Terrestre {
public:
    Fuente_de_tension_de_bateria(Casilla& casillaInicial)
        : Terrestre("Fuente de tension de bateria", 350,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Arco electrico", 75, 2, 2),
            3, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "Bateria"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteV.png"; }

    float getTamanoSprite() const override { return 60.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Descarga.png";
    }
    
};

class Moto_electrica : public Volador {
public:
    Moto_electrica(Casilla& casillaInicial)
        : Volador("Moto electrica", 225,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("Rayo", 50, 4, 2),
            8, // Velocidad de movimiento
            3, //Rdio de movimiento
            casillaInicial) {}

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
    
};

class Copilot : public Volador {
public:
    Copilot(Casilla& casillaInicial)
        : Volador("Copilot", 150,
            Turno::TURNO_DE_MANANA,
            Movimiento::AIRE,
            stats("C", 75, 6, 3),
            7, // Velocidad de movimiento
            4, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "COPILOTAnimado"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartacopilot.png"; }

    int getFramesIdle() const override { return 8; }

    float getTamanoSprite() const override { return 60.0f; }
    float getOffsetY() const override { return -30.0f; }

    int getTiempoAnimacion() const override { return 150; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Ataqueletra.png";
    }
    
};

class Circuito_integrado_M : public Terrestre {
public:
    Circuito_integrado_M(Casilla& casillaInicial)
        : Terrestre("Circuito integrado", 250,
            Turno::TURNO_DE_MANANA,
            Movimiento::TIERRA,
            stats("Patas del micro", 75, 1, 2),
            4, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

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
    
};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(Casilla& casillaInicial)
        : Volador("MH", 250,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 100, 6, 2),
            5, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

    Menu_habilidades menu;
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
    
};

class Microprocesador_T : public Volador {
public:
    Microprocesador_T(Casilla& casillaInicial)
        : Volador("Microprocesador", 200,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Cadena de bits", 75, 4, 1),
            6, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

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
    
};

class Osciloscopio : public Terrestre {
public:
    Osciloscopio(Casilla& casillaInicial)
        : Terrestre("Osciloscopio", 100,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza senos", 50, 10, 2),
            2, // Velocidad de movimiento
            3, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "OsciloscopioAnimacion"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartaosci.png"; }

    int getFramesIdle() const override { return 8; }
    float getOffsetY() const override { return -15.0f; }
    int getTiempoAnimacion() const override { return 300; }

    float getTamanoSprite() const override { return 60.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Seno.png";
    }
    

};

class Brazo_robot : public Terrestre {
public:
    Brazo_robot(Casilla& casillaInicial)
        : Terrestre("Brazo robot", 500,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Lanza tornillos", 100, 1, 1),
            3, // Velocidad de movimiento
            1, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "BRAZOANIMADO3"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartarobot.png"; }


    int getFramesIdle() const override { return 17; }

    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 300; }

    float getTamanoSprite() const override { return 80.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Tornillo.png";
    }
    

};

class Fuente_de_corriente : public Terrestre {
public:
    Fuente_de_corriente(Casilla& casillaInicial)
        : Terrestre("Fuente de corriente", 375,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Arco eléctrico", 75, 2, 2),
            3, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "FuenteCorrienteAnimada"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteI.png"; }

    float getTamanoSprite() const override { return 70.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/Descarga.png";
    }
    

};

class Moto_petrol : public Volador {
public:
    Moto_petrol(Casilla& casillaInicial)
        : Volador("Moto Petrol", 225,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Gasolina", 50, 4, 2),
            8, // Velocidad de movimiento
            3, //Rdio de movimiento
            casillaInicial) {}

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

    
};

class Gemini : public Volador {
public:
    Gemini(Casilla& casillaInicial)
        : Volador("Gemini", 150,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("C++", 75, 6, 3),
            7, // Velocidad de movimiento
            4, //Rdio de movimiento
            casillaInicial) {}

    std::string getNombreSprite() const override { return "GEMINIAnimado"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartagemini.png"; }

    float getTamanoSprite() const override { return 55.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 150; }

    float getOffsetX() const override { return 5.0f; }
    float getOffsetY() const override { return -22.0f; }

    std::string getNombreProyectil() const override {
        return "assets/menu_imagenes/C++.png";
    }
    

};

class Circuito_integrado_T : public Terrestre {
public:
    Circuito_integrado_T(Casilla& casillaInicial)
        : Terrestre("Circuito integrado", 250,
            Turno::TURNO_DE_TARDE,
            Movimiento::TIERRA,
            stats("Patas del micro", 75, 1, 2),
            4, // Velocidad de movimiento
            2, //Rdio de movimiento
            casillaInicial) {}

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
    
};