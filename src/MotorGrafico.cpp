
#include "MotorGrafico.h"
#include "Partida.h"
#include "ArenaCombate.h"
#include "personaje.h" // Necesario para acceder a los métodos de Personaje



void MotorGrafico::dibujar() {
    // Interpolación nearest neighbor para pixel art nítido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const Tablero& t = Partida::get_instance().tablero();
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
            float x = INICIO_X + col * TAM;
            float y = INICIO_Y + fila * TAM;
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
            float x = INICIO_X + col * TAM;
            float y = INICIO_Y + fila * TAM;

            Personaje* p = t.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
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
    glVertex2f(x + TAM, y);
    glVertex2f(x + TAM, y + TAM);
    glVertex2f(x, y + TAM);
    glEnd();
}

void MotorGrafico::dibujarArena() {
    extern ArenaCombate* arena;
    Personaje* local = arena->getLocal();
    Personaje* invasor = arena->getInvasor();

    dibujarFondoArena();
    dibujarPersonajesArena(local, invasor);
}

void MotorGrafico::dibujarFondoArena() {
    extern ArenaCombate* arena;
    arena->dibuja();
}

void MotorGrafico::dibujarPersonajesArena(Personaje* local, Personaje* invasor) {
    const auto& dibujos = Partida::get_instance().getDibujos();
    extern ArenaCombate* arena;

    float TAMCasilla = 60.0f;
    float inicioArenaX = -300.0f;
    float inicioArenaY = -300.0f;

    if (local != nullptr) {
        float x = inicioArenaX + arena->getPosLocal().columna * TAMCasilla;
        float y = inicioArenaY + arena->getPosLocal().fila * TAMCasilla;
        for (auto d : dibujos) {
            if (d->getPersonaje() == local) {
                d->dibujar(x, y);
                break;
            }
        }
    }

    if (invasor != nullptr) {
        float x = inicioArenaX + arena->getPosInvasor().columna * TAMCasilla;
        float y = inicioArenaY + arena->getPosInvasor().fila * TAMCasilla;
        for (auto d : dibujos) {
            if (d->getPersonaje() == invasor) {
                d->dibujar(x, y);
                break;
            }
        }
    }
}

void MotorGrafico::dibujaSeleccion(Personaje* seleccionado, const std::vector<Casilla*>& iluminadas) {
    if (seleccionado == nullptr) return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 1. Dibujar casillas disponibles (Relleno amarillo translúcido)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 0.0f, 0.4f);

    glBegin(GL_QUADS);
    for (Casilla* c : iluminadas) {
        float cX = INICIO_X + c->getCol() * TAM;
        float cY = INICIO_Y + c->getFila() * TAM;

        glVertex2f(cX, cY);
        glVertex2f(cX + TAM, cY);
        glVertex2f(cX + TAM, cY + TAM);
        glVertex2f(cX, cY + TAM);
    }
    glEnd();

    glDisable(GL_BLEND);

    // 2. Dibujar recuadro verde del personaje seleccionado
    Casilla* c = seleccionado->getCasillaActual();
    if (c != nullptr) {
        float x0 = INICIO_X + c->getCol() * TAM;
        float y0 = INICIO_Y + c->getFila() * TAM;

        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(4.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x0, y0);
        glVertex2f(x0 + TAM, y0);
        glVertex2f(x0 + TAM, y0 + TAM);
        glVertex2f(x0, y0 + TAM);
        glEnd();
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujaHabilidades() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Boton Revivir (izquierda)
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-390, -390); glVertex2f(-150, -390);
    glVertex2f(-150, -340); glVertex2f(-390, -340);
    glEnd();

    // Boton Inmovilizar (centro)
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-80, -390); glVertex2f(80, -390);
    glVertex2f(80, -340);  glVertex2f(-80, -340);
    glEnd();

    // Boton Teleport (derecha)
    glColor3f(0.2f, 0.2f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(150, -390); glVertex2f(390, -390);
    glVertex2f(390, -340); glVertex2f(150, -340);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPopAttrib();
}
