#include "PantallaFinal.h"
#include <GL/freeglut.h>
#include <string>

PantallaFinal::PantallaFinal() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/pantalla_final.png", 0, 0, 800, 800);
    creditos_ = new ETSIDI::Sprite("assets/menu_imagenes/creditos.png", 0, 0, 800, 800);

    resultado = ResultadoPartida::VICTORIA_MANANA;
    puntuacion_final = 0;
    nombre_ganador = "Jugador";
    tiempoInicio_ = 0;
}

void PantallaFinal::setResultado(ResultadoPartida r, int puntuacion,
    const std::string& nombre) {
    resultado = r;
    puntuacion_final = puntuacion;
    nombre_ganador = nombre;
    tiempoInicio_ = glutGet(GLUT_ELAPSED_TIME);

    // Cancion de victoria
    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/victoria.mp3", false);
}

void PantallaFinal::dibujarTextoCentrado(const std::string& texto, void* font,
    float y, float r, float g, float b, float offsetX) {
    int ancho = 0;
    for (char c : texto) ancho += glutBitmapWidth(font, c);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);
    glRasterPos2f(-ancho / 2.0f + offsetX, y);  // ← offsetX aquí
    for (char c : texto)
        glutBitmapCharacter(font, c);
    glPopAttrib();
}

void PantallaFinal::dibuja() {
    int ahora = glutGet(GLUT_ELAPSED_TIME);
    bool enCreditos = (tiempoInicio_ > 0)
        && (ahora - tiempoInicio_ >= tiempo_creditos);

    if (enCreditos) {
        creditos_->draw();
        return;
    }

    fondo->draw();


    // Titulo - dentro del rectangulo blanco, parte superior
    if (resultado == ResultadoPartida::VICTORIA_MANANA) {
        dibujarTextoCentrado("VICTORIA - TURNO DE MANANA", GLUT_BITMAP_TIMES_ROMAN_24,
            230, 0.1f, 0.1f, 0.1f);  // negro
    }
    else {
        dibujarTextoCentrado("VICTORIA - TURNO DE TARDE", GLUT_BITMAP_TIMES_ROMAN_24,
            230, 0.1f, 0.1f, 0.1f);  // negro
    }

    // Nombre y puntuacion - centrados en el rectangulo
    dibujarTextoCentrado("Ganador:  " + nombre_ganador,
        GLUT_BITMAP_HELVETICA_18, 175, 0.1f, 0.1f, 0.1f);
    dibujarTextoCentrado("Puntuacion:  " + std::to_string(puntuacion_final),
        GLUT_BITMAP_HELVETICA_18, 140, 0.1f, 0.1f, 0.1f);

}

bool PantallaFinal::volverMenu() const {
    if (tiempoInicio_ == 0) return false;
    int ahora = glutGet(GLUT_ELAPSED_TIME);
    return (ahora - tiempoInicio_) >= (tiempo_creditos + 10000);
}