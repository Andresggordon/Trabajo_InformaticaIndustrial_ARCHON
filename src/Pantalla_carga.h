/**
 * @file Pantalla_carga.h
 * @brief Define la secuencia cinemática introductoria al abrir el juego (Splash Screen).
 *
 * @details Gestiona la pantalla inicial de presentación. Controla un temporizador interno
 * (`timer`) para mostrar y desvanecer logotipos de forma secuencial. Una vez finalizada
 * la secuencia automática, solicita la confirmación del usuario (pulsar Enter) para
 * realizar la transición segura hacia el `Menu` principal.
 */

#pragma once
#include "ETSIDI.h"
#include "Menu.h"
#include "Modos_juego.h"

class Pantalla_carga {
public:
    Pantalla_carga();
    void dibuja();
    void update();
    Modos_juego click(int x, int y);
    void teclado(unsigned char key);
    bool carga_completa;

private:
    ETSIDI::Sprite* fondo_carga;
    ETSIDI::Sprite* logo1;
    ETSIDI::Sprite* logo2;
    bool esperando_enter;
    float timer;
};