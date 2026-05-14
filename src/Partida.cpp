
#include "Partida.h"
#include "MotorGrafico.h"
#include <GL/freeglut.h>
#include "tipo_personaje.h"
#include "Modos_juego.h"
#include "ArenaCombate.h"
#include "Geometria.h" // Necesario para calcular las casillas iluminadas

extern ArenaCombate* arena;

Partida::Partida() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 800, 800);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
    mostrar_popup = false;
    boton_activo = 0;
}

void Partida::dibuja() {
    fondo->draw();
}

void Partida::dibujaextra() {
    abandonar_partida->draw();
    if (mostrar_popup)
        popup_salir->draw();

    if (personaje_seleccionado != nullptr) {
        std::string ruta = personaje_seleccionado->getNombreCarta();

        if (ruta != nombre_carta_cargada) {
            delete carta_actual;
            carta_actual = new ETSIDI::Sprite(ruta.c_str(), 0, 0, 800, 800);
            nombre_carta_cargada = ruta;
        }

        carta_actual->draw();
    }
    else {
        nombre_carta_cargada = "";
    }
}

void Partida::update(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    if (!mostrar_popup) {
        if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274)
            boton_activo = 1;
        else
            boton_activo = 0;
    }
    else {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5)
            boton_activo = 2;
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            boton_activo = 3;
        else
            boton_activo = 0;
    }
}

Modos_juego Partida::click(int x, int y) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    ETSIDI::play("assets/sonidos/click.mp3");
    float cx = ((x - offsetX) / (float)tam) * 800 - 400;
    float cy = 400 - ((y - offsetY) / (float)tam) * 800;

    float tam_casilla = MotorGrafico::TAM;
    float inicioX = MotorGrafico::INICIO_X;
    float inicioY = MotorGrafico::INICIO_Y;
    int col = (int)((cx - inicioX) / tam_casilla);
    int fil = (int)((cy - inicioY) / tam_casilla);

    float ox = ((float)x / 500.0f - 1.0f) * 400.0f;
    float oy = (1.0f - (float)y / 500.0f) * 400.0f;

    // 1. POPUP tiene maxima prioridad
    if (mostrar_popup) {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
            return Modos_juego::MENU;
        }
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4)
            mostrar_popup = false;
        return Modos_juego::Partida;
    }

    // 2. Boton exit (abrir popup)
    if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274) {
        mostrar_popup = true;
        return Modos_juego::Partida;
    }

    // 3. Botones de habilidades del lider
    if (es_lider_seleccionado && personaje_seleccionado != nullptr) {
        Menu_habilidades* menu = personaje_seleccionado->getMenu();
        if (menu != nullptr) {
            if (ox >= -390 && ox <= -150 && oy >= -390 && oy <= -340) {
                int vida = personaje_seleccionado->getVidaActual();
                int vidaMax = personaje_seleccionado->getVidaMax();
                bool inmov = personaje_seleccionado->getInmovilizado();
                int px = personaje_seleccionado->getPosX();
                int py = personaje_seleccionado->getPosY();
                menu->Usar_habilidad(habilidades::REVIVIR, vida, vidaMax, px, py, inmov);
                personaje_seleccionado->setVida(vida);
                modo_revivir = true;
                return Modos_juego::Partida;
            }
            if (ox >= -80 && ox <= 80 && oy >= -390 && oy <= -340) {
                int vida = personaje_seleccionado->getVidaActual();
                int vidaMax = personaje_seleccionado->getVidaMax();
                bool inmov = personaje_seleccionado->getInmovilizado();
                int px = personaje_seleccionado->getPosX();
                int py = personaje_seleccionado->getPosY();
                menu->Usar_habilidad(habilidades::INMOVILIZA, vida, vidaMax, px, py, inmov);
                personaje_seleccionado->setInmovilizado(inmov);
                modo_inmovilizar = true;
                return Modos_juego::Partida;
            }
            if (ox >= 150 && ox <= 390 && oy >= -390 && oy <= -340) {
                modo_teleport = true;
                return Modos_juego::Partida;
            }
        }
    }

    // 4. Tablero
    if (col >= 0 && col < 9 && fil >= 0 && fil < 9)
        return procesarClickTablero(fil, col);

    return Modos_juego::Partida;
}

