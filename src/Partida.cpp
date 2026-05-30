/**
 * @file Partida.cpp
 * @brief Controlador principal de la fase de juego.
 *
 * @details Implementa el patrón Singleton y actúa como coordinador entre el tablero, los personajes, la IA y la arena de combate.
 * Gestiona los turnos, las habilidades de los líderes, las casillas iluminadas, las barras de vida y la detección del fin de partida.
 * */

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

// Lista de inicialización 
Partida::Partida() : tiempo_inicio_turno_(glutGet(GLUT_ELAPSED_TIME)), temporizador_activo_(false), mostrar_popup(false), boton_activo(0), pausa_habilidad(false), tiempo_pausa_inicio(0) {
    fondo = new ETSIDI::Sprite("assets/menu_imagenes/fondo_partida.png", 0, 0, 800, 800);
    abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
    popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
}

void Partida::dibuja() { fondo->draw(); }

void Partida::dibujaextra() {
    // Gestiona que las piezas entren de una en una al inicio
    gestionarIntro();

    //Cartelito para saltar la animación 
    if (intro_activa) {
        MotorGrafico::get_instance().dibujaCartelSaltarIntro();
    }

    abandonar_partida->draw();
    if (personaje_seleccionado != nullptr) {
        std::string ruta = personaje_seleccionado->getNombreCarta();
        if (ruta != nombre_carta_cargada) {
            //delete carta_actual;
            carta_actual = new ETSIDI::Sprite(ruta.c_str(), 0, 0, 800, 800);
            nombre_carta_cargada = ruta;
        }
        carta_actual->draw();
        
        MotorGrafico::get_instance().dibujarVidaPanel(personaje_seleccionado);
    }
    else { nombre_carta_cargada = ""; }

    if (mostrar_popup) popup_salir->draw();

    int hab_activa = 0;
    if (modo_revivir) hab_activa = 1;
    else if (modo_inmovilizar) hab_activa = 2;
    else if (modo_teleport) hab_activa = 3;
    else if (modo_curar) hab_activa = 4;
    else if (modo_escudo) hab_activa = 5;
    else if (modo_inmunidad) hab_activa = 6;

    // SOLO dibujar el cartel si el juego está en la pausa de habilidad
    if (hab_activa != 0 && pausa_habilidad) {
        MotorGrafico::get_instance().dibujarIndicacionesHabilidades(hab_activa);
    }

    MotorGrafico::get_instance().dibujaTemporizador(getTiempoRestante(), temporizador_activo_);
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

    if (pausa_habilidad) return Modos_juego::Partida; 

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
    
    if (!intro_activa) {
        Casilla& casilla = tab_.getCasilla(fil, col);
        Menu_habilidades* menu = personaje_seleccionado ? personaje_seleccionado->getMenu() : nullptr;

        if (modo_teleport) {
            if (menu) {
                Casilla* origen = personaje_seleccionado->getCasillaActual();
                menu->activarHabilidad(0, personaje_seleccionado, nullptr, &casilla);
                if (personaje_seleccionado->getCasillaActual() != origen) {
                    personaje_seleccionado->setTeletransportado(true);
                }
            }
            if (menu && !menu->puedeUsar(0)) {
                turno_actual = 1 - turno_actual;
                temporizador_activo_ = false;
            }
            modo_teleport = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
            return comprobarFinPartida();
        }

        if (modo_inmovilizar) {
            Personaje* obj = casilla.getPersonaje();
            if (menu && obj) {
                bool ejecutado = menu->activarHabilidad(2, personaje_seleccionado, obj, nullptr);
                if (ejecutado) {
                    turno_actual = 1 - turno_actual;
                    temporizador_activo_ = false;
                }
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
                    temporizador_activo_ = false;

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
                    temporizador_activo_ = false;
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
                if (ejecutado) {
                    turno_actual = 1 - turno_actual;
                    temporizador_activo_ = false;
                }
            }
            modo_escudo = false; personaje_seleccionado = nullptr; casillas_iluminadas.clear();
            return Modos_juego::Partida;
        }

        if (modo_inmunidad) {
            Personaje* obj = casilla.getPersonaje();
            if (menu && obj) {
                bool ejecutado = menu->activarHabilidad(5, personaje_seleccionado, obj, nullptr);
                if (ejecutado) {
                    turno_actual = 1 - turno_actual;
                    temporizador_activo_ = false;
                }
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

                    // El jugador actual hace su primer clic: encendemos el reloj de arena
                    if (!temporizador_activo_) {
                        reiniciarTemporizador();
                    }
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

                temporizador_activo_ = false; // Deja el reloj listo y congelado para el rival

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

                    temporizador_activo_ = false;

                    personaje_seleccionado = nullptr; casillas_iluminadas.clear();
                    return Modos_juego::Partida;
                }

                entradaArena();

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
    // 1. Temporizador de turno
    if (temporizador_activo_ && getTiempoRestante() == 0) {
        forzarFinDeTurno();
        MotorGrafico::mensajeAviso = "Tiempo agotado!";
        MotorGrafico::tiempoAviso = 2.0f;
        return Modos_juego::Partida;
    }

    // 2. Lógica de juego
    if (modo_actual != 1) return Modos_juego::Partida;
    if (mostrar_popup)    return Modos_juego::Partida;

    int idxTurnoIA = equipo_j2 - 1;
    if (turno_actual != idxTurnoIA) {
        ia_pensando_ = false;
        return Modos_juego::Partida;
    }

    if (!temporizador_activo_) {
        reiniciarTemporizador();
    }

    int ahora = glutGet(GLUT_ELAPSED_TIME);
    const int INTERVALO_PENSAMIENTO_IA = 1200;
    if (!ia_pensando_) {
        ia_pensando_ = true;
        ia_tiempoInicioTurno_ = ahora;
        return Modos_juego::Partida;
    }
    if (ahora - ia_tiempoInicioTurno_ < INTERVALO_PENSAMIENTO_IA)
        return Modos_juego::Partida;

    ia_pensando_ = false;

    Turno turnoIA = (equipo_j2 == 1) ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;

    ResultadoMover res = ia_.jugarTurno(tab_, turnoIA);

    if (res == ResultadoMover::CHOQUE) {
        Personaje* defensor = tab_.getPendienteLocal();
        if (defensor != nullptr && defensor->getInmune()) {
            defensor->decrementarInmunidad();
            tab_.limpiarPendiente();
            turno_actual = 1 - turno_actual;
            decrementarEstados();

            temporizador_activo_ = false;

            personaje_seleccionado = nullptr; casillas_iluminadas.clear();
            return Modos_juego::Partida;
        }

        entradaArena();
        arena->iniciarCombate(tab_.getPendienteLocal(), tab_.getPendienteInvasor(), modo_actual, tab_.getFase());
        personaje_seleccionado = nullptr; casillas_iluminadas.clear();
        return Modos_juego::Arena_Combate;
    }

    if (res == ResultadoMover::OK) {
        turno_actual = 1 - turno_actual;
        decrementarEstados();
        temporizador_activo_ = false;

        Modos_juego fin = comprobarFinPartida();
        if (fin != Modos_juego::Partida) return fin;
    }
    else {
        turno_actual = 1 - turno_actual;
        temporizador_activo_ = false;
    }
    return Modos_juego::Partida;
}

void Partida::tecladoHabilidades(unsigned char key) {
    if (!es_lider_seleccionado || !personaje_seleccionado) return;
    Menu_habilidades* menu = personaje_seleccionado->getMenu();
    if (!menu) return;

    int id_habilidad = -1;
    switch (key) {
    case '1': id_habilidad = 1; break; // Revivir
    case '2': id_habilidad = 2; break; // Inmovilizar
    case '3': id_habilidad = 0; break; // Teleport (tu índice interno es 0)
    case '4': id_habilidad = 3; break; // Curar
    case '5': id_habilidad = 4; break; // Escudo
    case '6': id_habilidad = 5; break; // Inmunidad
    default: return; // Si pulsa cualquier otra tecla, salimos directamente
    }

    if (menu->puedeUsar(id_habilidad)) {

        // Apagamos todas las habilidades para evitar que se acumulen los carteles
        modo_revivir = modo_inmovilizar = modo_teleport = false;
        modo_curar = modo_escudo = modo_inmunidad = false;

        // Encendemos exclusivamente la solicitada
        switch (key) {
        case '1': modo_revivir = true; break;
        case '2': modo_inmovilizar = true; break;
        case '3': modo_teleport = true; break;
        case '4': modo_curar = true; break;
        case '5': modo_escudo = true; break;
        case '6': modo_inmunidad = true; break;
        }

        // Activamos la pausa de tiempo
        if (!pausa_habilidad) {
            pausa_habilidad = true;
            tiempo_pausa_inicio = glutGet(GLUT_ELAPSED_TIME);
        }
    }

    glutPostRedisplay();
}

void Partida::dibujaSeleccion() {
    MotorGrafico::get_instance().dibujaSeleccion(personaje_seleccionado, casillas_iluminadas);
}
void Partida::dibujaHabilidades() {
    MotorGrafico::get_instance().dibujaHabilidades(personaje_seleccionado, modo_teleport, modo_inmovilizar, modo_revivir, modo_curar, modo_escudo, modo_inmunidad);
}
void Partida::dibujaInmovilizados() { MotorGrafico::get_instance().dibujaInmovilizados(tab_); }

void Partida::dibujaBarrasVida() {
    if (!intro_activa) {
        MotorGrafico::get_instance().dibujaBarrasVida(tab_, personaje_seleccionado);
    }
}

void Partida::dibujaEscudos() { MotorGrafico::get_instance().dibujaEscudos(tab_); }
void Partida::dibujaInmunidad() { MotorGrafico::get_instance().dibujaInmunidad(tab_); }
void Partida::dibujaAviso() { MotorGrafico::get_instance().dibujaAviso(); }

void Partida::teclado(unsigned char key) {
    if (key == 27) { 
        if (pausa_habilidad) {
            pausa_habilidad = false;
            int tiempo_pausado = glutGet(GLUT_ELAPSED_TIME) - tiempo_pausa_inicio;
            tiempo_inicio_turno_ += tiempo_pausado; 
        }
        else if (modo_revivir || modo_inmovilizar || modo_teleport || modo_curar || modo_escudo || modo_inmunidad) {
            modo_revivir = modo_inmovilizar = modo_teleport = modo_curar = modo_escudo = modo_inmunidad = false;
            personaje_seleccionado = nullptr;
            casillas_iluminadas.clear();
        }
        else {
           
            mostrar_popup = false;
        }
    }

    if (key == ' ' && intro_activa) {
        intro_activa = false;           
        indice_intro = dibujos.size();  

        for (auto d : dibujos) {
            d->arrancar();              
            d->forzarTeletransporte();  
        }
    }

    tecladoHabilidades(key);


}

void Partida::gestionarIntro() {
    if (!intro_activa || dibujos.empty()) return;

    if (indice_intro < dibujos.size()) {
        DibujoPersonaje* actual = dibujos[indice_intro];

        
        actual->arrancar();

        float destX = MotorGrafico::INICIO_X + actual->getPersonaje()->getPosX() * MotorGrafico::TAM;
        float destY = MotorGrafico::INICIO_Y + actual->getPersonaje()->getPosY() * MotorGrafico::TAM;

        if (actual->haLlegado(destX, destY)) {
            indice_intro++; 
        }
    }
    else {
        intro_activa = false; // Ya han entrado todos
    }
}

void Partida::reset() {

    pausa_habilidad = false;
    tiempo_pausa_inicio = 0;


    for (int f = 0; f < 9; f++) for (int c = 0; c < 9; c++) tab_.getCasilla(f, c).setPersonaje(nullptr);
    ETSIDI::stopMusica(); ETSIDI::playMusica("assets/sonidos/partida.mp3", true);
    mostrar_popup = false; modo_actual = modo_juego; turno_actual = turno_inicio;
    muertosAliados_manana.clear();
    muertosAliados_tarde.clear();

    personaje_seleccionado = nullptr;
    es_lider_seleccionado = false;
    modo_teleport = modo_inmovilizar = modo_revivir = false;
    modo_curar = modo_escudo = modo_inmunidad = false;
    ia_pensando_ = false; ia_tiempoInicioTurno_ = 0;
    casillas_iluminadas.clear();
    //delete carta_actual;
    carta_actual = nullptr;
    nombre_carta_cargada = "";
    tab_.reset();
    temporizador_activo_ = false;

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

    // Ocultar piezas en la intro
    for (auto d : dibujos) {
        Personaje* p = d->getPersonaje();

        float inicioX = (p->getTurno() == Turno::TURNO_DE_MANANA) ? -550.0f : 550.0f;
        float inicioY = MotorGrafico::INICIO_Y + p->getPosY() * MotorGrafico::TAM;

        d->iniciarIntroFuera(inicioX, inicioY);
    }

    // Reseteamos el gestor de la intro para que empiece por el personaje 0
    indice_intro = 0;
    intro_activa = true;
    despliegue_inicial = true;

}
Modos_juego Partida::comprobarFinPartida() {
    CondicionVictoria r = FinPartida::comprobar(personajes, tab_);

    if (!FinPartida::partidaTerminada(r))
        return Modos_juego::Partida;

    bool ganaMan = FinPartida::ganaManana(r);
    ResultadoPartida res = ganaMan ? ResultadoPartida::VICTORIA_MANANA
        : ResultadoPartida::VICTORIA_TARDE;
    Turno bandoGanador = ganaMan ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;

    int piezasGanadorVivas = 0;
    int piezasRivalEliminadas = 0;
    for (auto* p : personajes) {
        if (!p) continue;
        bool enJuego = p->estaVivo() && p->getCasillaActual() != nullptr;
        if (p->getTurno() == bandoGanador) {
            if (enJuego) piezasGanadorVivas++;
        }
        else {
            if (!enJuego) piezasRivalEliminadas++;
        }
    }
    int puntuacion = (piezasGanadorVivas + piezasRivalEliminadas) * 100;
    std::string nombre = ganaMan ? "Turno de Manana" : "Turno de Tarde";

    std::cout << "[FIN PARTIDA] gana "
        << (ganaMan ? "MANANA" : "TARDE")
        << " (puntuacion " << puntuacion << ")\n";

    bool ganadorEsHumano = (modo_actual == 2) ||
        (modo_actual == 1 && ((ganaMan && equipo_j1 == 1) || (!ganaMan && equipo_j1 == 2)));

    if (pantalla_final != nullptr)
        pantalla_final->setResultado(res, puntuacion, ganadorEsHumano);

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

void Partida::reiniciarTemporizador() {
    tiempo_inicio_turno_ = glutGet(GLUT_ELAPSED_TIME);
    temporizador_activo_ = true;
}

int Partida::getTiempoRestante() const {
    if (!temporizador_activo_) return TIEMPO_MAXIMO_TURNO / 1000;

    int ahora = pausa_habilidad ? tiempo_pausa_inicio : glutGet(GLUT_ELAPSED_TIME);
    int tiempo_pasado = ahora - tiempo_inicio_turno_;
    int tiempo_restante_ms = TIEMPO_MAXIMO_TURNO - tiempo_pasado;

    if (tiempo_restante_ms <= 0) return 0;
    return tiempo_restante_ms / 1000;
}

void Partida::forzarFinDeTurno() {
    turno_actual = 1 - turno_actual;
    decrementarEstados();
    personaje_seleccionado = nullptr;
    casillas_iluminadas.clear();
    reiniciarTemporizador();
    temporizador_activo_ = false;
}

void Partida::regresarDeArena() {
    for (auto d : dibujos) {
        float realX = MotorGrafico::INICIO_X + d->getPersonaje()->getPosX() * MotorGrafico::TAM;
        float realY = MotorGrafico::INICIO_Y + d->getPersonaje()->getPosY() * MotorGrafico::TAM;
        d->setPosicionVisual(realX, realY);
    }
    reiniciarTemporizador();
}

void Partida::entradaArena() {
    for (auto d : dibujos) {
        d->getPersonaje()->setTeletransportado(true);
    }
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