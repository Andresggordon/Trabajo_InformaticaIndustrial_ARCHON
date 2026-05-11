#include "FinPartida.h"

// ── Puntos de poder en el tablero 9x9 ────────────────────────────────────────
// Formato: {fila, columna}
// Son el centro + los 4 puntos medios de cada borde,
// como en el juego original Archon.
const int FinPartida::PUNTOS_PODER[5][2] = {
    {4, 4}, // centro
    {0, 4}, // borde superior, centro
    {8, 4}, // borde inferior, centro
    {4, 0}, // borde izquierdo, centro
    {4, 8}, // borde derecho, centro
};

// ============================================================
//  PRIVADOS
// ============================================================

int FinPartida::contarVivas(
    const std::vector<Personaje*>& personajes,
    Turno bando)
{
    int count = 0;
    for (auto* p : personajes) {
        if (p == nullptr) continue;
        if (!p->estaVivo()) continue;
        if (p->getTurno() != bando) continue;
        count++;
    }
    return count;
}

int FinPartida::puntosDePoderControlados(
    const std::vector<Personaje*>& personajes,
    Turno bando)
{
    int count = 0;
    // Para cada punto de poder, miramos si hay alguna pieza viva del bando encima
    for (int i = 0; i < NUM_PUNTOS_PODER; i++) {
        int fila = PUNTOS_PODER[i][0];
        int col = PUNTOS_PODER[i][1];

        for (auto* p : personajes) {
            if (p == nullptr) continue;
            if (!p->estaVivo()) continue;
            if (p->getTurno() != bando) continue;

            // getPosY = fila, getPosX = columna  (segun personaje.cpp)
            if (p->getPosY() == fila && p->getPosX() == col) {
                count++;
                break; // ya hay una pieza nuestra aqui, pasamos al siguiente punto
            }
        }
    }
    return count;
}

// ============================================================
//  PUBLICO
// ============================================================

CondicionVictoria FinPartida::comprobar(
    const std::vector<Personaje*>& personajes,
    const Tablero& /*tablero*/)
{
    // ── Condicion 1: piezas eliminadas ──────────────────────────────────────
    int vivas_manana = contarVivas(personajes, Turno::TURNO_DE_MANANA);
    int vivas_tarde = contarVivas(personajes, Turno::TURNO_DE_TARDE);

    if (vivas_manana == 0) return CondicionVictoria::GANA_TARDE_POR_PIEZAS;
    if (vivas_tarde == 0)  return CondicionVictoria::GANA_MANANA_POR_PIEZAS;

    // ── Condicion 2: puntos de poder ────────────────────────────────────────
    int pp_manana = puntosDePoderControlados(personajes, Turno::TURNO_DE_MANANA);
    int pp_tarde = puntosDePoderControlados(personajes, Turno::TURNO_DE_TARDE);

    if (pp_manana >= NUM_PUNTOS_PODER) return CondicionVictoria::GANA_MANANA_POR_PUNTOS;
    if (pp_tarde >= NUM_PUNTOS_PODER)  return CondicionVictoria::GANA_TARDE_POR_PUNTOS;

    // ── Condicion 3: rival con una sola pieza encarcelada ───────────────────
    // TODO: pendiente. Requiere que personaje.h exponga estaEncarcelado() como
    //       getter publico. Hablarlo con Andres y Fer antes de implementar.

    // Si no se cumple nada, la partida sigue
    return CondicionVictoria::NINGUNA;
}

// ── Helpers de consulta del resultado ────────────────────────────────────────

bool FinPartida::ganaManana(CondicionVictoria c) {
    return c == CondicionVictoria::GANA_MANANA_POR_PIEZAS
        || c == CondicionVictoria::GANA_MANANA_POR_PUNTOS;
}

bool FinPartida::ganaTarde(CondicionVictoria c) {
    return c == CondicionVictoria::GANA_TARDE_POR_PIEZAS
        || c == CondicionVictoria::GANA_TARDE_POR_PUNTOS;
}

bool FinPartida::partidaTerminada(CondicionVictoria c) {
    return c != CondicionVictoria::NINGUNA;
}