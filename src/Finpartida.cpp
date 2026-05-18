#include "Finpartida.h"
#include "Casilla.h"

// Los 5 puntos de poder: centro + centro de cada borde (tablero 9x9).
const int FinPartida::PUNTOS_PODER[5][2] = {
    {4, 4}, // centro
    {0, 4}, // borde superior
    {8, 4}, // borde inferior
    {4, 0}, // borde izquierdo
    {4, 8}, // borde derecho
};

bool FinPartida::enJuego(const Personaje* p) {
    // Viva (vida > 0) y colocada en una casilla del tablero.
    // Una pieza muerta o retirada del tablero NO cuenta.
    return p != nullptr && p->estaVivo() && p->getCasillaActual() != nullptr;
}

int FinPartida::contarEnJuego(const std::vector<Personaje*>& personajes, Turno bando) {
    int count = 0;
    for (auto* p : personajes)
        if (enJuego(p) && p->getTurno() == bando)
            count++;
    return count;
}

bool FinPartida::liderEnJuego(const std::vector<Personaje*>& personajes, Turno bando) {
    for (auto* p : personajes)
        if (p != nullptr && p->getTurno() == bando && p->esLider() && enJuego(p))
            return true;
    return false;
}

int FinPartida::contarNoEncarceladas(const std::vector<Personaje*>& personajes, Turno bando) {
    int count = 0;
    for (auto* p : personajes)
        if (enJuego(p) && p->getTurno() == bando && !p->estaEncarcelado())
            count++;
    return count;
}

int FinPartida::puntosDePoderControlados(Turno bando, const Tablero& tablero) {
    int count = 0;
    for (int i = 0; i < NUM_PUNTOS_PODER; i++) {
        const Casilla& c = tablero.getCasilla(PUNTOS_PODER[i][0], PUNTOS_PODER[i][1]);
        Personaje* p = c.getPersonaje();
        if (p != nullptr && p->estaVivo() && p->getTurno() == bando)
            count++;
    }
    return count;
}

CondicionVictoria FinPartida::comprobar(
    const std::vector<Personaje*>& personajes,
    const Tablero& tablero)
{
    // ── 1. El mago/lider ha caido (propuesta: "si muere el mago pierdes").
    //       Es la condicion mas decisiva y la que de verdad termina partidas.
    bool liderM = liderEnJuego(personajes, Turno::TURNO_DE_MANANA);
    bool liderT = liderEnJuego(personajes, Turno::TURNO_DE_TARDE);
    if (liderM && !liderT) return CondicionVictoria::GANA_MANANA_POR_LIDER;
    if (liderT && !liderM) return CondicionVictoria::GANA_TARDE_POR_LIDER;

    int vivasM = contarEnJuego(personajes, Turno::TURNO_DE_MANANA);
    int vivasT = contarEnJuego(personajes, Turno::TURNO_DE_TARDE);

    // ── 2. Un bando se ha quedado sin piezas.
    if (vivasM == 0 && vivasT > 0) return CondicionVictoria::GANA_TARDE_POR_PIEZAS;
    if (vivasT == 0 && vivasM > 0) return CondicionVictoria::GANA_MANANA_POR_PIEZAS;

    // ── 3. Rival reducido a una sola pieza y ademas encarcelada.
    if (vivasT == 1 && contarNoEncarceladas(personajes, Turno::TURNO_DE_TARDE) == 0)
        return CondicionVictoria::GANA_MANANA_POR_ENCARCELADO;
    if (vivasM == 1 && contarNoEncarceladas(personajes, Turno::TURNO_DE_MANANA) == 0)
        return CondicionVictoria::GANA_TARDE_POR_ENCARCELADO;

    // ── 4. Control de los 5 puntos de poder.
    if (puntosDePoderControlados(Turno::TURNO_DE_MANANA, tablero) >= NUM_PUNTOS_PODER)
        return CondicionVictoria::GANA_MANANA_POR_PUNTOS;
    if (puntosDePoderControlados(Turno::TURNO_DE_TARDE, tablero) >= NUM_PUNTOS_PODER)
        return CondicionVictoria::GANA_TARDE_POR_PUNTOS;

    return CondicionVictoria::NINGUNA;
}

bool FinPartida::ganaManana(CondicionVictoria c) {
    return c == CondicionVictoria::GANA_MANANA_POR_LIDER
        || c == CondicionVictoria::GANA_MANANA_POR_PIEZAS
        || c == CondicionVictoria::GANA_MANANA_POR_ENCARCELADO
        || c == CondicionVictoria::GANA_MANANA_POR_PUNTOS;
}

bool FinPartida::ganaTarde(CondicionVictoria c) {
    return c == CondicionVictoria::GANA_TARDE_POR_LIDER
        || c == CondicionVictoria::GANA_TARDE_POR_PIEZAS
        || c == CondicionVictoria::GANA_TARDE_POR_ENCARCELADO
        || c == CondicionVictoria::GANA_TARDE_POR_PUNTOS;
}

bool FinPartida::partidaTerminada(CondicionVictoria c) {
    return c != CondicionVictoria::NINGUNA;
}
