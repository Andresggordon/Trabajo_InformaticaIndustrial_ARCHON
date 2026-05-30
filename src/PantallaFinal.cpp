/**
 * @file PantallaFinal.cpp
 * @brief Implementación de la secuencia de fin de partida, entrada de datos del usuario y créditos.
 */

#include "PantallaFinal.h"
#include <GL/freeglut.h>
#include <string>

PantallaFinal::PantallaFinal() {
    fondo_nombre_ = new ETSIDI::Sprite("assets/menu_imagenes/pantalla_final.png", 0, 0, 800, 800);
    fondo_victoria_ = new ETSIDI::Sprite("assets/menu_imagenes/pantalla_final.png", 0, 0, 800, 800);
    creditos_ = new ETSIDI::Sprite("assets/menu_imagenes/creditos.png", 0, 0, 800, 800);

    fase_ = Fase::PEDIR_NOMBRE;
    resultado_ = ResultadoPartida::VICTORIA_MANANA;
    puntuacion_ = 0;
    nombre_ = "";
    tiempoFaseVictoria_ = 0;
}

void PantallaFinal::setResultado(ResultadoPartida r, int puntuacion, bool ganadorEsHumano) {
    resultado_ = r;
    puntuacion_ = puntuacion;
    nombre_ = "";
    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/victoria.mp3", false);

    if (ganadorEsHumano) {
        fase_ = Fase::PEDIR_NOMBRE;
    }
    else {
        nombre_ = "IA";  // o el nombre que quieras que aparezca en el ranking
        fase_ = Fase::MOSTRAR_VICTORIA;
        tiempoFaseVictoria_ = glutGet(GLUT_ELAPSED_TIME);
    }
}

void PantallaFinal::dibujarTextoCentrado(const std::string& texto, void* font,
    float y, float r, float g, float b, float offsetX) {
    int ancho = 0;
    for (char c : texto) ancho += glutBitmapWidth(font, c);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);
    glRasterPos2f(-ancho / 2.0f + offsetX, y);
    for (char c : texto)
        glutBitmapCharacter(font, c);
    glPopAttrib();
}

void PantallaFinal::teclado(unsigned char key) {
    if (fase_ != Fase::PEDIR_NOMBRE) return;
    if (key == 8 && !nombre_.empty())
        nombre_.pop_back();
    else if (key == 13 && !nombre_.empty()) {   // Enter
        fase_ = Fase::MOSTRAR_VICTORIA;
        tiempoFaseVictoria_ = glutGet(GLUT_ELAPSED_TIME);
    }
    else if (nombre_.size() < 20 && (isalnum(key) || key == ' '))
        nombre_ += (char)key;
}



void PantallaFinal::dibuja() {
    if (fase_ == Fase::PEDIR_NOMBRE) {
        fondo_nombre_->draw();
        if (resultado_ == ResultadoPartida::VICTORIA_MANANA)
            dibujarTextoCentrado("VICTORIA - TURNO DE MANANA", GLUT_BITMAP_TIMES_ROMAN_24,
                230, 1.0f, 0.85f, 0.0f);
        else
            dibujarTextoCentrado("VICTORIA - TURNO DE TARDE", GLUT_BITMAP_TIMES_ROMAN_24,
                230, 0.3f, 0.7f, 1.0f);
        dibujarTextoCentrado("Introduce el nombre del ganador:",
            GLUT_BITMAP_HELVETICA_18, 175, 1.0f, 1.0f, 1.0f);
        dibujarTextoCentrado(nombre_ + "_",
            GLUT_BITMAP_HELVETICA_18, 140, 1.0f, 0.85f, 0.0f);
        return;
    }

    int ahora = glutGet(GLUT_ELAPSED_TIME);
    bool enCreditos = (ahora - tiempoFaseVictoria_) >= TIEMPO_CREDITOS;

    if (fase_ == Fase::MOSTRAR_VICTORIA && enCreditos)
        fase_ = Fase::CREDITOS;

    if (fase_ == Fase::CREDITOS) {
        creditos_->draw();
        return;
    }

    // MOSTRAR_VICTORIA
    fondo_victoria_->draw();
    if (resultado_ == ResultadoPartida::VICTORIA_MANANA)
        dibujarTextoCentrado("VICTORIA - TURNO DE MANANA", GLUT_BITMAP_TIMES_ROMAN_24,
            230, 0.1f, 0.1f, 0.1f);
    else
        dibujarTextoCentrado("VICTORIA - TURNO DE TARDE", GLUT_BITMAP_TIMES_ROMAN_24,
            230, 0.1f, 0.1f, 0.1f);
    dibujarTextoCentrado("Ganador:  " + nombre_,
        GLUT_BITMAP_HELVETICA_18, 175, 0.1f, 0.1f, 0.1f);
    dibujarTextoCentrado("Puntuacion:  " + std::to_string(puntuacion_),
        GLUT_BITMAP_HELVETICA_18, 140, 0.1f, 0.1f, 0.1f);
}

bool PantallaFinal::volverMenu() const {
    if (fase_ != Fase::CREDITOS) return false;
    int ahora = glutGet(GLUT_ELAPSED_TIME);
    return (ahora - tiempoFaseVictoria_) >= (TIEMPO_CREDITOS + TIEMPO_VUELTA_MENU);
}