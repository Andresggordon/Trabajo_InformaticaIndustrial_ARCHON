#include <Windows.h>
#include <GL/freeglut.h>
#include "Menu.h"
#include "Eleccion_1jugador.h"
#include "Eleccion_2jugadores.h"
#include "Eleccion2_1jugador.h"
#include "ranking.h"
#include "Pantalla_carga.h"
#include "Partida.h"
#include "MotorGrafico.h"
#include "ArenaCombate.h"
#include "PantallaFinal.h"


int equipo_j1 = 0;
int equipo_j2 = 0;
int modo_juego = 0;
int turno_inicio = 0;


Menu* menu = nullptr;
Eleccion_1jugador* eleccion_1jugador = nullptr;
Eleccion_2jugadores* eleccion_2jugadores = nullptr;
Eleccion2_1jugador* eleccion2_1jugador = nullptr;
Ranking* ranking = nullptr;
Pantalla_carga* pantalla_carga = nullptr;
ArenaCombate* arena = nullptr;
PantallaFinal* pantalla_final = nullptr;

Modos_juego estado = Modos_juego::Pantalla_carga;

void reshape(int w, int h) {
    int tam = min(w, h);
    int x = (w - tam) / 2;
    int y = (h - tam) / 2;
    glViewport(x, y, tam, tam);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Forzar pixel art nítido en todas las texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (estado == Modos_juego::Pantalla_carga)
        pantalla_carga->dibuja();
    else if (estado == Modos_juego::MENU)
        menu->dibuja();
    else if (estado == Modos_juego::Eleccion_1jugador)
        eleccion_1jugador->dibuja();
    else if (estado == Modos_juego::Eleccion_2jugadores)
        eleccion_2jugadores->dibuja();
    else if (estado == Modos_juego::Eleccion2_1jugador)
        eleccion2_1jugador->dibuja();
    else if (estado == Modos_juego::Pantalla_Ranking)
        ranking->dibuja();
    else if (estado == Modos_juego::Partida) {
        Partida::get_instance().dibuja();           // 1. fondo
        MotorGrafico::get_instance().dibujar();     // 2. tablero
        Partida::get_instance().dibujaSeleccion(); // 3. Selección de casilla
        Partida::get_instance().dibujaHabilidades(); // 4. Dibujar habilidades      
        Partida::get_instance().dibujaInmovilizados(); //6. Personaje inmovilizado
        Partida::get_instance().dibujaBarrasVida(); // 7. Barras de vida 
        Partida::get_instance().dibujaEscudos(); // 8. Escudo casilla
        Partida::get_instance().dibujaInmunidad();// 9. Inmunidad casilla
        Partida::get_instance().dibujaAviso(); // 10. Avisos por pantalla
        Partida::get_instance().dibujaextra(); // 5. exit y popup encima de todo
    }
    else if (estado == Modos_juego::Arena_Combate)
    {
        MotorGrafico::get_instance().dibujarArena();
        arena->dibujaPopup();
        arena->dibujaCartel();
    }
    else if (estado == Modos_juego::Pantalla_Final)
        pantalla_final->dibuja();

    glutSwapBuffers();
}

void mouseMove(int x, int y) {
    if (estado == Modos_juego::MENU)
        menu->update(x, y);
    else if (estado == Modos_juego::Eleccion_1jugador)
        eleccion_1jugador->update(x, y);
    else if (estado == Modos_juego::Eleccion_2jugadores)
        eleccion_2jugadores->update(x, y);
    else if (estado == Modos_juego::Eleccion2_1jugador)
        eleccion2_1jugador->update(x, y);
    else if (estado == Modos_juego::Pantalla_Ranking)
        ranking->update(x, y);
    else if (estado == Modos_juego::Partida)
        Partida::get_instance().update(x, y);
    else if (estado == Modos_juego::Arena_Combate)
        arena->update(x, y);
    else if (estado == Modos_juego::Pantalla_Final)
        pantalla_final->update(x, y);
    glutPostRedisplay();
}

