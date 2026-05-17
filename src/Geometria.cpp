#include "Geometria.h"
#include "Casilla.h"
#include "personaje.h"
#include "Tablero.h"

bool Geometria::desplazamientoValido(const Casilla& origen,
    const Casilla& destino,
    const Personaje& p) {
    int dx = abs(destino.getCol() - origen.getCol());
    int dy = abs(destino.getFila() - origen.getFila());
    int radio = p.getRadioMovimiento();

    switch (p.getMovimiento()) {

    case Movimiento::TIERRA:
        // Solo en cruz (horizontal o vertical), sin diagonales,
        // y la suma de pasos no supera el radio.
        return (dx == 0 || dy == 0) && (dx + dy <= radio) && (dx + dy > 0);

    case Movimiento::AIRE:
        // Cuadrado: ambas componentes dentro del radio.
        // Puede moverse en diagonal.
        return (dx <= radio) && (dy <= radio) && (dx + dy > 0);

    case Movimiento::TELETRANSPORTE:
        // Sin restricción geométrica.
        return (dx + dy > 0);

    default:
        return false;
    }
}

// Comprueba que todas las casillas intermedias en línea recta estén vacías.
// Solo aplica a TIERRA porque AIRE y TELETRANSPORTE no tienen camino intermedio.

bool Geometria::caminoLibre(const Casilla& origen,
    const Casilla& destino,
    const Tablero& t) {
    int filaO = origen.getFila();
    int colO = origen.getCol();
    int filaD = destino.getFila();
    int colD = destino.getCol();

    // Dirección del movimiento normalizada a -1, 0 o 1
    int df = (filaD > filaO) ? 1 : (filaD < filaO) ? -1 : 0;
    int dc = (colD > colO) ? 1 : (colD < colO) ? -1 : 0;

    int fila = filaO + df;
    int col = colO + dc;

    // Recorremos casilla a casilla hasta llegar al destino (sin incluirlo)
    while (fila != filaD || col != colD) {
        if (t.getCasilla(fila, col).getPersonaje() != nullptr)
            return false;  // hay alguien en el camino
        fila += df;
        col += dc;
    }

    return true;
}


// Geometría y camino libre

bool Geometria::esMovimientoLegal(const Casilla& origen,
    const Casilla& destino,
    const Personaje& p,
    const Tablero& t) {
    if (!desplazamientoValido(origen, destino, p))
        return false;

    // Solo los terrestres tienen restricción de camino
    if (p.getMovimiento() == Movimiento::TIERRA)
        if (!caminoLibre(origen, destino, t))
            return false;

    return true;
}

// Recorre todo el tablero y devuelve las casillas a las que p puede ir.

std::vector<Casilla*> Geometria::getCasillasAccesibles(const Personaje& p,
    const Tablero& t) {
    std::vector<Casilla*> accesibles;
    const Casilla* origen = p.getCasillaActual();

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            const Casilla& destino = t.getCasilla(fila, col);

            // No incluir la casilla actual del personaje
            if (&destino == origen) continue;

            // Comprobar geometría y camino
            if (!esMovimientoLegal(*origen, destino, p, t)) continue;

            // No incluir casillas ocupadas por aliados
            Personaje* ocupante = destino.getPersonaje();
            if (ocupante != nullptr && ocupante->getTurno() == p.getTurno())
                continue;

            accesibles.push_back(const_cast<Casilla*>(&destino));
        }
    }

    return accesibles;
}