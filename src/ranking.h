#pragma once
#include "ETSIDI.h"
#include "Modos_juego.h"
#include <string>
#include <vector>

// -----------------------------------------------------------------------------
//  EntradaRanking + Ranking
//
//  Responsabilidad unica de Ranking: gestionar la lista de puntuaciones de
//  partidas terminadas. Carga al construirse, guarda automaticamente tras
//  cada agregar(), y dibuja las Top N en pantalla.
//
//  Alta cohesion: todo lo del ranking (datos, fichero y dibujo) vive aqui.
//  Bajo acoplamiento: el resto del juego solo usa agregar() — no sabe del
//  formato del fichero ni de como se ordenan.
//
//  Persistencia: "ranking.txt" en el cwd del ejecutable. Formato por linea:
//        puntuacion;nombre
//  La puntuacion va primero porque es la clave de orden y "nombre" puede
//  contener espacios.
// -----------------------------------------------------------------------------

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
