#pragma once
#include "Tablero.h"
#include "ETSIDI.h"
#include <GL/freeglut.h>
#include <vector>

class Personaje;

class MotorGrafico {
public:
    static constexpr float TAM = 60.0f;
    static constexpr float INICIO_X = -270.0f;
    static constexpr float INICIO_Y = -270.0f;

    static MotorGrafico& get_instance() {
        static MotorGrafico instance;
        return instance;
    }

    void dibujar();
    void dibujarArena();
    void dibujarBarrasHP(Personaje* local, Personaje* invasor);

    // FUNCIONES DE DIBUJO (Trasladadas desde Partida para cumplir normativa)
    void dibujaSeleccion(Personaje* seleccionado, const std::vector<Casilla*>& iluminadas);
    void dibujaHabilidades(Personaje* p, bool modo_t, bool modo_i, bool modo_r);
    void dibujaInmovilizados(const Tablero& t);
    void dibujaBarrasVida(const Tablero& t, Personaje* p);
    void dibujarVidaPanel(Personaje* p);

private:
    MotorGrafico() = default;
    void dibujarTextoBitmap(float x, float y, const char* texto);
    void dibujarTablero(const Tablero& t);
    void dibujarPersonajes(const Tablero& t, Personaje* seleccionado = nullptr);
    void dibujaCuadrado(float x, float y, float r, float g, float b);
    void dibujarPersonajesArena(Personaje* local, Personaje* invasor);
    void dibujarFondoArena();
    void dibujarBarraVida(float x, float y, Personaje* p);
    void dibujarVidaTexto(float x, float y, Personaje* p);
};