/**
 * @file Personaje.cpp
 * @brief Implementación de la lógica base de las unidades del juego.
 *
 * @details Gestiona la inicialización de estado, la aplicación de daño/cura
 * y valida las condiciones previas antes de permitir que una unidad se mueva,
 * apoyándose en la clase Geometria. También incluye el motor de interpolación
 * matemática (Lerp) para animar desplazamientos suaves entre casillas.
 */

#include "personaje.h"
#include "Casilla.h"
#include "Geometria.h"
#include "Tablero.h"
#include "Partida.h"
#include <GL/freeglut.h>
#include <cmath>

Personaje::Personaje(std::string nombre_, int vida_, Turno turno_, Movimiento movimiento_, stats arma_, int velocidad_, int radio_mov_, Casilla& casillaInicial)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_), turno(turno_), movimiento(movimiento_), arma(arma_), velocidad_movimiento(velocidad_),
    radio_movimiento(radio_mov_), casilla_actual(&casillaInicial)
{
    casilla_actual->setPersonaje(this);  // El personaje ocupa la casilla inicial al nacer

    // Orientación inicial automática por bando 
    if (turno == Turno::TURNO_DE_MANANA) {
        mirando_derecha = true;
        mirando_izquierda = false;
    }
    else {
        mirando_derecha = false;
        mirando_izquierda = true;
    }
}

Personaje::~Personaje() {}

void Personaje::setCasillaActual(Casilla* c) {
    casilla_actual = c;
}

// ---------------- SALUD Y ESTADO ----------------

void Personaje::recibirDano(int cantidad_) {
    vida_actual -= cantidad_;
    if (vida_actual < 0) vida_actual = 0;
}

void Personaje::curar(int cantidad_) {
    vida_actual += cantidad_;
    if (vida_actual > vida_Max) vida_actual = vida_Max;
}

bool Personaje::estaVivo() const {
    return vida_actual > 0;
}

// ---------------- GETTERS ----------------

std::string Personaje::getNombre() const { return nombre; }
int Personaje::getPosX() const { return casilla_actual ? casilla_actual->getCol() : -1; }
int Personaje::getPosY() const { return casilla_actual ? casilla_actual->getFila() : -1; }
float Personaje::getPorcentajeVida() const { return (float)vida_actual / vida_Max; }
int Personaje::getVidaActual() const { return vida_actual; }
int Personaje::getVidaMax() const { return vida_Max; }
Casilla* Personaje::getCasillaActual() const { return casilla_actual; }

// ---------------- LOGICA DE MOVIMIENTO EN TABLERO ----------------

ResultadoMover Personaje::mover(Casilla& destino) {
    // 1. Condiciones físicas del estado del personaje 
    if (!estaVivo()) return ResultadoMover::ILEGAL;
    if (getInmovilizado()) return ResultadoMover::ILEGAL;
    if (encarcelado) return ResultadoMover::ILEGAL;

    const Tablero& t = Partida::get_instance().tablero();

    // 2. Geometría decide si el movimiento es válido
    if (!Geometria::esMovimientoLegal(*casilla_actual, destino, *this, t))
        return ResultadoMover::ILEGAL;

    // 3. Evaluar a quién ocupa el destino
    Personaje* ocupante = destino.getPersonaje();
    if (ocupante != nullptr && ocupante->getTurno() == turno) // Es un aliado
        return ResultadoMover::ILEGAL;
    if (ocupante != nullptr && ocupante->getTurno() != turno) // Es un enemigo
        return ResultadoMover::CHOQUE;

    // 4. Ejecutar movimiento lógico (Intercambio de punteros)
    casilla_actual->setPersonaje(nullptr);
    destino.setPersonaje(this);
    casilla_actual = &destino;

    return ResultadoMover::OK;
}

// ---------------- TRANSICIÓN VISUAL ----------------

void Personaje::iniciarAnimacionMovimiento(float x_origen, float y_origen, float x_destino, float y_destino) {
    // EL TRUCO ANTISALTOS: Si estaba quieto, su posición visual es el origen que nos pasan.
    // Pero si YA estaba en movimiento, ignoramos el origen para que no dé un tirón hacia atrás.
    if (!en_transicion_) {
        posX_visual_ = x_origen;
        posY_visual_ = y_origen;
        tiempo_inicio_animacion_ = glutGet(GLUT_ELAPSED_TIME); // Lo usamos para calcular el DeltaTime
    }

    // Le decimos a la capa visual cuál es su nueva "zanahoria" a perseguir
    posX_destino_ = x_destino;
    posY_destino_ = y_destino;
    en_transicion_ = true;
}

void Personaje::actualizarPosicionVisual() {
    if (!en_transicion_) return;

    int ahora = glutGet(GLUT_ELAPSED_TIME);
    float dt = (ahora - tiempo_inicio_animacion_) / 1000.0f; // Delta time en segundos
    tiempo_inicio_animacion_ = ahora; // Actualizamos para el siguiente fotograma

    // MRU: v = d / t
    // Distancia = 45.0f píxeles (tamaño de la casilla en la arena)
    // Tiempo = getDuracionAnimacion() en segundos
    float tiempo_casilla_seg = getDuracionAnimacion() / 1000.0f;
    float velocidad_px_por_seg = 45.0f / tiempo_casilla_seg;

    // Calculamos el vector de dirección hacia el destino
    float dx = posX_destino_ - posX_visual_;
    float dy = posY_destino_ - posY_visual_;
    float distancia = std::sqrt(dx * dx + dy * dy);

    // ¿Cuánto puede avanzar en este fotograma?
    float movimiento_este_frame = velocidad_px_por_seg * dt;

    if (distancia <= movimiento_este_frame) {
        // Si el paso es mayor que la distancia que le queda, lo clavamos en la meta
        posX_visual_ = posX_destino_;
        posY_visual_ = posY_destino_;
        en_transicion_ = false; // Se detiene suavemente
    }
    else {
        // MRU puro: avanza hacia el destino
        posX_visual_ += (dx / distancia) * movimiento_este_frame;
        posY_visual_ += (dy / distancia) * movimiento_este_frame;
    }
}