#include "Como_jugar.h"
#include <GL/freeglut.h>
#include <string>

// Función auxiliar para dibujar texto con glutBitmapString
static void drawText(float x, float y, const std::string& texto, void* fuente = GLUT_BITMAP_9_BY_15) {
    glRasterPos2f(x, y);
    for (char c : texto)
        glutBitmapCharacter(fuente, c);
}

ComoJugar::ComoJugar() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo.png", 0, 0, 800, 800);
    boton_volver = new ETSIDI::Sprite("assets/menu_imagenes/boton_Ranking.png", 0, 0, 800, 800); // reutiliza imagen o crea una
    boton_activo = 0;
    pagina = 0;
}

void ComoJugar::dibuja() {
    fondo->draw();

    // Color del texto: blanco/amarillo segun tema
    glColor3f(1.0f, 0.95f, 0.7f);

    // --- TITULO ---
    glRasterPos2f(-140, 340);
    std::string titulo = "COMO JUGAR - REGLAS DEL JUEGO";
    for (char c : titulo)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    glColor3f(1.0f, 1.0f, 1.0f);

    // --- PAGINA 0: Objetivo y tablero ---
    if (pagina == 0) {
        struct Linea { float y; std::string txt; };
        Linea lineas[] = {
            {300, "OBJETIVO DEL JUEGO:"},
            {278, "  Controla el tablero 9x9 ocupando 5 casillas clave (casillas de poder)."},
            {258, "  O bien elimina todas las piezas del rival."},
            {228, "TABLERO:"},
            {208, "  El tablero tiene 9x9 casillas. Las casillas oscuras son 'casillas de poder'."},
            {188, "  Quien controle 5 casillas de poder gana la partida."},
            {158, "PIEZAS:"},
            {138, "  Cada bando tiene 16 piezas: 8 guerreros (terrestres) + 8 magos (voladores)."},
            {118, "  Los voladores pueden atravesar piezas al moverse."},
            { 98, "  Los terrestres no pueden pasar por encima de otras piezas."},
            { 68, "MOVIMIENTO:"},
            { 48, "  Selecciona una pieza y haz clic en una casilla valida para moverla."},
            { 28, "  Solo puedes mover piezas propias en tu turno."},
        };
        for (auto& l : lineas)
            drawText(-380, l.y, l.txt);

        // Boton siguiente pagina
        glColor3f(0.8f, 0.6f, 0.2f);
        drawText(200, -360, "> Siguiente pagina");
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    // --- PAGINA 1: Combate y reglas especiales ---
    if (pagina == 1) {
        struct Linea { float y; std::string txt; };
        Linea lineas[] = {
            {300, "COMBATE:"},
            {278, "  Si mueves una pieza a una casilla ocupada por el rival, se inicia un combate."},
            {258, "  El combate es un minijuego: cada jugador dispara proyectiles al rival."},
            {238, "  Gana quien reduzca la vida del rival a 0. El perdedor es eliminado del tablero."},
            {208, "HABILIDADES ESPECIALES:"},
            {188, "  Cada tipo de pieza tiene habilidades unicas (ver icono en pantalla de seleccion)."},
            {168, "  Las habilidades tienen un coste y un numero de usos limitado."},
            {138, "CASILLAS DE PODER:"},
            {118, "  Al final de cada turno completo, si un jugador ocupa 5 casillas de poder, gana."},
            { 98, "  Las casillas de poder estan marcadas con un simbolo especial en el tablero."},
            { 68, "MODOS DE JUEGO:"},
            { 48, "  1 Jugador: te enfrentas a la maquina."},
            { 28, "  2 Jugadores: dos humanos en el mismo ordenador."},
        };
        for (auto& l : lineas)
            drawText(-380, l.y, l.txt);

        glColor3f(0.8f, 0.6f, 0.2f);
        drawText(-380, -360, "< Pagina anterior");
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    // --- Boton volver al menu (siempre visible) ---
    glColor3f(0.9f, 0.3f, 0.3f);
    drawText(-30, -380, "[VOLVER AL MENU]");
    glColor3f(1.0f, 1.0f, 1.0f);
}

void ComoJugar::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (cx >= -80 && cx <= 120 && cy >= -390 && cy <= -370)
        boton_activo = 1; // volver
    else if (pagina == 0 && cx >= 150 && cx <= 380 && cy >= -375 && cy <= -350)
        boton_activo = 2; // siguiente
    else if (pagina == 1 && cx >= -380 && cx <= -100 && cy >= -375 && cy <= -350)
        boton_activo = 3; // anterior
    else
        boton_activo = 0;
}

Modos_juego ComoJugar::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    ETSIDI::play("assets/sonidos/click.mp3");

    // Volver al menu
    if (cx >= -80 && cx <= 120 && cy >= -390 && cy <= -370)
        return Modos_juego::MENU;

    // Siguiente pagina
    if (pagina == 0 && cx >= 150 && cx <= 380 && cy >= -375 && cy <= -350) {
        pagina = 1;
        return Modos_juego::Como_jugar;
    }

    // Pagina anterior
    if (pagina == 1 && cx >= -380 && cx <= -100 && cy >= -375 && cy <= -350) {
        pagina = 0;
        return Modos_juego::Como_jugar;
    }

    return Modos_juego::Como_jugar;
}