void mouseClick(int button, int estadoBtn, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && estadoBtn == GLUT_DOWN) {
        Modos_juego estado_anterior = estado;

        if (estado == Modos_juego::MENU)
            estado = menu->click(x, y);
        else if (estado == Modos_juego::Eleccion_1jugador)
            estado = eleccion_1jugador->click(x, y);
        else if (estado == Modos_juego::Eleccion_2jugadores)
            estado = eleccion_2jugadores->click(x, y);
        else if (estado == Modos_juego::Eleccion2_1jugador)
            estado = eleccion2_1jugador->click(x, y);
        else if (estado == Modos_juego::Pantalla_Ranking)
            estado = ranking->click(x, y);
        else if (estado == Modos_juego::Partida)
            estado = Partida::get_instance().click(x, y);
        else if (estado == Modos_juego::Arena_Combate)
            estado = arena->click(x, y);
        else if (estado == Modos_juego::Pantalla_Final)
            estado = pantalla_final->click(x, y);

        if (estado == Modos_juego::Partida && estado_anterior != Modos_juego::Partida)
            Partida::get_instance().reset();

        glutPostRedisplay();
    }
}

void teclado(unsigned char key, int x, int y) {
    if (estado == Modos_juego::Pantalla_carga) {
        pantalla_carga->teclado(key);
        if (pantalla_carga->carga_completa)
            estado = Modos_juego::MENU;
    }
    else if (estado == Modos_juego::Partida) {
        Partida::get_instance().teclado(key);
        Partida::get_instance().tecladoHabilidades(key);
    }
    else if (estado == Modos_juego::Arena_Combate) {  
        arena->teclado(key);
    }
    glutPostRedisplay();
}

void tecladoEspecial(int key, int x, int y) {
    if (estado == Modos_juego::Arena_Combate)
        arena->tecladoEspecial(key);
    glutPostRedisplay();
}

void reposo() {

    static int tiempoAnterior = glutGet(GLUT_ELAPSED_TIME);
    int tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (tiempoActual - tiempoAnterior) / 1000.0f; 
    tiempoAnterior = tiempoActual;

    if (estado == Modos_juego::Pantalla_carga) {
        pantalla_carga->update();
        if (pantalla_carga->carga_completa)
            estado = Modos_juego::MENU;
    }
    else if (estado == Modos_juego::Arena_Combate)
    {
        arena->actualizar();

        if (arena->combateTerminado() && !arena->mostrandoCartel()) {
            Partida::get_instance().tablero().resolverCombate(arena->getResultado());
            arena->finalizarCombate();
            // Tras el combate puede haber acabado la partida (mago/piezas).
            estado = Partida::get_instance().comprobarFinPartida();
        }
    }
    else if (estado == Modos_juego::Partida) {
        if (MotorGrafico::tiempoAviso > 0.0f) MotorGrafico::tiempoAviso -= deltaTime;  // ~60fps, resta ~1 seg cada 60 llamadas
        // En modo 1 jugador, deja que la maquina mueva si es su turno.
        estado = Partida::get_instance().turnoMaquina();
    }
    glutPostRedisplay();
}

void tecladoUp(unsigned char key, int x, int y) {
    if (estado == Modos_juego::Arena_Combate)
        arena->teclaLevantada(key);
}

void tecladoEspecialUp(int key, int x, int y) {
    if (estado == Modos_juego::Arena_Combate)
        arena->teclaEspecialLevantada(key);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    SetProcessDPIAware();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("ARCHON");
    //glutFullScreen(); // automaticamente pantalla completa
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    menu = new Menu();
    eleccion_1jugador = new Eleccion_1jugador();
    eleccion_2jugadores = new Eleccion_2jugadores();
    eleccion2_1jugador = new Eleccion2_1jugador();
    ranking = new Ranking();
    pantalla_carga = new Pantalla_carga();
    arena = new ArenaCombate();
    pantalla_final = new PantallaFinal();
    // Partida y MotorGrafico se inicializan solos la primera vez que se llaman
    Partida::get_instance();
    MotorGrafico::get_instance();
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(teclado);
    glutIdleFunc(reposo);
    glutReshapeFunc(reshape);
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardUpFunc(tecladoUp);
    glutSpecialUpFunc(tecladoEspecialUp);
    glutMainLoop();
    return 0;
}