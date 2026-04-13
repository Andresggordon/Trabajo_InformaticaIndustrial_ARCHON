#include "PantallaFinal.h"
#include <GL/freeglut.h>
#include <string>

PantallaFinal::PantallaFinal() {
    // Reutilizamos el fondo2 del ranking (mismo estilo visual)
    fondo      = new ETSIDI::Sprite("assets/menu_imagenes/fondo2.png", 0, 0, 600, 600);
    boton_menu = new ETSIDI::Sprite("assets/menu_imagenes/back.png",   0, 0, 600, 600);

    resultado        = ResultadoPartida::VICTORIA_MANANA;
    puntuacion_final = 0;
    nombre_ganador   = "Jugador";
    boton_activo     = 0;
}

void PantallaFinal::setResultado(ResultadoPartida r, int puntuacion,
                                  const std::string& nombre) {
    resultado        = r;
    puntuacion_final = puntuacion;
    nombre_ganador   = nombre;
}

// ── Texto normal (Helvetica 18) ─────────────────────────────────────────────
void PantallaFinal::dibujarTexto(const std::string& texto, float x, float y,
                                  float r, float g, float b) {
    // Guardamos el estado de OpenGL igual que en Tablero_vista
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (char c : texto)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glPopAttrib();
}

// ── Texto grande para el titulo (Times Roman 24) ─────────────────────────────
void PantallaFinal::dibujarTextoGrande(const std::string& texto, float x, float y,
                                        float r, float g, float b) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (char c : texto)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    glPopAttrib();
}

void PantallaFinal::dibuja() {
    fondo->draw();
    boton_menu->draw();

    // ── Linea decorativa superior ──────────────────────────────────────────
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(1.0f, 0.85f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-200, 175); glVertex2f(200, 175);
    glEnd();
    glPopAttrib();

    // ── Titulo: quien ha ganado ────────────────────────────────────────────
    if (resultado == ResultadoPartida::VICTORIA_MANANA) {
        dibujarTextoGrande("TURNO DE MANANA GANA!",
                           -165, 130, 1.0f, 0.85f, 0.0f); // amarillo
    } else {
        dibujarTextoGrande("TURNO DE TARDE GANA!",
                           -155, 130, 0.3f, 0.6f, 1.0f);  // azul claro
    }

    // ── Nombre del ganador ─────────────────────────────────────────────────
    dibujarTexto("Ganador:  " + nombre_ganador,
                 -100, 70, 1.0f, 1.0f, 1.0f);

    // ── Puntuacion ─────────────────────────────────────────────────────────
    dibujarTexto("Puntuacion:  " + std::to_string(puntuacion_final),
                 -100, 30, 1.0f, 1.0f, 0.2f);

    // ── Instruccion como ganar puntos para que el jugador entienda ─────────
    dibujarTexto("La puntuacion depende de piezas vivas y velocidad",
                 -195, -30, 0.6f, 0.6f, 0.6f);

    // ── Instruccion boton ──────────────────────────────────────────────────
    dibujarTexto("Pulsa BACK para volver al menu",
                 -120, -80, 0.5f, 0.5f, 0.5f);

    // ── Linea decorativa inferior ──────────────────────────────────────────
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-200, -110); glVertex2f(200, -110);
    glEnd();
    glPopAttrib();
}

void PantallaFinal::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    // Mismo area del boton "back" que en el resto de pantallas
    boton_activo = (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235) ? 1 : 0;
}

Modos_juego PantallaFinal::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 225 && cx <= 275 && cy >= -265 && cy <= -235) {
        ETSIDI::play("assets/sonidos/click.mp3");
        ETSIDI::stopMusica();
        ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
        return Modos_juego::MENU;
    }
    return Modos_juego::Pantalla_Final;
}
