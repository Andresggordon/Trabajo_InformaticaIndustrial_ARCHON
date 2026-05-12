#include "MotorGrafico.h"
#include "Partida.h"
#include "ArenaCombate.h"

MotorGrafico::MotorGrafico() {
    tam = TAM;
    inicioX = INICIO_X;
    inicioY = INICIO_Y;
}

void MotorGrafico::dibujar() {
    // Interpolación nearest neighbor para pixel art nítido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    const Tablero& t = Partida::get_instance().tablero();  // accede al tablero via Singleton
    dibujarTablero(t);
    dibujarPersonajes(t);
}

void MotorGrafico::dibujarTablero(const Tablero& t) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            float x = inicioX + col * tam;
            float y = inicioY + fila * tam;
            EstadoCasilla tipo = t.getCasilla(fila, col).getEstado();

            if (tipo == EstadoCasilla::BLANCA_FIJA) {
                dibujaCuadrado(x, y, 1.0f, 1.0f, 1.0f);
            }
            else if (tipo == EstadoCasilla::AZUL_FIJA) {
                dibujaCuadrado(x, y, 0.0f, 0.0f, 0.3f);
            }
            else {
                float r, g, b;
                t.getColorDinamica(r, g, b);
                dibujaCuadrado(x, y, r, g, b);
            }
        }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujarPersonajes(const Tablero& t) {
    const auto& dibujos = Partida::get_instance().getDibujos();

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            float x = inicioX + col * tam;
            float y = inicioY + fila * tam;

            Personaje* p = t.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
                // Buscar el DibujoPersonaje que corresponde a este personaje
                for (auto d : dibujos) {
                    if (d->getPersonaje() == p) {
                        d->dibujar(x, y);
                        break;
                    }
                }
            }
        }
    }
}

void MotorGrafico::dibujaCuadrado(float x, float y, float r, float g, float b) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + tam, y);
    glVertex2f(x + tam, y + tam);
    glVertex2f(x, y + tam);
    glEnd();
}

void MotorGrafico::dibujarArena() {
    // Obtener los personajes de la arena
    extern ArenaCombate* arena;
    Personaje* local = arena->getLocal();
    Personaje* invasor = arena->getInvasor();

    dibujarFondoArena();
    dibujarPersonajesArena(local, invasor);
}

void MotorGrafico::dibujarFondoArena() {
    // El fondo lo dibuja ArenaCombate
    extern ArenaCombate* arena;
    arena->dibuja();
}

void MotorGrafico::dibujarPersonajesArena(Personaje* local, Personaje* invasor) {
    const auto& dibujos = Partida::get_instance().getDibujos();
    extern ArenaCombate* arena;

    // Convertir posición en cuadrícula a coordenadas OpenGL
    float tamCasilla = 60.0f;
    float inicioArenaX = -240.0f;
    float inicioArenaY = -240.0f;

    if (local != nullptr) {
        float x = inicioArenaX + arena->getPosLocal().columna * tamCasilla;
        float y = inicioArenaY + arena->getPosLocal().fila * tamCasilla;
        for (auto d : dibujos) {
            if (d->getPersonaje() == local) {
                d->dibujar(x, y);
                break;
            }
        }
    }

    if (invasor != nullptr) {
        float x = inicioArenaX + arena->getPosInvasor().columna * tamCasilla;
        float y = inicioArenaY + arena->getPosInvasor().fila * tamCasilla;
        for (auto d : dibujos) {
            if (d->getPersonaje() == invasor) {
                d->dibujar(x, y);
                break;
            }
        }
    }
}




