#include "Partida.h"
#include "MotorGrafico.h"
#include <GL/freeglut.h>
#include "tipo_personaje.h"
#include "Modos_juego.h"
#include "ArenaCombate.h"
#include "Finpartida.h"
#include "PantallaFinal.h"
#include "ranking.h"
#include "Geometria.h"
#include <iostream>
#include <string>

extern ArenaCombate* arena;
extern PantallaFinal* pantalla_final;
extern Ranking* ranking;

Partida::Partida() {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 800, 800);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
    mostrar_popup = false;
    boton_activo = 0;
}

void Partida::dibuja() { fondo->draw(); }

void Partida::dibujaextra() {
    abandonar_partida->draw();
    if (personaje_seleccionado != nullptr) {
        std::string ruta = personaje_seleccionado->getNombreCarta();
        if (ruta != nombre_carta_cargada) {
            delete carta_actual;
            carta_actual = new ETSIDI::Sprite(ruta.c_str(), 0, 0, 800, 800);
            nombre_carta_cargada = ruta;
        }
        carta_actual->draw();
        MotorGrafico::get_instance().dibujarVidaPanel(personaje_seleccionado);
    }
    else { nombre_carta_cargada = ""; }

    if (mostrar_popup) popup_salir->draw();
}

void Partida::update(int x, int y) {
    float cx, cy;
    screenToGame(x, y, cx, cy);

    if (!mostrar_popup) {
        if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274) boton_activo = 1;
        else boton_activo = 0;
    }
    else {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) boton_activo = 2;
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4) boton_activo = 3;
        else boton_activo = 0;
    }
}

Modos_juego Partida::click(int x, int y) {
    float cx, cy;
    screenToGame(x, y, cx, cy);

    ETSIDI::play("assets/sonidos/click.mp3");

    int col = (int)((cx - MotorGrafico::INICIO_X) / MotorGrafico::TAM);
    int fil = (int)((cy - MotorGrafico::INICIO_Y) / MotorGrafico::TAM);

    if (mostrar_popup) {
        if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
            return Modos_juego::MENU;
        }
        else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4) mostrar_popup = false;
        return Modos_juego::Partida;
    }

    if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274) {
        mostrar_popup = true;
        return Modos_juego::Partida;
    }

    if (col >= 0 && col < 9 && fil >= 0 && fil < 9) return procesarClickTablero(fil, col);
    return Modos_juego::Partida;
}

