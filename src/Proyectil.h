/**
 * @file Proyectil.h
 * @brief Entidad gráfica y lógica que representa los ataques a distancia en la arena.
 *
 * @details Controla el ciclo de vida, desplazamiento interpolado y renderizado
 * de los ataques en la Arena de Combate. Calcula las colisiones radiales en tiempo real
 * contra los personajes y respeta una distancia máxima basada en el alcance del arma,
 * destruyéndose automáticamente al alcanzar su objetivo o su límite físico.
 */

#pragma once
#include "ETSIDI.h"
#include <string>

class Proyectil {
public:
    Proyectil(float origenX, float origenY,
        float destinoX, float destinoY,
        int dano, float velocidad,
        const std::string& rutaSprite, bool disparadoPorLocal,int alcance);
    ~Proyectil();

    void actualizar();
    void dibujar() const;

    bool haLlegado() const { return llegado_; }
    int  getDano()   const { return dano_; }

    bool esDeLocal() const { return disparadoPorLocal_; }

    bool ColisionaCon(float x, float y, float radio = 20.0f) const;
    void marcarLlegado() { llegado_ = true; }

    float getX() const { return x_; }
    float getY() const { return y_; }
private:
    float origenX_, origenY_;       
    float distanciaMaxima_ = 500.f;
    float x_, y_;
    float destinoX_, destinoY_;
    float velocidad_;
    int   dano_;
    bool  llegado_ = false;
    bool disparadoPorLocal_ = true;
    ETSIDI::Sprite* sprite_ = nullptr;
    bool            tieneSprite_ = false;
};

