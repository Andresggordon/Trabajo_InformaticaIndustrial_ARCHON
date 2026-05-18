#pragma once
#include <vector>
#include "Menu.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include "dibujo_personajes.h"
#include "personaje.h"
#include "tipo_personaje.h"
#include "Tablero_vista.h"
#include "IAJugador.h"

extern int equipo_j1;
extern int equipo_j2;
extern int modo_juego;
extern int turno_inicio;

class Partida {
public:
    static Partida& get_instance() {
        static Partida instance;
        return instance;
    }

    Tablero& tablero() { return tab_; }
    const Tablero& tablero() const { return tab_; }
    const std::vector<DibujoPersonaje*>& getDibujos() const { return dibujos; }

    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    Modos_juego turnoMaquina();          // juega la maquina si le toca (modo 1 jug.)
    void teclado(unsigned char key);
    void reset();
    void dibujaextra();

    // Dibujos y habilidades (Mezcla de ambos trabajos)
    void dibujaSeleccion();
    void dibujaHabilidades();
    void tecladoHabilidades(unsigned char key);
    void dibujarTextoBitmap(float x, float y, const char* texto);
    void dibujaInmovilizados();
    void dibujaEscudos();
    void dibujaInmunidad();

    Personaje* getPersonajeSeleccionado() const { return personaje_seleccionado; }
    void dibujaBarrasVida();

private:
    Partida();
    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Tablero tab_;
    IAJugador ia_;   // cerebro de la maquina (modo 1 jugador)

    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* abandonar_partida;
    ETSIDI::Sprite* popup_salir;

    std::vector<Personaje*>       personajes;
    std::vector<DibujoPersonaje*> dibujos;

    // NUESTRO: Saber las casillas en las que se moverá el personaje
    std::vector<Casilla*> casillas_iluminadas;

    int modo_actual = 1;
    int turno_actual = 0;

    Personaje* personaje_seleccionado = nullptr;
    Modos_juego procesarClickTablero(int fil, int col);
    bool es_lider_seleccionado = false;

    bool mostrar_popup;
    int boton_activo;
    bool modo_teleport = false;
    bool modo_inmovilizar = false;
    bool modo_revivir = false;
    bool modo_curar = false;
    bool modo_escudo = false;
    bool modo_inmunidad = false;

    ETSIDI::Sprite* carta_actual = nullptr;
    std::string nombre_carta_cargada = "";
};