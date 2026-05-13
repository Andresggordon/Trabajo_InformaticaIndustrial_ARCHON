#include "Partida.h"
#include "MotorGrafico.h"
#include <GL/freeglut.h>
#include "tipo_personaje.h"
#include "Modos_juego.h"
#include "ArenaCombate.h"
#include <string>
extern ArenaCombate* arena;


Partida::Partida() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 800, 800);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
    mostrar_popup = false;
    boton_activo = 0;
}

void Partida::dibuja() {
    fondo->draw();  // solo el fondo
}

void Partida::dibujaextra() {
    abandonar_partida->draw();  // exit encima de todo
    if (mostrar_popup)
        popup_salir->draw();
}


void Partida::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (!mostrar_popup) {
        if (cx >= 209 && cx <= 289 && cy >= -275 && cy <= -252)
            boton_activo = 1;
        else
            boton_activo = 0;
    }
    else {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5)
            boton_activo = 2;
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            boton_activo = 3;
        else
            boton_activo = 0;
    }
}

Modos_juego Partida::click(int x, int y) {

    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;

    ETSIDI::play("assets/sonidos/click.mp3");

    float cx = ((x - offsetX) / (float)tam) * 800.0f - 400.0f;
    float cy = 400.0f - ((y - offsetY) / (float)tam) * 800.0f;

    // EXIT - se comprueba SIEMPRE antes que nada
    if (!mostrar_popup) {
        if (cx >= 209.0f && cx <= 289.0f && cy >= -275.0f && cy <= -252.0f) {
            mostrar_popup = true;
            return Modos_juego::Partida;
        }
    }
    else {
        if (cx >= -153.0f && cx <= -57.0f && cy >= -43.0f && cy <= -5.0f) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
            mostrar_popup = false;
            return Modos_juego::MENU;
        }
        if (cx >= 15.0f && cx <= 108.0f && cy >= -46.0f && cy <= -4.0f) {
            mostrar_popup = false;
            return Modos_juego::Partida;
        }
        return Modos_juego::Partida;  // popup abierto bloquea tablero
    }

    // TABLERO
    float tam_casilla = MotorGrafico::TAM;
    float inicioX = MotorGrafico::INICIO_X;
    float inicioY = MotorGrafico::INICIO_Y;
    int col = (int)((cx - inicioX) / tam_casilla);
    int fil = (int)((cy - inicioY) / tam_casilla);

    if (col >= 0 && col < 9 && fil >= 0 && fil < 9)
        return procesarClickTablero(fil, col);

    return Modos_juego::Partida;
}

Modos_juego Partida::procesarClickTablero(int fil, int col) {
    Casilla& casilla = tab_.getCasilla(fil, col);

    if (modo_teleport) {
        if (personaje_seleccionado == nullptr) {
            modo_teleport = false;
            return Modos_juego::Partida;;
        }
        Menu_habilidades* menu = personaje_seleccionado->getMenu();
        if (menu != nullptr && menu->usarTeleport(personaje_seleccionado, &casilla)) {
            turno_actual = 1 - turno_actual;
        }
        modo_teleport = false;
        personaje_seleccionado = nullptr;
        es_lider_seleccionado = false;
        return Modos_juego::Partida;;
    }

    if (modo_inmovilizar) {
        if (personaje_seleccionado == nullptr) {
            modo_inmovilizar = false;
            return Modos_juego::Partida;;
        }
        Menu_habilidades* menu = personaje_seleccionado->getMenu();
        Personaje* objetivo = casilla.getPersonaje();

        if (menu != nullptr && menu->usarInmovilizar(personaje_seleccionado, objetivo)) {
            turno_actual = 1 - turno_actual;
        }
        modo_inmovilizar = false;
        personaje_seleccionado = nullptr;
        es_lider_seleccionado = false;
        return Modos_juego::Partida;
    }

    if (modo_revivir) {
        if (personaje_seleccionado == nullptr) {
            modo_revivir = false;
            return Modos_juego::Partida;
        }
        Menu_habilidades* menu = personaje_seleccionado->getMenu();
        Personaje* objetivo = casilla.getPersonaje();

        if (menu != nullptr && menu->usarRevivir(personaje_seleccionado, objetivo)) {
            turno_actual = 1 - turno_actual;
        }
        modo_revivir = false;
        personaje_seleccionado = nullptr;
        es_lider_seleccionado = false;
        return Modos_juego::Partida;
    }

    if (personaje_seleccionado == nullptr) {
        Personaje* p = casilla.getPersonaje();
        if (p != nullptr && p->estaVivo()) {
            bool es_manana = (p->getTurno() == Turno::TURNO_DE_MANANA);
            bool turno_ok = (turno_actual == 0 && es_manana) ||
                (turno_actual == 1 && !es_manana);
            if (turno_ok) {
                personaje_seleccionado = p;
                es_lider_seleccionado = (p->getMenu() != nullptr);
            }
        }
    }
    else {
        ResultadoMover res = tab_.moverPersonaje(personaje_seleccionado, casilla);

        if (res == ResultadoMover::OK) {
            turno_actual = 1 - turno_actual;
            for (auto p : personajes)
                p->decrementarInmovilizacion();
        }
        else if (res == ResultadoMover::CHOQUE) {
            arena->iniciarCombate(
                tab_.getPendienteLocal(),
                tab_.getPendienteInvasor(),
                modo_actual
            );
            tab_.limpiarPendiente();
            personaje_seleccionado = nullptr;
            es_lider_seleccionado = false;
            return Modos_juego::Arena_Combate;
        }

        personaje_seleccionado = nullptr;
        es_lider_seleccionado = false;
        return Modos_juego::Partida;
    }
    return Modos_juego::Partida;
}

