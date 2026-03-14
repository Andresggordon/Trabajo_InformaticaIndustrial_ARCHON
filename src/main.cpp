#include <Windows.h>
#include <GL/freeglut.h>
#include "Menu.h"

Menu* menu = nullptr; //puntero al menú vacio
Modos_juego estado = Modos_juego::MENU; //Estado actual del juego empieza en MENU

void display() {
    glClear(GL_COLOR_BUFFER_BIT); //Borra la pantalla
    if (estado == Modos_juego::MENU) {
        menu->dibuja(); //dibuja
    }
    glutSwapBuffers(); //muestra dibujo
}

void mouseMove(int x, int y) {
    if (estado == Modos_juego::MENU) {
        menu->update(x, y); //le dice al menú dónde está el ratón
    }
    glutPostRedisplay();
}

void mouseClick(int button, int estadoBtn, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && estadoBtn == GLUT_DOWN) { //click izquierdo ok
        if (estado == Modos_juego::MENU) {
            estado = menu->click(x, y); // clickeas y cambia el estado
        }
    }
    glutPostRedisplay();
}

void reposo() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    SetProcessDPIAware(); //para que no se vea borroso
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

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutIdleFunc(reposo);

    glutMainLoop();
    return 0;
}