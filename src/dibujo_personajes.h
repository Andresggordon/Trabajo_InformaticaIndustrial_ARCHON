/**
 * @file dibujo_personajes.h
 * @brief Define la clase DibujoPersonaje, encargada de la representación visual y animación de las piezas.
 *
 * @details Separa la lógica interna del juego de su representación gráfica.
 * Esta clase envuelve los sprites y animaciones de la librería ETSIDI, gestionando las transiciones
 * visuales de movimiento en el tablero, la interpolación de posiciones y las cinemáticas de entrada
 * al comenzar la partida, leyendo siempre los datos lógicos desde su puntero a `Personaje`.
 */

#pragma once
#include "ETSIDI.h"      // Dibujo de los sprites
#include "Casilla.h"
#include "personaje.h"
#include <cmath>         // Obligatorio para std::abs()

class DibujoPersonaje {
public:
    // El constructor recibe el puntero al personaje lógico, para leer su posición
    DibujoPersonaje(Personaje* p);
    ~DibujoPersonaje();

    // El método principal de renderizado
    void dibujar(float x, float y);
    void update() { if (sprite) sprite->loop(); }

    Personaje* getPersonaje() const { return modelo; }
    void setModelo(Personaje* nuevo_modelo) { modelo = nuevo_modelo; } // Para manejar el turno de tarde y el de mañana

    void forzarTeletransporte() { modelo->setTeletransportado(true); }

    // Fija la posición de golpe (se usa al volver de la Arena al Tablero)
    void setPosicionVisual(float x, float y) {
        x_visual = x;
        y_visual = y;
        inicializado = true;
    }

    // Configura la pieza fuera de la pantalla y la deja congelada
    void iniciarIntroFuera(float x, float y) {
        x_visual = x;
        y_visual = y;
        esperando_intro = true;
        inicializado = true;
        intro_terminada = false;
    }

    // Le da permiso para empezar a caminar hacia su destino
    void arrancar() { esperando_intro = false; }

    // Nos chiva si ya ha llegado a su destino
    bool haLlegado(float x_destino, float y_destino) {
        return (std::abs(x_destino - x_visual) < 2.0f && std::abs(y_destino - y_visual) < 2.0f);
    }

private:
    Personaje* modelo;               // Puntero a la lógica del personaje
    ETSIDI::Sprite* sprite;          // Usado si frames == 1
    ETSIDI::SpriteSequence* anim;    // Usado si frames > 1

    // Para no resetear los frames y hacer la animación fluida
    int fila_actual_anim = -1;

    // Variables para la posición visual en el tablero
    bool inicializado = false;
    float x_visual = 0.0f;
    float y_visual = 0.0f;

    // Interruptor del gestor de turnos de la intro
    bool esperando_intro = false;

    bool intro_terminada = true;

};