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
    
    // Llamar desde Partida justo antes de cambiar al estado Pantalla_Final.
    // Tambien arranca el temporizador de la fase de creditos.
    void setResultado(ResultadoPartida r, int puntuacion);
    void teclado(unsigned char key);
    bool volverMenu() const;

    enum class Fase { PEDIR_NOMBRE, MOSTRAR_VICTORIA, CREDITOS };

    const std::string& getNombre()    const { return nombre_; }
    int                getPuntuacion() const { return puntuacion_; }
    Fase               getFase()       const { return fase_; }

private:
    
    ETSIDI::Sprite* fondo_nombre_;
    ETSIDI::Sprite* fondo_victoria_;
    ETSIDI::Sprite* creditos_;

    Fase fase_;
    ResultadoPartida resultado_;
    int  puntuacion_;
    std::string nombre_;
    int  tiempoFaseVictoria_;

    static const int TIEMPO_CREDITOS = 10000;
    static const int TIEMPO_VUELTA_MENU = 10000;

  
    
    void dibujarTextoCentrado(const std::string& texto, void* font, float y,
        float r, float g, float b, float offsetX = 45.0f);
};