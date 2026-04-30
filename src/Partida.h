#pragma once
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

    // Métodos de juego
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    void reset();
    void dibujaPersonajes();
    void dibujaextra();

private:
    Partida();
    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Tablero tab_;                       // propietaria del tablero, miembro directo


    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* abandonar_partida;
    ETSIDI::Sprite* popup_salir;

    // Pruebas de dibujo de sprites (borrador)
    DibujoPersonaje* PSS_prueba = nullptr;
    DibujoPersonaje* MH_prueba = nullptr;
    int modo_actual = 1;
    int turno_actual = 0;

    bool mostrar_popup;
    int boton_activo;
};