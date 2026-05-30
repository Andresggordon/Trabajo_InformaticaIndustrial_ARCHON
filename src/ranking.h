/**
 * @file ranking.h
 * @brief Gestiona la lectura, escritura y visualización de las mejores puntuaciones.
 *
 * @details Tiene la responsabilidad única de mantener una lista ordenada (Top N) de las
 * puntuaciones obtenidas en partidas finalizadas. Se encarga de cargar los datos desde el
 * archivo persistente (`ranking.txt`) al iniciarse, guardar automáticamente tras cada inserción
 * (`agregar()`) y renderizar la clasificación en pantalla. Su diseño garantiza alta cohesión
 * al encapsular el formato del fichero, y bajo acoplamiento al exponer solo métodos básicos.
 */

#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"
#include <string>
#include <vector>

struct EntradaRanking {
    std::string nombre;
    int         puntuacion;
};

class Ranking {
public:
    Ranking();

    void dibuja();
    void update(int x, int y);
    Modos_juego click(int x, int y);

    // UNICA API publica de escritura: anade entrada, reordena y guarda fichero.
    // La llama Partida al detectar fin de partida.
    void agregar(const std::string& nombre, int puntuacion);

private:
    ETSIDI::Sprite* fondo2;
    ETSIDI::Sprite* back;
    int boton_activo;

    std::vector<EntradaRanking> entradas_;  // ordenado descendente por puntuacion

    static const int TOP_N        = 10;   // entradas visibles en pantalla
    static const int MAX_ENTRADAS = 50;   // tope para que el fichero no crezca infinito

    // Persistencia (privada: nadie de fuera necesita conocer el fichero).
    void cargar();
    void guardar() const;

    // Helper de dibujo: texto centrado horizontalmente a altura y.
    void dibujarTextoCentrado(const std::string& texto, void* font, float y,
                               float r, float g, float b);
};
