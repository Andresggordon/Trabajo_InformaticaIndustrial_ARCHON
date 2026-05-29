#include "dibujo_personajes.h"
#include "MotorGrafico.h"
#include <cmath>
#include <GL/freeglut.h> // Necesario para el reloj de las animaciones de las piernas

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

    // 2. EL TELETRANSPORTE INSTANTÁNEO
    if (modelo->getTeletransportado()) {
        x_visual = x;
        y_visual = y;
        modelo->setTeletransportado(false);
    }
    // 3. MOVIMIENTO LENTO Y UNIFORME (MRU)
    else if (!esperando_intro) {
        float dx = x - x_visual;
        float dy = y - y_visual;
        float distancia = std::sqrt(dx * dx + dy * dy);

        float velocidad = intro_terminada ? 0.28f : 0.4f;

        if (distancia > velocidad) {
            // Avanza a velocidad constante (MRU)
            x_visual += (dx / distancia) * velocidad;
            y_visual += (dy / distancia) * velocidad;
        }
        else {
            // Llegó a la casilla exacta
            x_visual = x;
            y_visual = y;

            // ¡MAGIA!: Al pisar su casilla por primera vez, la intro se acaba para siempre
            intro_terminada = true;
        }
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
        int ahora = glutGet(GLUT_ELAPSED_TIME);

        // Evaluamos si físicamente se está moviendo en este fotograma para mover las piernas
        bool esta_caminando = !esperando_intro &&
            (std::abs(x - x_visual) > 1.0f || std::abs(y - y_visual) > 1.0f);

        if (modelo->getFilasAnimacion() > 1 && (modelo->getEnMovimiento() || esta_caminando)) {
            // --- MODO CAMINAR ---
            int frame_caminar = (ahora / 100) % cols;
            frame_index = frame_caminar;
        }
        else {
            // --- MODO IDLE (Respirar) ---
            int ms_por_frame = modelo->getTiempoAnimacion();
            int frame_idle = (ahora / ms_por_frame) % cols;
            frame_index = cols + frame_idle;
        }

        anim->setState(frame_index, true);
        anim->flip(hacer_flip, false);

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