void Partida::tecladoHabilidades(unsigned char key) {
    if (!es_lider_seleccionado) return;
    if (personaje_seleccionado == nullptr) return;

    Menu_habilidades* menu = personaje_seleccionado->getMenu();
    if (menu == nullptr) return;

    modo_revivir = false;
    modo_inmovilizar = false;
    modo_teleport = false;

    switch (key) {
    case '1':
        if (menu->puedeUsarRevivir()) {
            modo_revivir = true;
        }
        break;

    case '2':
        if (menu->puedeUsarInmovilizar()) {
            modo_inmovilizar = true;
        }
        break;

    case '3':
        if (menu->puedeUsarTeleport()) {
            modo_teleport = true;
        }
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void Partida::dibujaSeleccion() {

    if (personaje_seleccionado == nullptr) return;

    Casilla* c = personaje_seleccionado->getCasillaActual();
    float tam = MotorGrafico::TAM;
    float inicioX = MotorGrafico::INICIO_X;
    float inicioY = MotorGrafico::INICIO_Y;

    float x0 = inicioX + c->getCol() * tam;
    float y0 = inicioY + c->getFila() * tam;

    glPushAttrib(GL_ALL_ATTRIB_BITS);  // guarda todo el estado
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.0f, 1.0f, 0.0f);  // verde puro
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x0, y0);
    glVertex2f(x0 + tam, y0);
    glVertex2f(x0 + tam, y0 + tam);
    glVertex2f(x0, y0 + tam);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();  // restaura todo el estado anterior
}

void Partida::dibujarTextoBitmap(float x, float y, const char* texto) {
    glRasterPos2f(x, y);
    while (*texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto);
        ++texto;
    }
}

