#include <GL/freeglut.h>
#include "Menu.h"

Menu* menu = nullptr;
Modos_juego estado = Modos_juego::MENU;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estado == Modos_juego::MENU) {
        menu->dibuja();
    }

    glutSwapBuffers();
}

void mouseMove(int x, int y) {
    if (estado == Modos_juego::MENU) {
        menu->update(x, y);
    }
    glutPostRedisplay();
}

void mouseClick(int button, int estadoBtn, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && estadoBtn == GLUT_DOWN) {
        if (estado == Modos_juego::MENU) {
            estado = menu->click(x, y);
        }
    }
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400); // Ventana de 400x400
    glutCreateWindow("ARCHON");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // El (0,0) arriba a la izquierda. X crece a la derecha, Y crece hacia abajo.
    gluOrtho2D(0, 400, 400, 0);
    glMatrixMode(GL_MODELVIEW);

    menu = new Menu();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutIdleFunc(idle);

    glutMainLoop();

    delete menu;
    return 0;
}