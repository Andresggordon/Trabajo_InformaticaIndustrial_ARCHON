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
//  Muestra quien ha ganado, la puntuacion obtenida,
//  y permite volver al menu principal.
//
//  USO desde Partida:
//    1. pantalla_final->setResultado(r, puntuacion, nombre);
//    2. Cambiar estado a Modos_juego::Pantalla_Final
//    3. ranking->agregarPuntuacion(nombre, puntuacion);  <- guardar en fichero
// ============================================================
class PantallaFinal {
public:
    PantallaFinal();
    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

    // Llamar desde Partida justo antes de cambiar al estado Pantalla_Final
    void setResultado(ResultadoPartida r, int puntuacion, const std::string& nombre_ganador);

    // Getters para que main.cpp pueda guardar la partida en el ranking
    int         getPuntuacion()    const { return puntuacion_final; }
    std::string getNombreGanador() const { return nombre_ganador;   }

private:
    ETSIDI::Sprite* fondo;
    ETSIDI::Sprite* boton_menu;

    ResultadoPartida resultado;
    int              puntuacion_final;
    std::string      nombre_ganador;
    int              boton_activo;

    // Renderiza texto en las coordenadas del sistema OpenGL (-400 a 400)
    void dibujarTexto(const std::string& texto, float x, float y,
                      float r, float g, float b);
    void dibujarTextoGrande(const std::string& texto, float x, float y,
                             float r, float g, float b);
};
