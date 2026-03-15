#include <Windows.h>
#include <GL/freeglut.h>
#include "Menu.h"
#include "Eleccion_1jugador.h"
#include "Eleccion_2jugadores.h"
#include "Eleccion2_1jugador.h" 

Menu* menu = nullptr;
Eleccion_1jugador* eleccion_1jugador = nullptr;
Eleccion_2jugadores* eleccion_2jugadores = nullptr;
Eleccion2_1jugador* eleccion2_1jugador = nullptr; 

Modos_juego estado = Modos_juego::MENU;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (estado == Modos_juego::MENU)
        menu->dibuja();
    if (estado == Modos_juego::Eleccion_1jugador)
        eleccion_1jugador->dibuja();
    if (estado == Modos_juego::Eleccion_2jugadores)
        eleccion_2jugadores->dibuja();
    if (estado == Modos_juego::Eleccion2_1jugador) 
        eleccion2_1jugador->dibuja();
    glutSwapBuffers();
}

void mouseMove(int x, int y) {
    if (estado == Modos_juego::MENU)
        menu->update(x, y);
    if (estado == Modos_juego::Eleccion_1jugador)
        eleccion_1jugador->update(x, y);
    if (estado == Modos_juego::Eleccion_2jugadores)
        eleccion_2jugadores->update(x, y);
    if (estado == Modos_juego::Eleccion2_1jugador)
        eleccion2_1jugador->update(x, y);
    glutPostRedisplay();
}

void mouseClick(int button, int estadoBtn, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && estadoBtn == GLUT_DOWN) {
        if (estado == Modos_juego::MENU)
            estado = menu->click(x, y);
        else if (estado == Modos_juego::Eleccion_1jugador)
            estado = eleccion_1jugador->click(x, y);
        else if (estado == Modos_juego::Eleccion_2jugadores)
            estado = eleccion_2jugadores->click(x, y);
        else if (estado == Modos_juego::Eleccion2_1jugador)
            estado = eleccion2_1jugador->click(x, y);
    }
    glutPostRedisplay();
}

void reposo() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    SetProcessDPIAware();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("ARCHON");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    menu = new Menu();
    eleccion_1jugador = new Eleccion_1jugador();
    eleccion_2jugadores = new Eleccion_2jugadores();
    eleccion2_1jugador = new Eleccion2_1jugador(); 
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutIdleFunc(reposo);
    glutMainLoop();
    return 0;
}