void Partida::dibujaHabilidades() {
    if (!es_lider_seleccionado) return;
    if (personaje_seleccionado == nullptr) return;

    Menu_habilidades* menu = personaje_seleccionado->getMenu();
    if (menu == nullptr) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    float panelX = 20.0f;
    float panelY = h - 170.0f;
    float panelW = 260.0f;
    float panelH = 135.0f;

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

    // Fondo
    glColor4f(0.08f, 0.08f, 0.08f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2f(panelX, panelY);
    glVertex2f(panelX + panelW, panelY);
    glVertex2f(panelX + panelW, panelY + panelH);
    glVertex2f(panelX, panelY + panelH);
    glEnd();

    // Borde
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(panelX, panelY);
    glVertex2f(panelX + panelW, panelY);
    glVertex2f(panelX + panelW, panelY + panelH);
    glVertex2f(panelX, panelY + panelH);
    glEnd();

    // Título
    glColor3f(1.0f, 1.0f, 0.7f);
    dibujarTextoBitmap(panelX + 12.0f, panelY + 22.0f, "HABILIDADES");

    // Línea separadora
    glBegin(GL_LINES);
    glVertex2f(panelX + 10.0f, panelY + 32.0f);
    glVertex2f(panelX + panelW - 10.0f, panelY + 32.0f);
    glEnd();

    // [1] Revivir
    if (menu->puedeUsarRevivir()) glColor3f(0.9f, 0.9f, 0.9f);
    else                          glColor3f(0.45f, 0.45f, 0.45f);
    dibujarTextoBitmap(panelX + 15.0f, panelY + 58.0f, "[1] Revivir");

    // [2] Inmovilizar
    if (menu->puedeUsarInmovilizar()) glColor3f(0.9f, 0.9f, 0.9f);
    else                              glColor3f(0.45f, 0.45f, 0.45f);
    dibujarTextoBitmap(panelX + 15.0f, panelY + 86.0f, "[2] Inmovilizar");

    // [3] Teleport
    if (menu->puedeUsarTeleport()) glColor3f(0.9f, 0.9f, 0.9f);
    else                           glColor3f(0.45f, 0.45f, 0.45f);
    dibujarTextoBitmap(panelX + 15.0f, panelY + 114.0f, "[3] Teleport");

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();
}
void Partida::teclado(unsigned char key) {
    if (key == 32)
        tab_.avanzarCiclo();
    if (key == 27)
        mostrar_popup = false;
}

void Partida::reset() {

    //LIMPIAMOS TODAS LAS CASILLAS
    for (int fila = 0; fila < Tablero::FILAS; fila++)
        for (int col = 0; col < Tablero::COLUMNAS; col++)
            tab_.getCasilla(fila, col).setPersonaje(nullptr);

    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false;
    boton_activo = 0;


    modo_actual = modo_juego;      // 1=1jugador, 2=2jugadores
    turno_actual = turno_inicio;   // 1=mañana primero, 2=tarde primero


    // Limpiar listas por si reset() se llama más de una vez
    for (auto p : personajes) delete p;
    for (auto d : dibujos)    delete d;
    personajes.clear();
    dibujos.clear();

    // (FILAS , COLUMNAS)
    // ── Equipo mañana  ──
    personajes.push_back(new Profesor_SS(tab_.getCasilla(4, 0)));
   
    personajes.push_back(new PLC(tab_.getCasilla(1, 0)));
    personajes.push_back(new PLC(tab_.getCasilla(7, 0)));

    personajes.push_back(new Moto_electrica(tab_.getCasilla(2, 0)));
    personajes.push_back(new Moto_electrica(tab_.getCasilla(6, 0)));

    personajes.push_back(new Fuente_de_tension_de_bateria(tab_.getCasilla(3, 0)));

    personajes.push_back(new Copilot(tab_.getCasilla(5, 0)));

    personajes.push_back(new Microprocesador_M(tab_.getCasilla(0, 0)));
    personajes.push_back(new Microprocesador_M(tab_.getCasilla(8, 0)));

    personajes.push_back(new Multimetro(tab_.getCasilla(0, 1)));
    personajes.push_back(new Multimetro(tab_.getCasilla(8, 1)));
    for (int i = 1; i <= 7; i++)
    {
        personajes.push_back(new Circuito_integrado_M(tab_.getCasilla(i, 1)));

    }
    // (FILAS , COLUMNAS)

    // ── Equipo tarde ── 
    personajes.push_back(new Profesor_MH(tab_.getCasilla(4, 8)));

    personajes.push_back(new Microprocesador_T(tab_.getCasilla(0, 8)));
    personajes.push_back(new Microprocesador_T(tab_.getCasilla(8, 8)));

    personajes.push_back(new Osciloscopio(tab_.getCasilla(0, 7)));
    personajes.push_back(new Osciloscopio(tab_.getCasilla(8, 7)));


    personajes.push_back(new Brazo_robot(tab_.getCasilla(1, 8)));
    personajes.push_back(new Brazo_robot(tab_.getCasilla(7, 8)));

    personajes.push_back(new Fuente_de_corriente(tab_.getCasilla(3, 8)));

    personajes.push_back(new Moto_petrol(tab_.getCasilla(2, 8)));
    personajes.push_back(new Moto_petrol(tab_.getCasilla(6, 8)));

    personajes.push_back(new Gemini(tab_.getCasilla(5, 8)));

	for (int i = 1; i <= 7; i++)
    {
        personajes.push_back(new Circuito_integrado_T(tab_.getCasilla(i, 7)));
    }

    // Crear un DibujoPersonaje por cada personaje
    for (auto p : personajes)
        dibujos.push_back(new DibujoPersonaje(p));
}