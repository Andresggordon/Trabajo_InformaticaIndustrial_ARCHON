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

Personaje::Personaje(std::string nombre_, int vida_, Turno turno_, Movimiento movimiento_, stats arma_, Casilla& casillaInicial)
    : nombre(nombre_), vida_Max(vida_), vida_actual(vida_),
    turno(turno_), movimiento(movimiento_), arma(arma_), casilla_actual(&casillaInicial)
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

// ---------------- TRANSICIÓN VISUAL (LERP) ----------------

void Personaje::iniciarAnimacionMovimiento(float x_origen, float y_origen, float x_destino, float y_destino) {
    posX_visual_ = x_origen;
    posY_visual_ = y_origen;
    posX_destino_ = x_destino;
    posY_destino_ = y_destino;
    tiempo_inicio_animacion_ = glutGet(GLUT_ELAPSED_TIME);
    en_transicion_ = true;
}

void Personaje::actualizarPosicionVisual() {
    if (!en_transicion_) return;

    int ahora = glutGet(GLUT_ELAPSED_TIME);
    int tiempo_pasado = ahora - tiempo_inicio_animacion_;

    // Calculamos el progreso matemático de la animación de 0.0f a 1.0f
    float progreso = (float)tiempo_pasado / DURACION_ANIMACION_MS;

    if (progreso >= 1.0f) {
        // La animación ha terminado, forzamos posición final exacta
        posX_visual_ = posX_destino_;
        posY_visual_ = posY_destino_;
        en_transicion_ = false;
    }
    else {
        // Fórmula LERP: Posición = Inicio + (Destino - Inicio) * Progreso
        posX_visual_ = posX_visual_ + (posX_destino_ - posX_visual_) * progreso;
        posY_visual_ = posY_visual_ + (posY_destino_ - posY_visual_) * progreso;
    }
}