Modos_juego Partida::procesarClickTablero(int fil, int col) {
    Casilla& casilla = tab_.getCasilla(fil, col);

    if (modo_teleport) {
        if (personaje_seleccionado == nullptr) {
            modo_teleport = false;
            return Modos_juego::Partida;
        }
        if (casilla.getPersonaje() == nullptr) {
            personaje_seleccionado->getCasillaActual()->setPersonaje(nullptr);
            casilla.setPersonaje(personaje_seleccionado);
            personaje_seleccionado->setCasillaActual(&casilla);
        }
        modo_teleport = false;
        personaje_seleccionado = nullptr;
        casillas_iluminadas.clear();
        turno_actual = 1 - turno_actual;
        return Modos_juego::Partida;
    }

    if (modo_inmovilizar) {
        Personaje* objetivo = casilla.getPersonaje();
        if (objetivo != nullptr && objetivo->getTurno() != personaje_seleccionado->getTurno()) {
            objetivo->setInmovilizado(true);
        }
        modo_inmovilizar = false;
        personaje_seleccionado = nullptr;
        casillas_iluminadas.clear();
        es_lider_seleccionado = false;
        turno_actual = 1 - turno_actual;
        return Modos_juego::Partida;
    }

    if (modo_revivir) {
        Personaje* objetivo = casilla.getPersonaje();
        if (objetivo != nullptr
            && objetivo->getTurno() == personaje_seleccionado->getTurno()
            && !objetivo->estaVivo()) {
            objetivo->setVida(objetivo->getVidaMax());
        }
        modo_revivir = false;
        personaje_seleccionado = nullptr;
        casillas_iluminadas.clear();
        es_lider_seleccionado = false;
        turno_actual = 1 - turno_actual;
        return Modos_juego::Partida;
    }

    if (personaje_seleccionado == nullptr) {
        Personaje* p = casilla.getPersonaje();
        if (p != nullptr && p->estaVivo()) {
            bool es_manana = (p->getTurno() == Turno::TURNO_DE_MANANA);
            bool turno_ok = (turno_actual == 0 && es_manana) ||
                (turno_actual == 1 && !es_manana);
            if (turno_ok) {
                personaje_seleccionado = p;
                es_lider_seleccionado = (p->getMenu() != nullptr);
                casillas_iluminadas = Geometria::getCasillasAccesibles(*personaje_seleccionado, tab_);
            }
        }
    }
    else {
        ResultadoMover res = tab_.moverPersonaje(personaje_seleccionado, casilla);

        if (res == ResultadoMover::OK) {
            turno_actual = 1 - turno_actual;
            for (auto p : personajes)
                p->decrementarInmovilizacion();
        }
        else if (res == ResultadoMover::CHOQUE) {
            arena->iniciarCombate(
                tab_.getPendienteLocal(),
                tab_.getPendienteInvasor(),
                modo_actual
            );
            tab_.limpiarPendiente();
            personaje_seleccionado = nullptr;
            casillas_iluminadas.clear();
            es_lider_seleccionado = false;
            return Modos_juego::Arena_Combate;
        }

        personaje_seleccionado = nullptr;
        casillas_iluminadas.clear();
        es_lider_seleccionado = false;
        return Modos_juego::Partida;
    }
    return Modos_juego::Partida;
}

void Partida::dibujaSeleccion() {
    MotorGrafico::get_instance().dibujaSeleccion(personaje_seleccionado, casillas_iluminadas);
}

void Partida::dibujaHabilidades() {
    if (!es_lider_seleccionado) return;
    if (modo_teleport || modo_inmovilizar || modo_revivir) return;

    MotorGrafico::get_instance().dibujaHabilidades();
}

void Partida::teclado(unsigned char key) {
    if (key == 32)
        tab_.avanzarCiclo();
    if (key == 27)
        mostrar_popup = false;
}

void Partida::reset() {
    for (int fila = 0; fila < Tablero::FILAS; fila++)
        for (int col = 0; col < Tablero::COLUMNAS; col++)
            tab_.getCasilla(fila, col).setPersonaje(nullptr);

    ETSIDI::stopMusica();
    ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false;
    boton_activo = 0;

    modo_actual = modo_juego;
    turno_actual = turno_inicio;

    for (auto p : personajes) delete p;
    for (auto d : dibujos)    delete d;
    personajes.clear();
    dibujos.clear();

    // Equipo manana
    personajes.push_back(new Profesor_SS(tab_.getCasilla(4, 0)));
    personajes.push_back(new PLC(tab_.getCasilla(1, 0)));
    personajes.push_back(new PLC(tab_.getCasilla(7, 0)));
    personajes.push_back(new Moto_electrica(tab_.getCasilla(2, 0)));
    personajes.push_back(new Moto_electrica(tab_.getCasilla(6, 0)));
    personajes.push_back(new Fuente_de_tension_de_bateria(tab_.getCasilla(3, 0)));
    personajes.push_back(new Copilot(tab_.getCasilla(5, 0)));
    personajes.push_back(new Microprocesador_M(tab_.getCasilla(0, 0)));
    personajes.push_back(new Microprocesador_M(tab_.getCasilla(8, 0)));
    personajes.push_back(new Multimetro(tab_.getCasilla(0, 1)));
    personajes.push_back(new Multimetro(tab_.getCasilla(8, 1)));
    for (int i = 1; i <= 7; i++)
        personajes.push_back(new Circuito_integrado_M(tab_.getCasilla(i, 1)));

    // Equipo tarde
    personajes.push_back(new Profesor_MH(tab_.getCasilla(4, 8)));
    personajes.push_back(new Microprocesador_T(tab_.getCasilla(0, 8)));
    personajes.push_back(new Microprocesador_T(tab_.getCasilla(8, 8)));
    personajes.push_back(new Osciloscopio(tab_.getCasilla(0, 7)));
    personajes.push_back(new Osciloscopio(tab_.getCasilla(8, 7)));
    personajes.push_back(new Brazo_robot(tab_.getCasilla(1, 8)));
    personajes.push_back(new Brazo_robot(tab_.getCasilla(7, 8)));
    personajes.push_back(new Fuente_de_corriente(tab_.getCasilla(3, 8)));
    personajes.push_back(new Moto_petrol(tab_.getCasilla(2, 8)));
    personajes.push_back(new Moto_petrol(tab_.getCasilla(6, 8)));
    personajes.push_back(new Gemini(tab_.getCasilla(5, 8)));
    for (int i = 1; i <= 7; i++)
        personajes.push_back(new Circuito_integrado_T(tab_.getCasilla(i, 7)));

    for (auto p : personajes)
        dibujos.push_back(new DibujoPersonaje(p));
}