Modos_juego Partida::procesarClickTablero(int fil, int col) {
    Casilla& casilla = tab_.getCasilla(fil, col);
    Menu_habilidades* menu = personaje_seleccionado ? personaje_seleccionado->getMenu() : nullptr;

    if (modo_teleport) {
        if (menu) menu->activarHabilidad(0, personaje_seleccionado, nullptr, &casilla);
        if (menu && !menu->puedeUsar(0)) turno_actual = 1 - turno_actual;
        modo_teleport = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return comprobarFinPartida();
    }

    if (modo_inmovilizar) {
        Personaje* obj = casilla.getPersonaje();
        if (menu && obj) {
            bool ejecutado = menu->activarHabilidad(2, personaje_seleccionado, obj, nullptr);
            if (ejecutado) turno_actual = 1 - turno_actual;
        }
        modo_inmovilizar = false; personaje_seleccionado = nullptr;
        es_lider_seleccionado = false; casillas_iluminadas.clear();
        return comprobarFinPartida();
    }

    if (modo_revivir) {
        if (menu) {
            auto& listaMuertos = (personaje_seleccionado->getTurno() == Turno::TURNO_DE_MANANA)
                ? muertosAliados_manana : muertosAliados_tarde;

            if (!listaMuertos.empty()) {
                Personaje* ultimo = listaMuertos.back();
                listaMuertos.pop_back();
                ultimo->setVida(ultimo->getVidaMax() / 2);
                casilla.setPersonaje(ultimo);
                ultimo->setCasillaActual(&casilla);
                turno_actual = 1 - turno_actual;
                menu->activarHabilidad(1, personaje_seleccionado, nullptr, nullptr);
            }
            else {
                MotorGrafico::mensajeAviso = "No hay aliados muertos!";
                MotorGrafico::tiempoAviso = 2.0f;
            }
        }
        modo_revivir = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Partida;
    }

    if (modo_curar) {
        Personaje* obj = casilla.getPersonaje();
        if (menu && obj) {
            bool ejecutado = menu->activarHabilidad(3, personaje_seleccionado, obj, nullptr);
            if (ejecutado) {
                turno_actual = 1 - turno_actual;
                MotorGrafico::mensajeAviso = "Curado!";
                MotorGrafico::tiempoAviso = 2.0f;
            }
            else {
                MotorGrafico::mensajeAviso = "Curar fallo!";
                MotorGrafico::tiempoAviso = 2.0f;
            }
        }
        else {
            MotorGrafico::mensajeAviso = "No hay objetivo!";
            MotorGrafico::tiempoAviso = 2.0f;
        }
        modo_curar = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Partida;
    }

    if (modo_escudo) {
        Personaje* obj = casilla.getPersonaje();
        if (menu && obj) {
            bool ejecutado = menu->activarHabilidad(4, personaje_seleccionado, obj, nullptr);
            if (ejecutado) turno_actual = 1 - turno_actual;
        }
        modo_escudo = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Partida;
    }

    if (modo_inmunidad) {
        Personaje* obj = casilla.getPersonaje();
        if (menu && obj) {
            bool ejecutado = menu->activarHabilidad(5, personaje_seleccionado, obj, nullptr);
            if (ejecutado) turno_actual = 1 - turno_actual;
        }
        modo_inmunidad = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Partida;
    }

    if (personaje_seleccionado == nullptr) {
        Personaje* p = casilla.getPersonaje();
        if (p && p->estaVivo()) {
            bool turno_ok = (turno_actual == 0 && p->getTurno() == Turno::TURNO_DE_MANANA) ||
                (turno_actual == 1 && p->getTurno() == Turno::TURNO_DE_TARDE);
            if (turno_ok) {
                personaje_seleccionado = p;
                es_lider_seleccionado = (p->getMenu() != nullptr);
                casillas_iluminadas = Geometria::getCasillasAccesibles(*p, tab_);
            }
            else {
                MotorGrafico::mensajeAviso = "No es tu turno!";
                MotorGrafico::tiempoAviso = 2.0f;
            }
        }
        else {
            MotorGrafico::mensajeAviso = "Eso no se puede hacer!";
            MotorGrafico::tiempoAviso = 2.0f;
        }
    }
    else {
        ResultadoMover res = tab_.moverPersonaje(personaje_seleccionado, casilla);
        if (res == ResultadoMover::OK) {
            turno_actual = 1 - turno_actual;
            decrementarEstados();

            Modos_juego fin = comprobarFinPartida();
            if (fin != Modos_juego::Partida) return fin;
        }
        else if (res == ResultadoMover::CHOQUE) {
            Personaje* defensor = tab_.getPendienteLocal();
            if (defensor != nullptr && defensor->getInmune()) {
                defensor->decrementarInmunidad();
                tab_.limpiarPendiente();
                turno_actual = 1 - turno_actual;
                decrementarEstados();
                personaje_seleccionado = nullptr; casillas_iluminadas.clear();
                return Modos_juego::Partida;
            }
            arena->iniciarCombate(tab_.getPendienteLocal(), tab_.getPendienteInvasor(), modo_actual, tab_.getFase());
            personaje_seleccionado = nullptr; casillas_iluminadas.clear();
            return Modos_juego::Arena_Combate;

        }
        else {
            MotorGrafico::mensajeAviso = "Movimiento no valido!";
            MotorGrafico::tiempoAviso = 2.0f;
        }
        personaje_seleccionado = nullptr; casillas_iluminadas.clear();
    }
    return Modos_juego::Partida;
}

void Partida::registrarMuerto(Personaje* p) {
    if (!p || p->estaVivo()) return;
    if (p->getTurno() == Turno::TURNO_DE_MANANA)
        muertosAliados_manana.push_back(p);
    else
        muertosAliados_tarde.push_back(p);
}

