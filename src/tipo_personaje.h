<<<<<<< HEAD
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
    std::string getNombreSprite() const override { return "SanseAnimado"; }

    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 20.0f; }

    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }

    Menu_habilidades* getMenu() override { return &menu; }

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
    float getTamanoSprite() const override { return 50.0f; }



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
    std::string getNombreSprite() const override { return "AnimacionMultimetro"; }

    int getFramesIdle() const override { return 4; }
    float getOffsetX() const override { return 30.0f; }
    float getTamanoSprite() const override { return 60.0f; }


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
    float getTamanoSprite() const override { return 60.0f; }


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
    float getTamanoSprite() const override { return 60.0f; }


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
    float getTamanoSprite() const override { return 60.0f; }


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
    std::string getNombreSprite() const override { return "COPILOTAnimado"; }
    int getFramesIdle() const override { return 8; }

    float getTamanoSprite() const override { return 60.0f; }
    float getOffsetY() const override { return -30.0f; }

    int getTiempoAnimacion() const override { return 150; }



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
    float getTamanoSprite() const override { return 55.0f; }



};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(Casilla& casillaInicial)
        : Volador("MH", 35,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 8, 1, 6),
            casillaInicial) {}
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MHAnimado"; }
    float getTamanoSprite() const override { return 80.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }

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
    float getTamanoSprite() const override { return 50.0f; }



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
    std::string getNombreSprite() const override { return "OsciloscopioAnimacion"; }
    int getFramesIdle() const override { return 8; }
    float getOffsetY() const override { return -15.0f; }
    int getTiempoAnimacion() const override { return 300; }

    float getTamanoSprite() const override { return 60.0f; }



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
    std::string getNombreSprite() const override { return "BRAZOANIMADO2"; }

    int getFramesIdle() const override { return 17; }
    float getOffsetY() const override { return 10.0f; }
    int getTiempoAnimacion() const override {return 500;}

    float getTamanoSprite() const override { return 90.0f; }



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
    std::string getNombreSprite() const override { return "FuenteCorrienteAnimada"; }
    float getTamanoSprite() const override { return 70.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }



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
    float getTamanoSprite() const override { return 60.0f; }



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
    std::string getNombreSprite() const override { return "GEMINIAnimado"; }
    float getTamanoSprite() const override { return 55.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 100 ; }
    float getOffsetY() const override { return -20.0f; }





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
    float getTamanoSprite() const override { return 50.0f; }



=======
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
    std::string getNombreSprite() const override { return "SanseAnimado"; }
    std::string getNombreCarta()  const override { return "assets/cartas/cartass.png"; }

    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 20.0f; }

    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }

    Menu_habilidades* getMenu() override { return &menu; }

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
    std::string getNombreSprite() const override { return "MicroMAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamicrom.png"; }
    float getTamanoSprite() const override { return 90.0f; }
    float getOffsetX() const override { return 25.0f; }
    float getOffsetY() const override { return -12.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 200; }



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
    std::string getNombreSprite() const override { return "MultimetroAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamulti.png"; }
 

    int getFramesIdle() const override { return 4; }
    float getOffsetX() const override { return 30.0f; }
    float getTamanoSprite() const override { return 70.0f; }
    int getTiempoAnimacion() const override { return 500; }



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
    std::string getNombreSprite() const override { return "PLCAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartaPLC.png"; }
 
    float getTamanoSprite() const override { return 65.0f; }

    int getFramesIdle() const override { return 8; }
    float getOffsetX() const override { return 95.0f; }
    float getOffsetY() const override { return 65.0f; }
    int getTiempoAnimacion() const override { return 1000; }




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
std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteV.png"; }

    float getTamanoSprite() const override { return 60.0f; }


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
    std::string getNombreSprite() const override { return "MotoEAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamotoe.png"; }

    float getTamanoSprite() const override { return 60.0f; }

    int getFramesIdle() const override { return 8; }
    float getOffsetX() const override { return 35.0f; }
    float getOffsetY() const override { return 0.0f; }
    int getTiempoAnimacion() const override { return 80; }
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
    std::string getNombreSprite() const override { return "COPILOTAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartacopilot.png"; }
 
    int getFramesIdle() const override { return 8; }

    float getTamanoSprite() const override { return 60.0f; }
    float getOffsetY() const override { return -30.0f; }

    int getTiempoAnimacion() const override { return 150; }



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
    std::string getNombreSprite() const override { return "CIMAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartacim.png"; }

    float getTamanoSprite() const override { return 90.0f; }

    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 1200; }
    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return -20.0f; }

};

//TURNO DE TARDE 

class Profesor_MH : public Volador {
public:
    Profesor_MH(Casilla& casillaInicial)
        : Volador("MH", 35,
            Turno::TURNO_DE_TARDE,
            Movimiento::AIRE,
            stats("Tizas", 8, 1, 6),
            casillaInicial) {}
    Menu_habilidades menu;
    int getRadioMovimiento() const override { return 4; }
    std::string getNombreSprite() const override { return "MHAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartamh.png"; }

    float getTamanoSprite() const override { return 80.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }

    Menu_habilidades* getMenu() override { return &menu; }
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
    std::string getNombreSprite() const override { return "MicroTAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamicrot.png"; }
 
    float getTamanoSprite() const override { return 90.0f; }
    float getOffsetX() const override { return 25.0f; }
    float getOffsetY() const override { return -12.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 150; }



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
    std::string getNombreSprite() const override { return "OsciloscopioAnimacion"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartaosci.png"; }
 
    int getFramesIdle() const override { return 8; }
    float getOffsetY() const override { return -15.0f; }
    int getTiempoAnimacion() const override { return 300; }

    float getTamanoSprite() const override { return 60.0f; }



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
    std::string getNombreSprite() const override { return "BRAZOANIMADO2"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartarobot.png"; }


    int getFramesIdle() const override { return 17; }
    float getOffsetY() const override { return 10.0f; }
    int getTiempoAnimacion() const override {return 300;}

    float getTamanoSprite() const override { return 90.0f; }



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
    std::string getNombreSprite() const override { return "FuenteCorrienteAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartafuenteI.png"; }
 
    float getTamanoSprite() const override { return 70.0f; }
    int getFramesIdle() const override { return 8; }

    float getOffsetX() const override { return 30.0f; }

    int getTiempoAnimacion() const override { return 350; }



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
    std::string getNombreSprite() const override { return "MotoPAnimada"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartamotop.png"; }


    float getTamanoSprite() const override { return 60.0f; }
    int getFramesIdle() const override { return 10; }

    float getOffsetX() const override { return 130.0f; }
    float getOffsetY() const override { return 100.0f; }

    int getTiempoAnimacion() const override { return 100; }


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
    std::string getNombreSprite() const override { return "GEMINIAnimado"; }
 std::string getNombreCarta()  const override { return "assets/cartas/cartagemini.png"; }

    float getTamanoSprite() const override { return 55.0f; }
    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 150 ; }

    float getOffsetX() const override { return 5.0f; }
    float getOffsetY() const override { return -22.0f; }





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
    std::string getNombreSprite() const override { return "CITAnimado"; }
std::string getNombreCarta()  const override { return "assets/cartas/cartacit.png"; }
    float getTamanoSprite() const override { return 90.0f; }

    int getFramesIdle() const override { return 8; }
    int getTiempoAnimacion() const override { return 1200; }
    float getOffsetX() const override { return 20.0f; }
    float getOffsetY() const override { return -20.0f; }
>>>>>>> 998d517d5d95f105c647aea597064eaa6853373e
};