/**
 * @file EvaluadorMovimiento.cpp
 * @brief Implementación de la heurística de evaluación táctica para la Inteligencia Artificial.
 */

#include "EvaluadorMovimiento.h"
#include "personaje.h"
#include "Casilla.h"
#include "Tablero.h"
#include "Geometria.h"

EvaluadorMovimiento::EvaluadorMovimiento()
    : peso_captura_mago_(1000),
      peso_punto_poder_(150),
      peso_riesgo_(70),
      peso_color_propio_(15) {
}

int EvaluadorMovimiento::valorPieza(const Personaje& p) const {
    if (p.esLider())
        return peso_captura_mago_;

    // Pieza normal: peligrosa segun lo que pega, su alcance y lo que aguanta.
    stats arma = p.getArma();
    return arma.getDanio() + arma.getAlcance() * 3 + p.getVidaMax() / 5;
}

bool EvaluadorMovimiento::esPuntoDePoder(const Casilla& destino) const {
    int f = destino.getFila();
    int c = destino.getCol();

    // Tablero 9x9 (indices 0..8): centro + centro de cada borde.
    const int centro = Tablero::FILAS / 2;          // 4
    const int borde_min = 0;
    const int borde_max = Tablero::FILAS - 1;       // 8

    if (f == centro && c == centro) return true;          // centro
    if (f == centro && (c == borde_min || c == borde_max)) return true; // bordes horizontales
    if (c == centro && (f == borde_min || f == borde_max)) return true; // bordes verticales
    return false;
}

bool EvaluadorMovimiento::esColorPropio(const Casilla& destino,
                                        const Personaje& pieza) const {
    
    EstadoCasilla e = destino.getEstado();
    if (pieza.getTurno() == Turno::TURNO_DE_TARDE)
        return e == EstadoCasilla::AZUL_FIJA;
    else
        return e == EstadoCasilla::BLANCA_FIJA;
}

bool EvaluadorMovimiento::casillaAmenazada(const Casilla& destino,
                                           const Personaje& piezaPropia,
                                           const Tablero& tablero) const {
    Personaje* ocupanteDestino = destino.getPersonaje();

    for (int f = 0; f < Tablero::FILAS; f++) {
        for (int c = 0; c < Tablero::COLUMNAS; c++) {
            const Casilla& origenEnemigo = tablero.getCasilla(f, c);
            Personaje* enemigo = origenEnemigo.getPersonaje();

            if (enemigo == nullptr) continue;
            if (!enemigo->estaVivo()) continue;
            // Mismo bando: no amenaza.
            if (enemigo->getTurno() == piezaPropia.getTurno()) continue;
            // Inmovilizado: no podra moverse el proximo turno.
            if (enemigo->getInmovilizado()) continue;
            // Si el enemigo es justo el que pensamos capturar en `destino`,
            // tras el combate ya no esta para amenazar: no lo contamos.
            if (enemigo == ocupanteDestino) continue;

            if (Geometria::esMovimientoLegal(origenEnemigo, destino,
                                             *enemigo, tablero))
                return true;
        }
    }
    return false;
}

int EvaluadorMovimiento::evaluar(const Personaje& pieza,
                                 const Casilla& destino,
                                 const Tablero& tablero) const {
    int puntuacion = 0;

    // 1. ¿Que capturamos? destino solo puede estar vacio o con un enemigo
    Personaje* ocupante = destino.getPersonaje();
    if (ocupante != nullptr && ocupante->estaVivo())
        puntuacion += valorPieza(*ocupante);

    // 2. ¿Quedamos expuestos? Descontamos parte del valor de la pieza propia
    //    proporcional al riesgo configurado.
    if (casillaAmenazada(destino, pieza, tablero))
        puntuacion -= (valorPieza(pieza) * peso_riesgo_) / 100;

    // 3. Bonus posicional: puntos de poder y color propio.
    if (esPuntoDePoder(destino))
        puntuacion += peso_punto_poder_;
    if (esColorPropio(destino, pieza))
        puntuacion += peso_color_propio_;

    return puntuacion;
}
