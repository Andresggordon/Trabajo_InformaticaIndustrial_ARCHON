#include "MotorGrafico.h"
#include "Partida.h"
#include "ArenaCombate.h"
#include "personaje.h"
#include "habilidades_profes.h"

void MotorGrafico::dibujar() {
    // Interpolación nearest neighbor para pixel art nítido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const Tablero& t = Partida::get_instance().tablero();
    dibujarTablero(t);
    dibujarPersonajes(t);
}

void MotorGrafico::dibujarTextoBitmap(float x, float y, const char* texto) {
    glRasterPos2f(x, y);
    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto);
        ++texto;
    }
}

void MotorGrafico::dibujaHabilidades(Personaje* p, bool modo_t, bool modo_i, bool modo_r) {
    if (p == nullptr || modo_t || modo_i || modo_r) return;
    Menu_habilidades* menu = p->getMenu();
    if (menu == nullptr) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Configurar cámara 2D
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // --- LA SOLUCIÓN AL BUG ---
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);     // ¡CLAVE! Evita que el texto se vuelva negro
    glDisable(GL_DEPTH_TEST);   // Asegura que el menú esté por encima de todo el juego
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Dibujar el fondo del panel
    glColor4f(0.08f, 0.08f, 0.08f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2f(20, h - 170); glVertex2f(280, h - 170);
    glVertex2f(280, h - 35);  glVertex2f(20, h - 35);
    glEnd();

    // 2. Dibujar el borde
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(20, h - 170); glVertex2f(280, h - 170);
    glVertex2f(280, h - 35);  glVertex2f(20, h - 35);
    glEnd();

    // 3. Dibujar los Textos de habilidades 
    glColor3f(1.0f, 1.0f, 0.7f);
    dibujarTextoBitmap(32, h - 148, "HABILIDADES");

    if (menu->puedeUsarRevivir()) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(35, h - 112, "[1] Revivir");

    if (menu->puedeUsarInmovilizar()) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(35, h - 84, "[2] Inmovilizar");

    if (menu->puedeUsarTeleport()) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(35, h - 56, "[3] Teleport");

    // Limpiar matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::dibujaInmovilizados(const Tablero& t) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            Personaje* p = t.getCasilla(f, c).getPersonaje();
            if (p != nullptr && p->getInmovilizado()) {
                float x = INICIO_X + c * TAM;
                float y = INICIO_Y + f * TAM;
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y); glVertex2f(x + TAM, y);
                glVertex2f(x + TAM, y + TAM); glVertex2f(x, y + TAM);
                glEnd();
            }
        }
    }
    glPopMatrix();
    glPopAttrib();
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

    float TAMCasilla = 45.0f;
    float inicioArenaX = -245.0f;
    float inicioArenaY = -245.0f;

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



