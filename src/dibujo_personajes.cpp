#include "dibujo_personajes.h"
#include "MotorGrafico.h"
#include <cmath>

DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p), sprite(nullptr), anim(nullptr)
{
    std::string ruta = "assets/personajes_imagenes/" + p->getNombreSprite() + ".png";

    if (p->getFramesIdle() > 1) {
        anim = new ETSIDI::SpriteSequence(ruta.c_str(),
            p->getFramesIdle(), p->getFilasAnimacion(), p->getTiempoAnimacion(), true);
    }
    else {
        sprite = new ETSIDI::Sprite(ruta.c_str());
    }
}


void DibujoPersonaje::dibujar(float x, float y) {
    // 1. INICIALIZACIÓN DE LA POSICIÓN
    if (!inicializado) {
        x_visual = x; y_visual = y;
        inicializado = true;
    }

    // 2. EL TELETRANSPORTE INSTANTÁNEO (Habilidad)
    if (modelo->getTeletransportado()) {
        x_visual = x;
        y_visual = y;
        modelo->setTeletransportado(false);
    }

    // 3. MOVIMIENTO LINEAL CONSTANTE
    float dx = x - x_visual;
    float dy = y - y_visual;
    float distancia = std::sqrt(dx * dx + dy * dy);

    // VELOCIDAD: Píxeles que avanza por cada fotograma. 
    float velocidad = 0.2f;

    if (distancia > velocidad) {
        // Normalizamos el vector (dirección pura) y multiplicamos por la velocidad constante
        x_visual += (dx / distancia) * velocidad;
        y_visual += (dy / distancia) * velocidad;
    }
    else {
        // Si está a punto de llegar (más cerca que un solo paso), lo encajamos para que no tiemble
        x_visual = x;
        y_visual = y;
    }

    // ==========================================
    // 4. DIBUJADO DE ETSIDI
    // ==========================================
    float tam = modelo->getTamanoSprite();
    float tamCasilla = MotorGrafico::TAM;

    bool mirar_derecha = modelo->getMirandoDerecha();
    bool mirar_izquierda = modelo->getMirandoIzquierda();
    bool hacer_flip = false;

    if (modelo->getTurno() == Turno::TURNO_DE_MANANA) hacer_flip = !mirar_derecha;
    else hacer_flip = !mirar_izquierda;

    float offset_x = modelo->getOffsetX();
    if (hacer_flip) offset_x = -offset_x;

    if (anim != nullptr) {
        int cols = modelo->getFramesIdle();
        int frame_index = 0;

        if (modelo->getFilasAnimacion() > 1 && (std::abs(x - x_visual) > 1.0f || std::abs(y - y_visual) > 1.0f)) {
            // --- MODO CAMINAR AUTOMÁTICO ---
            int frame_caminar = (glutGet(GLUT_ELAPSED_TIME) / 100) % cols;
            frame_index = frame_caminar;
        }
        else {
            // --- MODO IDLE ---
            int ahora = glutGet(GLUT_ELAPSED_TIME);
            int ms_por_frame = modelo->getTiempoAnimacion();
            int frame_idle = (ahora / ms_por_frame) % cols;
            frame_index = cols + frame_idle;
        }

        anim->setState(frame_index, true);
        anim->flip(hacer_flip, false);

        // AQUÍ SE DIBUJA CON LAS VARIABLES MATEMÁTICAS SIMPLES
        anim->setPos(x_visual + tamCasilla / 2.0f + offset_x, y_visual + tamCasilla + modelo->getOffsetY());
        anim->setSize(tam, tam);
        anim->draw();
    }
    else {
        if (sprite != nullptr) {
            sprite->flip(hacer_flip, false);
            sprite->setPos(x_visual, y_visual);
            sprite->setSize(tam, tam);
            sprite->draw();
        }
    }
}

DibujoPersonaje::~DibujoPersonaje() {
    delete sprite;
    delete anim;
}

