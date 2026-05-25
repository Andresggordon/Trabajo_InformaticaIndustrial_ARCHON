#include "PantallaFinal.h"
#include <GL/freeglut.h>
#include <string>

PantallaFinal::PantallaFinal() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo2.png", 0, 0, 800, 800);
    boton_menu = new ETSIDI::Sprite("assets/menu_imagenes/back.png", 0, 0, 800, 800);
    creditos_ = new ETSIDI::Sprite("assets/menu_imagenes/pantalla_final.png", 0, 0, 800, 800);

    resultado = ResultadoPartida::VICTORIA_MANANA;
    puntuacion_final = 0;
    nombre_ganador = "Jugador";
    boton_activo = 0;
    tiempoInicio_ = 0;
}

void PantallaFinal::setResultado(ResultadoPartida r, int puntuacion,
    const std::string& nombre) {
    resultado = r;
    puntuacion_final = puntuacion;
    nombre_ganador = nombre;
    tiempoInicio_ = glutGet(GLUT_ELAPSED_TIME);  
}


void PantallaFinal::dibujarTextoCentrado(const std::string& texto, void* font,
    float y, float r, float g, float b) {
    int ancho = 0;
    for (char c : texto) ancho += glutBitmapWidth(font, c);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);
    glRasterPos2f(-ancho / 2.0f, y);
    for (char c : texto)
        glutBitmapCharacter(font, c);
    glPopAttrib();
}

void PantallaFinal::dibuja() {
    
    int ahora = glutGet(GLUT_ELAPSED_TIME);
    bool enCreditos = (tiempoInicio_ > 0)
        && (ahora - tiempoInicio_ >= TIEMPO_PARA_CREDITOS);
    if (enCreditos) {
        creditos_->draw();
        boton_menu->draw();
        return;
    }

    fondo->draw();
    boton_menu->draw();

    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(1.0f, 0.85f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-150, 75); glVertex2f(150, 75);
    glEnd();
    glPopAttrib();

    
    if (resultado == ResultadoPartida::VICTORIA_MANANA) {
        dibujarTextoCentrado("TURNO DE MANANA GANA!", GLUT_BITMAP_HELVETICA_18,
            50, 1.0f, 0.85f, 0.0f);  // amarillo
    }
    else {
        dibujarTextoCentrado("TURNO DE TARDE GANA!", GLUT_BITMAP_HELVETICA_18,
            50, 0.3f, 0.6f, 1.0f);   // azul claro
    }

    
    dibujarTextoCentrado("Ganador:  " + nombre_ganador,
        GLUT_BITMAP_HELVETICA_12, 15, 1.0f, 1.0f, 1.0f);
    dibujarTextoCentrado("Puntuacion:  " + std::to_string(puntuacion_final),
        GLUT_BITMAP_HELVETICA_12, -10, 1.0f, 1.0f, 0.2f);

   
    dibujarTextoCentrado("La puntuacion depende de piezas vivas y velocidad",
        GLUT_BITMAP_HELVETICA_10, -45, 0.6f, 0.6f, 0.6f);
    dibujarTextoCentrado("Pulsa BACK para volver al menu",
        GLUT_BITMAP_HELVETICA_10, -80, 0.5f, 0.5f, 0.5f);

    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-150, -105); glVertex2f(150, -105);
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
    boton_activo = (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328) ? 1 : 0;
}

Modos_juego PantallaFinal::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= 297 && cx <= 386 && cy >= -352 && cy <= -328) {
        ETSIDI::play("assets/sonidos/click.mp3");
        ETSIDI::stopMusica();
        ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
        return Modos_juego::MENU;
    }
    return Modos_juego::Pantalla_Final;
}