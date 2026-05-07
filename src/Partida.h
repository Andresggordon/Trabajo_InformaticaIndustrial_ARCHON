#pragma once
#include <vector>
#include "Menu.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include "dibujo_personajes.h"
#include "personaje.h"
#include "tipo_personaje.h"
#include "Tablero_vista.h" 


extern int equipo_j1;
extern int equipo_j2;
extern int modo_juego;
extern int turno_inicio;

class Partida {
public:
    // Singleton
    static Partida& get_instance() {
        static Partida instance;
        return instance;
    }

    // Getters del tablero
    Tablero& tablero() { return tab_; }
    const Tablero& tablero() const { return tab_; }
    const std::vector<DibujoPersonaje*>& getDibujos() const { return dibujos; }

    // Métodos de juego
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    void reset();
    void dibujaextra();
    void dibujaSeleccion();

private:
    Partida();
    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Tablero tab_;

    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* abandonar_partida;
    ETSIDI::Sprite* popup_salir;

    std::vector<Personaje*>       personajes;
    std::vector<DibujoPersonaje*> dibujos;

    int modo_actual = 1;
    int turno_actual = 0;

    Personaje* personaje_seleccionado = nullptr;  // ← ya lo tienes
    void procesarClickTablero(int fil, int col);   // ← ya lo tienes

    bool mostrar_popup;
    int boton_activo;
};