Modos_juego Partida::turnoMaquina() {
    // Solo juega la maquina en modo 1 jugador.
    if (modo_actual != 1) return Modos_juego::Partida;
    // No mover si el humano tiene abierto el popup de salir.
    if (mostrar_popup)    return Modos_juego::Partida;

    // equipo_j2 = bando de la IA (1 = mañana, 2 = tarde).
    // turno_actual usa otra codificacion (0 = mañana, 1 = tarde).
    int idxTurnoIA = equipo_j2 - 1;
    if (turno_actual != idxTurnoIA) {
        ia_pensando_ = false;   // ha vuelto el turno al humano: reset
        return Modos_juego::Partida;
    }

    // Retardo de "pensamiento": el jugador necesita ver el tablero antes
    // de que la maquina mueva. Sin esto la IA mueve al instante y resulta confuso.
    int ahora = glutGet(GLUT_ELAPSED_TIME);
    const int INTERVALO_PENSAMIENTO_IA = 1200; // ms
    if (!ia_pensando_) {
        ia_pensando_ = true;
        ia_tiempoInicioTurno_ = ahora;
        return Modos_juego::Partida;            // primer tick: empieza a "pensar"
    }
    if (ahora - ia_tiempoInicioTurno_ < INTERVALO_PENSAMIENTO_IA)
        return Modos_juego::Partida;            // todavia pensando

    // Ya paso el tiempo de espera: la maquina juega.
    ia_pensando_ = false;

    Turno turnoIA = (equipo_j2 == 1) ? Turno::TURNO_DE_MANANA
        : Turno::TURNO_DE_TARDE;

    ResultadoMover res = ia_.jugarTurno(tab_, turnoIA);

    if (res == ResultadoMover::CHOQUE) {
        Personaje* defensor = tab_.getPendienteLocal();
        // Mismo flujo que el humano: abrir la arena de combate. NO limpiar
      // pendientes aqui; resolverCombate() los consume y limpia al final.
        if (defensor != nullptr && defensor->getInmune()) {
            defensor->decrementarInmunidad();
            tab_.limpiarPendiente();
            turno_actual = 1 - turno_actual;
            decrementarEstados();
            personaje_seleccionado = nullptr; casillas_iluminadas.clear();
            return Modos_juego::Partida;
        }
        arena->iniciarCombate(tab_.getPendienteLocal(), tab_.getPendienteInvasor(), modo_actual, tab_.getFase());
        personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Arena_Combate;
    }

    if (res == ResultadoMover::OK) {
        turno_actual = 1 - turno_actual;
        decrementarEstados();

        Modos_juego fin = comprobarFinPartida();
        if (fin != Modos_juego::Partida) return fin;
    }
    else {
        // ILEGAL: la maquina no encontro jugada. Cede el turno para que la
        // partida no se bloquee (caso extremo, casi imposible en la practica).
        turno_actual = 1 - turno_actual;
    }
    return Modos_juego::Partida;
}

void Partida::tecladoHabilidades(unsigned char key) {
    if (!es_lider_seleccionado || !personaje_seleccionado) return;
    Menu_habilidades* menu = personaje_seleccionado->getMenu();
    if (!menu) return;
    if (key == '1' && menu->puedeUsar(1)) modo_revivir = true;
    if (key == '2' && menu->puedeUsar(2)) modo_inmovilizar = true;
    if (key == '3' && menu->puedeUsar(0)) modo_teleport = true;
    if (key == '4' && menu->puedeUsar(3)) modo_curar = true;
    if (key == '5' && menu->puedeUsar(4)) modo_escudo = true;
    if (key == '6' && menu->puedeUsar(5)) modo_inmunidad = true;
    glutPostRedisplay();
}

void Partida::dibujaSeleccion() { MotorGrafico::get_instance().dibujaSeleccion(personaje_seleccionado, casillas_iluminadas); }
void Partida::dibujaHabilidades() { MotorGrafico::get_instance().dibujaHabilidades(personaje_seleccionado, modo_teleport, modo_inmovilizar, modo_revivir); }
void Partida::dibujaInmovilizados() { MotorGrafico::get_instance().dibujaInmovilizados(tab_); }
void Partida::dibujaBarrasVida() { MotorGrafico::get_instance().dibujaBarrasVida(tab_, personaje_seleccionado); }
void Partida::dibujaEscudos() { MotorGrafico::get_instance().dibujaEscudos(tab_); }
void Partida::dibujaInmunidad() { MotorGrafico::get_instance().dibujaInmunidad(tab_); }
void Partida::dibujaAviso() { MotorGrafico::get_instance().dibujaAviso(); }

void Partida::teclado(unsigned char key) {
    if (key == 27) mostrar_popup = false;
    tecladoHabilidades(key);
}

