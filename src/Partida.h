#pragma once
#include "Menu.h"
#include "Tablero.h"
#include "MotorGrafico.h"
#include "ETSIDI.h"
#include "dibujo_personajes.h"
#include "personaje.h"
#include "tipo_personaje.h"

class Partida {
public:
    Partida();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    void reset();

private:
    Tablero* tablero;
    MotorGrafico* motor_grafico; 
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