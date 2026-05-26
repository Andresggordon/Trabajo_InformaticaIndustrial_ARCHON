#include "MotorGrafico.h"
#include "Partida.h"
#include "ArenaCombate.h"
#include "personaje.h"
#include "habilidades_profes.h"
#include <cmath>

float MotorGrafico::tiempoAviso = 0.0f;
std::string MotorGrafico::mensajeAviso = "";

void MotorGrafico::dibujar() {
    // Interpolación nearest neighbor para pixel art nítido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const Tablero& t = Partida::get_instance().tablero();
    dibujarTablero(t);
    dibujarPersonajes(t, Partida::get_instance().getPersonajeSeleccionado());
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
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float panelX1 = w * 0.02f;
    float panelX2 = w * 0.16f;
    float panelY1 = h * 0.72f;
    float panelY2 = h * 1.0f;
    float margenX  = w * 0.03f;
    float lineaAlto = (panelY2 - panelY1) / 8.0f;

    // Fondo
    glColor4f(0.08f, 0.08f, 0.08f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2f(panelX1, panelY1); glVertex2f(panelX2, panelY1);
    glVertex2f(panelX2, panelY2); glVertex2f(panelX1, panelY2);
    glEnd();

    // Borde
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(panelX1, panelY1); glVertex2f(panelX2, panelY1);
    glVertex2f(panelX2, panelY2); glVertex2f(panelX1, panelY2);
    glEnd();

    // Textos
    glColor3f(1.0f, 1.0f, 0.7f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 0.8f, "HABILIDADES");

    if (menu->puedeUsar(1)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 1.8f, "[1] Revivir");

    if (menu->puedeUsar(2)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 2.8f, "[2] Inmovilizar");

    if (menu->puedeUsar(0)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 3.8f, "[3] Teleport");

    if (menu->puedeUsar(3)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 4.8f, "[4] Curar");

    if (menu->puedeUsar(4)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 5.8f, "[5] Escudo");

    if (menu->puedeUsar(5)) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.4f, 0.4f, 0.4f);
    dibujarTextoBitmap(margenX, panelY1 + lineaAlto * 6.8f, "[6] Inmunidad");

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::dibujaInmovilizados(const Tablero& t) {
    dibujarRecuadroEstado(t, 1.0f, 0.0f, 0.0f, [](Personaje* p) { return p->getInmovilizado(); });
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

    // 1. Dibujar casillas disponibles (Relleno amarillo con parpadeo suave)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // PARPADEO DE LAS CASILLAS utilizando el tiempo del juego
    float tiempo_seg = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    // La función sin() devuelve valores entre -1 y 1. 
    float velocidad_parpadeo = 2.0f; // A mayor número, más rápido parpadea
    float alpha_dinamico = 0.33f + 0.20f * sin(tiempo_seg * velocidad_parpadeo);

    //OpenGL dibujará teniendo en cuenta el parámetro de tiempo calculado
    glColor4f(0.7f, 1.0f, 0.0f, alpha_dinamico);

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

void MotorGrafico::dibujaEscudos(const Tablero& t) {
    dibujarRecuadroEstado(t, 0.0f, 0.4f, 1.0f, [](Personaje* p) { return (bool)p->getEscudo(); });
}

void MotorGrafico::dibujaInmunidad(const Tablero& t) {
    dibujarRecuadroEstado(t, 1.0f, 0.85f, 0.0f, [](Personaje* p) { return p->getInmune(); });
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

void MotorGrafico::dibujarPersonajes(const Tablero& t, Personaje* seleccionado) {
    const auto& dibujos = Partida::get_instance().getDibujos();

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            float x = INICIO_X + col * TAM;
            float y = INICIO_Y + fila * TAM;
            Personaje* p = t.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
                for (auto d : dibujos) {
                    if (d->getPersonaje() == p) { d->dibujar(x, y); break; }
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

    // Las barras de vida se mapean por POSICION VISUAL (izq = mañana, dcha = tarde),
    // no por rol semantico (local/invasor), porque local_/invasor_ depende de quien
    // inicio el choque mientras que las piezas se colocan SIEMPRE: mañana izq, tarde dcha.
    Personaje* piezaIzq  = nullptr;  // ira al lado izq (mañana)
    Personaje* piezaDcha = nullptr;  // ira al lado dcho (tarde)
    if (local != nullptr) {
        if (local->getTurno() == Turno::TURNO_DE_MANANA) piezaIzq = local;
        else                                             piezaDcha = local;
    }
    if (invasor != nullptr) {
        if (invasor->getTurno() == Turno::TURNO_DE_MANANA) piezaIzq = invasor;
        else                                               piezaDcha = invasor;
    }
    dibujarBarrasHP(piezaIzq, piezaDcha);

    arena->dibujarProyectiles();
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

void MotorGrafico::dibujarBarraVida(float x, float y, Personaje* p) {
    if (p == nullptr || !p->estaVivo()) return;

    float porcentaje = p->getPorcentajeVida();
    float anchoTotal = TAM * 0.8f;
    float anchoVida = anchoTotal * porcentaje;
    float barraX = x + TAM * 0.1f;
    float barraY = y + TAM - 6.0f;
    float alturaBarra = 4.0f;

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Fondo gris
    glColor4f(0.2f, 0.2f, 0.2f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(barraX, barraY);
    glVertex2f(barraX + anchoTotal, barraY);
    glVertex2f(barraX + anchoTotal, barraY + alturaBarra);
    glVertex2f(barraX, barraY + alturaBarra);
    glEnd();

    // Color según porcentaje
    setColorVida(porcentaje);

    glBegin(GL_QUADS);
    glVertex2f(barraX, barraY);
    glVertex2f(barraX + anchoVida, barraY);
    glVertex2f(barraX + anchoVida, barraY + alturaBarra);
    glVertex2f(barraX, barraY + alturaBarra);
    glEnd();

    glDisable(GL_BLEND);
}

void MotorGrafico::dibujarVidaTexto(float x, float y, Personaje* p) {
    if (p == nullptr) return;

    std::string texto = std::to_string(p->getVidaActual()) + "/" + std::to_string(p->getVidaMax());

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    float px = (x + TAM * 0.5f + 400.0f) / 800.0f * (float)w;
    float py = (float)h - ((y + TAM + 10.0f + 400.0f) / 800.0f * (float)h);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(px - 12.0f, py);
    for (char c : texto) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::dibujaBarrasVida(const Tablero& t, Personaje* seleccionado) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int fila = 0; fila < Tablero::FILAS; fila++) {
        for (int col = 0; col < Tablero::COLUMNAS; col++) {
            float x = INICIO_X + col * TAM;
            float y = INICIO_Y + fila * TAM;
            Personaje* p = t.getCasilla(fila, col).getPersonaje();
            if (p != nullptr) {
                dibujarBarraVida(x, y, p);
                if (p == seleccionado) dibujarVidaTexto(x, y, p);
            }
        }
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::dibujarVidaPanel(Personaje* p) {
    if (p == nullptr) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    float porcentaje = p->getPorcentajeVida();
    std::string texto = std::to_string(p->getVidaActual()) + " / " + std::to_string(p->getVidaMax());


    float panelX = w * 0.877f;
    float panelAncho = w * 0.1f;
    float barraY = h * 0.55f;   
    float barraAlto = h * 0.020f;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Fondo oscuro de la barra
    glColor4f(0.15f, 0.15f, 0.15f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(panelX, barraY);
    glVertex2f(panelX + panelAncho, barraY);
    glVertex2f(panelX + panelAncho, barraY + barraAlto);
    glVertex2f(panelX, barraY + barraAlto);
    glEnd();

    // Barra de vida coloreada
    setColorVida(porcentaje);

    glBegin(GL_QUADS);
    glVertex2f(panelX, barraY);
    glVertex2f(panelX + panelAncho * porcentaje, barraY);
    glVertex2f(panelX + panelAncho * porcentaje, barraY + barraAlto);
    glVertex2f(panelX, barraY + barraAlto);
    glEnd();

    glDisable(GL_BLEND);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(panelX + panelAncho * 0.25f, barraY + barraAlto + h * 0.025f);
    for (char c : texto) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::dibujarBarrasHP(Personaje* local, Personaje* invasor) {
    Personaje* manana = (local != nullptr && local->getTurno() == Turno::TURNO_DE_MANANA)
        ? local : invasor;
    Personaje* tarde = (local != nullptr && local->getTurno() == Turno::TURNO_DE_TARDE)
        ? local : invasor;
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

    // ── Barra HP local (izquierda) ──────────────
    float xIniL = -305.f, xFinL = -94.f;
    float ySupL = -350.f, yInfL = -369.f;

    if (manana != nullptr) {
        float pct = manana->getPorcentajeVida();
        float xVidaL = xIniL + (xFinL - xIniL) * pct;

        // Fondo rojo (vida perdida)
        glColor3f(0.6f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(xIniL, yInfL);
        glVertex2f(xFinL, yInfL);
        glVertex2f(xFinL, ySupL);
        glVertex2f(xIniL, ySupL);
        glEnd();

        // Verde (vida restante)
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(xIniL, yInfL);
        glVertex2f(xVidaL, yInfL);
        glVertex2f(xVidaL, ySupL);
        glVertex2f(xIniL, ySupL);
        glEnd();
    }

    // ── Barra HP invasor (derecha) ───────────────
    float xIniR = 138.f, xFinR = 347.f;
    float ySupR = -350.f, yInfR = -369.f;

    if (tarde != nullptr) {
        float pct = tarde->getPorcentajeVida();
        float xVidaR = xIniR + (xFinR - xIniR) * pct;

        // Fondo rojo (vida perdida)
        glColor3f(0.6f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(xIniR, yInfR);
        glVertex2f(xFinR, yInfR);
        glVertex2f(xFinR, ySupR);
        glVertex2f(xIniR, ySupR);
        glEnd();

        // Verde (vida restante)
        glColor3f(0.0f, 0.8f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(xIniR, yInfR);
        glVertex2f(xVidaR, yInfR);
        glVertex2f(xVidaR, ySupR);
        glVertex2f(xIniR, ySupR);
        glEnd();
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujaAviso() {
    if (tiempoAviso <= 0.0f) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    // Fade: empieza a desvanecerse en el último 30% del tiempo
    float alpha = 1.0f;
    if (tiempoAviso < 0.6f)
        alpha = tiempoAviso / 0.6f;  // de 1 a 0 en los últimos 0.6 segundos

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float cx = w * 0.55f, cy = h * 0.38f; 
    float bw = w * 0.32f, bh = h * 0.07f;

    // Sombra negra desplazada (da profundidad)
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f * alpha);
    glBegin(GL_QUADS);
    glVertex2f(cx - bw / 2 + 4, cy - bh / 2 + 4);
    glVertex2f(cx + bw / 2 + 4, cy - bh / 2 + 4);
    glVertex2f(cx + bw / 2 + 4, cy + bh / 2 + 4);
    glVertex2f(cx - bw / 2 + 4, cy + bh / 2 + 4);
    glEnd();

    // Fondo rojo oscuro
    glColor4f(0.55f, 0.05f, 0.05f, 0.88f * alpha);
    glBegin(GL_QUADS);
    glVertex2f(cx - bw / 2, cy - bh / 2);
    glVertex2f(cx + bw / 2, cy - bh / 2);
    glVertex2f(cx + bw / 2, cy + bh / 2);
    glVertex2f(cx - bw / 2, cy + bh / 2);
    glEnd();

    // Borde blanco
    glColor4f(1.0f, 1.0f, 1.0f, 0.9f * alpha);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx - bw / 2, cy - bh / 2);
    glVertex2f(cx + bw / 2, cy - bh / 2);
    glVertex2f(cx + bw / 2, cy + bh / 2);
    glVertex2f(cx - bw / 2, cy + bh / 2);
    glEnd();

    // Línea decorativa superior dentro del cuadro
    glColor4f(1.0f, 0.4f, 0.4f, 0.6f * alpha);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(cx - bw / 2 + 8, cy - bh / 2 + 6);
    glVertex2f(cx + bw / 2 - 8, cy - bh / 2 + 6);
    glEnd();

    // Texto centrado (calcula el ancho aproximado: ~10px por carácter con Helvetica 18)
    float textoAncho = mensajeAviso.size() * 10.0f;
    float textoX = cx - textoAncho / 2.0f;
    float textoY = cy + 6.0f;

    // Sombra del texto
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f * alpha);
    glRasterPos2f(textoX + 1.5f, textoY + 1.5f);
    for (char c : mensajeAviso)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    // Texto principal blanco
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glRasterPos2f(textoX, textoY);
    for (char c : mensajeAviso)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void MotorGrafico::dibujarRecuadroEstado(const Tablero& t, float r, float g, float b,
    std::function<bool(Personaje*)> condicion) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);

    glColor3f(r, g, b);
    glLineWidth(4.0f);

    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            Personaje* p = t.getCasilla(f, c).getPersonaje();
            if (p && condicion(p)) {
                float x = INICIO_X + c * TAM;
                float y = INICIO_Y + f * TAM;
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);         glVertex2f(x + TAM, y);
                glVertex2f(x + TAM, y + TAM); glVertex2f(x, y + TAM);
                glEnd();
            }
        }
    }
    glPopMatrix();
    glPopAttrib();
}

void MotorGrafico::setColorVida(float porcentaje) {
    if (porcentaje > 0.6f)      glColor4f(0.2f, 0.85f, 0.2f, 0.9f);
    else if (porcentaje > 0.3f) glColor4f(1.0f, 0.65f, 0.0f, 0.9f);
    else                        glColor4f(0.9f, 0.1f, 0.1f, 0.9f);
}