void Partida::reset() {
    for (int f = 0; f < 9; f++) for (int c = 0; c < 9; c++) tab_.getCasilla(f, c).setPersonaje(nullptr);
    ETSIDI::stopMusica(); ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false; modo_actual = modo_juego; turno_actual = turno_inicio;
    muertosAliados_manana.clear();
    muertosAliados_tarde.clear();

    // Limpiar estado transitorio que pueda apuntar a objetos que vamos a
    // borrar, para no dejar punteros colgando al reiniciar la partida.
    personaje_seleccionado = nullptr;
    es_lider_seleccionado = false;
    modo_teleport = modo_inmovilizar = modo_revivir = false;
    modo_curar = modo_escudo = modo_inmunidad = false;
    ia_pensando_ = false; ia_tiempoInicioTurno_ = 0;
    casillas_iluminadas.clear();
    delete carta_actual; carta_actual = nullptr;
    nombre_carta_cargada = "";
    tab_.reset();

    for (auto p : personajes) delete p; for (auto d : dibujos) delete d;
    personajes.clear(); dibujos.clear();

    // Piezas UPM
    personajes.push_back(new Profesor_SS(tab_.getCasilla(4, 0)));
    personajes.push_back(new PLC(tab_.getCasilla(1, 0))); personajes.push_back(new PLC(tab_.getCasilla(7, 0)));
    personajes.push_back(new Moto_electrica(tab_.getCasilla(2, 0))); personajes.push_back(new Moto_electrica(tab_.getCasilla(6, 0)));
    personajes.push_back(new Fuente_de_tension_de_bateria(tab_.getCasilla(3, 0)));
    personajes.push_back(new Copilot(tab_.getCasilla(5, 0)));
    personajes.push_back(new Microprocesador_M(tab_.getCasilla(0, 0))); personajes.push_back(new Microprocesador_M(tab_.getCasilla(8, 0)));
    personajes.push_back(new Multimetro(tab_.getCasilla(0, 1))); personajes.push_back(new Multimetro(tab_.getCasilla(8, 1)));
    for (int i = 1; i <= 7; i++) personajes.push_back(new Circuito_integrado_M(tab_.getCasilla(i, 1)));

    personajes.push_back(new Profesor_MH(tab_.getCasilla(4, 8)));
    personajes.push_back(new Microprocesador_T(tab_.getCasilla(0, 8))); personajes.push_back(new Microprocesador_T(tab_.getCasilla(8, 8)));
    personajes.push_back(new Osciloscopio(tab_.getCasilla(0, 7))); personajes.push_back(new Osciloscopio(tab_.getCasilla(8, 7)));
    personajes.push_back(new Brazo_robot(tab_.getCasilla(1, 8))); personajes.push_back(new Brazo_robot(tab_.getCasilla(7, 8)));
    personajes.push_back(new Fuente_de_corriente(tab_.getCasilla(3, 8)));
    personajes.push_back(new Moto_petrol(tab_.getCasilla(2, 8))); personajes.push_back(new Moto_petrol(tab_.getCasilla(6, 8)));
    personajes.push_back(new Gemini(tab_.getCasilla(5, 8)));
    for (int i = 1; i <= 7; i++) personajes.push_back(new Circuito_integrado_T(tab_.getCasilla(i, 7)));

    // Crear un DibujoPersonaje por cada personaje
    for (auto p : personajes)
        dibujos.push_back(new DibujoPersonaje(p));
}

// ============================================================
//  Comprueba si la partida ha terminado.
//  Devuelve el nuevo estado del juego:
//    - Modos_juego::Partida  -> la partida sigue
//    - Modos_juego::MENU     -> la partida termino
// ============================================================
Modos_juego Partida::comprobarFinPartida() {
    CondicionVictoria r = FinPartida::comprobar(personajes, tab_);

    if (!FinPartida::partidaTerminada(r))
        return Modos_juego::Partida;

    // ── DEBUG: imprimir en consola quien ha ganado ──────────────
    bool ganaMan = FinPartida::ganaManana(r);
    ResultadoPartida res = ganaMan ? ResultadoPartida::VICTORIA_MANANA
        : ResultadoPartida::VICTORIA_TARDE;
    Turno bandoGanador = ganaMan ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;

    // Puntuacion sencilla: piezas que le quedan en juego al ganador.
    int piezas = 0;
    for (auto* p : personajes)
        if (p && p->estaVivo() && p->getCasillaActual() != nullptr
            && p->getTurno() == bandoGanador)
            piezas++;
    int puntuacion = piezas * 100;
    std::string nombre = ganaMan ? "Turno de Manana" : "Turno de Tarde";

    std::cout << "[FIN PARTIDA] gana "
        << (ganaMan ? "MANANA" : "TARDE")
        << " (puntuacion " << puntuacion << ")\n";

    if (pantalla_final != nullptr)
        pantalla_final->setResultado(res, puntuacion);


    return Modos_juego::Pantalla_Final;
}

void Partida::decrementarEstados() {
    for (auto p : personajes) p->decrementarInmovilizacion();
    for (auto p : personajes) p->decrementarInmunidad();
}

void Partida::screenToGame(int x, int y, float& cx, float& cy) {
    int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
    int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
    int tam = min(ventana_w, ventana_h);
    int offsetX = (ventana_w - tam) / 2;
    int offsetY = (ventana_h - tam) / 2;
    cx = ((x - offsetX) / (float)tam) * 800 - 400;
    cy = 400 - ((y - offsetY) / (float)tam) * 800;
}

Partida::~Partida() {
    delete fondo;
    delete abandonar_partida;
    delete popup_salir;
    delete carta_actual;
    for (auto p : personajes) delete p;
    for (auto d : dibujos) delete d;
}

ArenaCombate::~ArenaCombate() {
    delete fondo_arena;
    delete abandonar_partida;
    delete popup_salir;
    for (auto p : proyectiles_) delete p;
}