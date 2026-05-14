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
    void dibujaHabilidades();

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
    std::vector<Casilla*> casillas_iluminadas; //Saber las casillas en las que se moverá el personaje


    int modo_actual = 1;
    int turno_actual = 0;

    Personaje* personaje_seleccionado = nullptr;  // ← ya lo tienes
    Modos_juego procesarClickTablero(int fil, int col);   // ← ya lo tienes
    bool es_lider_seleccionado = false;

    bool mostrar_popup;
    int boton_activo;
    bool modo_teleport = false;
    bool modo_inmovilizar = false;
    bool modo_revivir = false;

    ETSIDI::Sprite* carta_actual = nullptr;
    std::string nombre_carta_cargada = "";
};