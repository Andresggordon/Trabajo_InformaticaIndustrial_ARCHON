
// EvaluadorMovimiento es el ente que sabe CUANTO de bueno es un movimiento.
// Su unica responsabilidad es puntuar

// Para puntuar solo consulta el Tablero y los Personajes (de solo lectura) y
// reutiliza Geometria para razonar sobre amenazas. No guarda referencias al
// estado del juego

#pragma once

class Personaje;
class Casilla;
class Tablero;

class EvaluadorMovimiento {
public:
    EvaluadorMovimiento();

    // Puntua mover `pieza` a `destino` en el estado actual de `tablero`.
    // Cuanto mayor sea el numero devuelto, mejor es la jugada.
    // No modifica nada: la evaluacion es una consulta pura.
    int evaluar(const Personaje& pieza, const Casilla& destino,
                const Tablero& tablero) const;

private:
    // Valor estrategico intrinseco de una pieza. Sirve tanto para valorar lo
    // que capturas (cuanto ganas) como lo que arriesgas (cuanto puedes perder).
    int valorPieza(const Personaje& p) const;

    // ¿Algun enemigo podria alcanzar `destino` en su proximo turno?
    bool casillaAmenazada(const Casilla& destino, const Personaje& piezaPropia,
                          const Tablero& tablero) const;

    // ¿Es `destino` uno de los 5 puntos de poder del tablero 9x9?
    bool esPuntoDePoder(const Casilla& destino) const;

    // ¿La casilla es del color del bando de `pieza`? (curan mas rapido ahi)
    bool esColorPropio(const Casilla& destino, const Personaje& pieza) const;

    // Pesos de la heuristica (encapsulados). Fijados en el constructor.
    int peso_captura_mago_;   // capturar al mago rival es practicamente ganar
    int peso_punto_poder_;    // ocupar un punto de poder
    int peso_riesgo_;         // % del valor propio que se descuenta si quedas amenazado
    int peso_color_propio_;   // pequeña ventaja por estar en tu color
};
