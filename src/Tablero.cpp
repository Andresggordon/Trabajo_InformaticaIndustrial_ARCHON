#include "Tablero.h"
#include "personaje.h"

Tablero::Tablero() {
    fase_actual = FaseCiclo::ATARDECER;
    inicializarMatriz();
}

void Tablero::inicializarMatriz() {
    EstadoCasilla B = EstadoCasilla::BLANCA_FIJA;
    EstadoCasilla A = EstadoCasilla::AZUL_FIJA;
    EstadoCasilla D = EstadoCasilla::DINAMICA;

    EstadoCasilla patron[FILAS][COLUMNAS] = {
        {A, B, A, D, D, D, B, A, B},
        {B, A, D, B, D, A, D, B, A},
        {A, D, B, A, D, B, A, D, B},
        {D, B, A, B, D, A, B, A, D},
        {B, D, D, D, D, D, D, D, A},
        {D, B, A, B, D, A, B, A, D},
        {A, D, B, A, D, B, A, D, B},
        {B, A, D, B, D, A, D, B, A},
        {A, B, A, D, D, D, B, A, B},
    };

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            matriz[i][j].setEstado(patron[i][j]);
}

void Tablero::avanzarCiclo() {
    switch (fase_actual) {
    case FaseCiclo::MEDIODIA:   fase_actual = FaseCiclo::ATARDECER;  break;
    case FaseCiclo::ATARDECER:  fase_actual = FaseCiclo::ANOCHECER;  break;
    case FaseCiclo::ANOCHECER:  fase_actual = FaseCiclo::MEDIANOCHE; break;
    case FaseCiclo::MEDIANOCHE: fase_actual = FaseCiclo::MADRUGADA;  break;
    case FaseCiclo::MADRUGADA:  fase_actual = FaseCiclo::AMANECER;   break;
    case FaseCiclo::AMANECER:   fase_actual = FaseCiclo::MEDIODIA;   break;
    }
}

Casilla& Tablero::getCasilla(int fila, int col) {
    return matriz[fila][col];
}

const Casilla& Tablero::getCasilla(int fila, int col) const {
    return matriz[fila][col];
}

void Tablero::getColorDinamica(float& r, float& g, float& b) const {
    switch (fase_actual) {
    case FaseCiclo::MEDIODIA:   r = 1.0f; g = 1.0f; b = 1.0f; break;
    case FaseCiclo::ATARDECER:  r = 0.6f; g = 0.7f; b = 0.9f; break;
    case FaseCiclo::ANOCHECER:  r = 0.2f; g = 0.4f; b = 0.7f; break;
    case FaseCiclo::MEDIANOCHE: r = 0.0f; g = 0.0f; b = 0.3f; break;
    case FaseCiclo::MADRUGADA:  r = 0.2f; g = 0.4f; b = 0.7f; break;
    case FaseCiclo::AMANECER:   r = 0.6f; g = 0.7f; b = 0.9f; break;
    }
}

FaseCiclo Tablero::getFase() const {
    return fase_actual;
}

bool Tablero::moverPersonaje(Personaje* p, int destinoX, int destinoY) {

    Casilla& casilladestino = getCasilla(destinoY, destinoX); //Obtenemos la casilla destino del personaje

    if (destinoX < 0 || destinoX >= COLUMNAS) //Mediante estos ifs, se comprueba que la casilla destino del personaje
        return false;                         // esta dentro del tablero
    if (destinoY < 0 || destinoY >= FILAS)
        return false;

    if (casilladestino.getPersonaje() == nullptr) //Casilla vacía, movimiento de la pieza normal
    {
        getCasilla(p->getPosY(), p->getPosX()).setPersonaje(nullptr);
        p->mover(destinoX, destinoY);
        casilladestino.setPersonaje(p);
        return true;
    }

    if (casilladestino.getPersonaje()->getTurno() == p->getTurno()) //Casilla ocupada por un personaje aliado, Repetir Turno
    {
        return false;
    }

    //Coincide en la casilla con un enemigo, se inicia combate
    pendienteOrigen_ = { p->getPosX(),p->getPosY() };
    pendienteDestino_ = { destinoX,destinoY };
    return false;
}

bool Tablero::hayChoquePendiente() const //Partida confirma que hay que activar la arena
{
    return pendienteOrigen_.x != -1;
}

void Tablero::getPendiente(int& origenX, int& origenY, int& destinoX, int& destinoY) const //obtiene las coordenadas del choque para poder llevarse a los personajes
{
    origenX = pendienteOrigen_.x;
    origenY = pendienteOrigen_.y;
    destinoX = pendienteDestino_.x;
    destinoY = pendienteDestino_.y;
}

void Tablero::limpiarPendiente() //Finaliza el combate y resetea las pendientes
{
    pendienteOrigen_ = { -1,-1 };
    pendienteDestino_ = { -1,-1 };
}