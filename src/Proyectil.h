#pragma once
#include "ETSIDI.h"
#include <string>

class Proyectil {
public:
    Proyectil(float origenX, float origenY,
        float destinoX, float destinoY,
        int dano, float velocidad,
        const std::string& rutaSprite, bool disparadoPorLocal);
    ~Proyectil();

    void actualizar();
    void dibujar() const;

    bool haLlegado() const { return llegado_; }
    int  getDano()   const { return dano_; }

    bool esDeLocal() const { return disparadoPorLocal_; }
private:
    float x_, y_;
    float destinoX_, destinoY_;
    float velocidad_;
    int   dano_;
    bool  llegado_ = false;
    bool disparadoPorLocal_ = true;
    ETSIDI::Sprite* sprite_ = nullptr;
    bool            tieneSprite_ = false;
};

