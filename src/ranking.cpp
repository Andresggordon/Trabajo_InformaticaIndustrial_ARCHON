/**
 * @file ranking.cpp
 * @brief Implementación del sistema de puntuación y renderizado del Top 10 de jugadores.
 */

#include "ranking.h"
#include <GL/freeglut.h>
#include <fstream>
#include <algorithm>

static const char* RUTA_FICHERO = "ranking.txt";

Ranking::Ranking() {
    fondo2 = new ETSIDI::Sprite("assets/menu_imagenes/fondo2.png", 0, 0, 800, 800);
    back = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 800, 800);
    boton_activo = 0;

    cargar();
}

void Ranking::cargar() {
    std::ifstream f(RUTA_FICHERO);
    if (!f.is_open()) return;

    entradas_.clear();
    std::string linea;
    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        size_t pos = linea.find(';');
        if (pos == std::string::npos) continue;
        try {
            int         puntuacion = std::stoi(linea.substr(0, pos));
            std::string nombre = linea.substr(pos + 1);
            entradas_.push_back({ nombre, puntuacion });
        }
        catch (...) {}
    }
}

void Ranking::guardar() const {
    std::ofstream f(RUTA_FICHERO);
    if (!f.is_open()) return;
    for (const auto& e : entradas_)
        f << e.puntuacion << ';' << e.nombre << '\n';
}

void Ranking::agregar(const std::string& nombre, int puntuacion) {
    entradas_.push_back({ nombre, puntuacion });

    std::sort(entradas_.begin(), entradas_.end(),
        [](const EntradaRanking& a, const EntradaRanking& b) {
            return a.puntuacion > b.puntuacion;
        });

    if ((int)entradas_.size() > MAX_ENTRADAS)
        entradas_.resize(MAX_ENTRADAS);

    guardar();
}

void Ranking::dibujarTextoCentrado(const std::string& texto, void* font,
    float y, float r, float g, float b) {
    int ancho = 0;
    for (char c : texto) ancho += glutBitmapWidth(font, c);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);   // sin esto, glRasterPos2f captura el color "iluminado" (sale negro)
    glColor3f(r, g, b);
    glRasterPos2f(-ancho / 2.0f, y);
    for (char c : texto)
        glutBitmapCharacter(font, c);
    glPopAttrib();
}

void Ranking::dibuja() {
    fondo2->draw();
    back->draw();

    // Titulo más grande
    dibujarTextoCentrado("RANKING", GLUT_BITMAP_TIMES_ROMAN_24,
        110, 1.0f, 0.85f, 0.0f);

    if (entradas_.empty()) {
        dibujarTextoCentrado("Sin puntuaciones aun",
            GLUT_BITMAP_HELVETICA_18, 55,
            0.7f, 0.7f, 0.7f);
        return;
    }

    int n = (int)entradas_.size();
    if (n > TOP_N) n = TOP_N;

    const float yInicio = 75.0f;
    const float dy = 22.0f;   // más espacio entre líneas por la fuente mayor
    for (int i = 0; i < n; ++i) {
        const auto& e = entradas_[i];
        std::string linea = std::to_string(i + 1) + ". " + e.nombre
            + "   " + std::to_string(e.puntuacion) + " pts";

        // Colores del podio bien contrastados sobre el fondo oscuro del ranking:
        //   oro    = amarillo dorado intenso
        //   plata  = gris azulado claro (claramente metalico, no confundible con blanco)
        //   bronce = cobre naranja saturado
        float r = 1.0f, g = 1.0f, b = 1.0f;
        if      (i == 0) { r = 1.00f; g = 0.82f; b = 0.00f; }   // oro
        else if (i == 1) { r = 0.70f; g = 0.78f; b = 0.92f; }   // plata
        else if (i == 2) { r = 0.87f; g = 0.50f; b = 0.13f; }   // bronce

        dibujarTextoCentrado(linea, GLUT_BITMAP_HELVETICA_18,
            yInicio - i * dy, r, g, b);
    }
}

void Ranking::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328)
        boton_activo = 1;
    else
        boton_activo = 0;
}

Modos_juego Ranking::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;

    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328) {
        ETSIDI::play("assets/sonidos/click.mp3");
        return Modos_juego::MENU;
    }
    return Modos_juego::Pantalla_Ranking;
}