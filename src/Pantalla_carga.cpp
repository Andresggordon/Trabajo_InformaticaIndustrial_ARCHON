#include "Pantalla_carga.h"
#include <GL/freeglut.h>

Pantalla_carga::Pantalla_carga() {
    fondo_carga = new ETSIDI::Sprite("assets/fondo_carga.png", 0, 0, 600, 600);
    logo1 = new ETSIDI::Sprite("assets/logo.png", -350, 50, 150, 150);
    logo2 = new ETSIDI::Sprite("assets/logo.png", 350, 50, 150, 150);
    esperando_enter = true;
    timer = 0.0f;
    carga_completa = false;
}

void Pantalla_carga::dibuja() {
    fondo_carga->draw();
    if (!esperando_enter) {
        logo1->draw();
        logo2->draw();
    }
}

void Pantalla_carga::update() {
    if (!esperando_enter && timer < 1.0f) {
        timer += 0.003f;
        logo1 = new ETSIDI::Sprite("assets/logo.png", -350 + 350 * timer, 50, 150, 150);
        logo2 = new ETSIDI::Sprite("assets/logo.png", 350 - 350 * timer, 50, 150, 150);
    }
    if (timer >= 1.0f)
        carga_completa = true;
}

Modos_juego Pantalla_carga::click(int x, int y) {
    return Modos_juego::Pantalla_carga;
}

void Pantalla_carga::teclado(unsigned char key) {
    if (key == 13 && esperando_enter) {
        esperando_enter = false;
        timer = 0.0f;
    }
}