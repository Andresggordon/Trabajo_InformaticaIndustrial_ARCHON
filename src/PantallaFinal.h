#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"
#include <string>

// Resultado posible de una partida
enum class ResultadoPartida {
    VICTORIA_MANANA, // Turno de mañana gana
    VICTORIA_TARDE,  // Turno de tarde gana
};

// ============================================================
//  Clase PantallaFinal
//  Muestra quien ha ganado, la puntuacion obtenida, y permite
//  volver al menu principal.
//
//  Tras TIEMPO_PARA_CREDITOS ms, sustituye automaticamente la
//  pantalla por una imagen de "creditos" (disenada por Esther).
//  El boton BACK sigue visible y funcional en ambas fases.
//
//  USO desde Partida:
//    1. pantalla_final->setResultado(r, puntuacion, nombre);
//    2. Cambiar estado a Modos_juego::Pantalla_Final
// ============================================================
class PantallaFinal {
public:
    PantallaFinal();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);
    bool volverMenu() const;

    // Llamar desde Partida justo antes de cambiar al estado Pantalla_Final.
    // Tambien arranca el temporizador de la fase de creditos.
    void setResultado(ResultadoPartida r, int puntuacion, const std::string& nombre_ganador);

    // Getters para que main.cpp pueda guardar la partida en el ranking
    int         getPuntuacion()    const { return puntuacion_final; }
    std::string getNombreGanador() const { return nombre_ganador; }

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* creditos_;   // Imagen mostrada tras TIEMPO_PARA_CREDITOS

    ResultadoPartida resultado;
    int              puntuacion_final;
    std::string      nombre_ganador;
    int              tiempoInicio_;   // ms en que se mostro la pantalla

    static const int tiempo_creditos = 10000;  // 10 segundos

  
    
    void dibujarTextoCentrado(const std::string& texto, void* font, float y,
        float r, float g, float b, float offsetX = 45.0f);
};