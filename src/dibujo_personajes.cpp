#include "dibujo_personajes.h"
#include "MotorGrafico.h"

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
    float tam = modelo->getTamanoSprite();
    float tamCasilla = MotorGrafico::TAM;

    // 1. Orientación y Espejo (Tu lógica impecable)
    bool mirar_derecha = modelo->getMirandoDerecha();
    bool mirar_izquierda = modelo->getMirandoIzquierda();
    bool hacer_flip = false;

    if (modelo->getTurno() == Turno::TURNO_DE_MANANA) hacer_flip = !mirar_derecha;
    else                                              hacer_flip = !mirar_izquierda;

    float offset_x = modelo->getOffsetX();
    if (hacer_flip) offset_x = -offset_x;

    // 2. Control Absoluto de los Frames
    if (anim != nullptr) {
        int cols = modelo->getFramesIdle();
        int frame_index = 0;

        if (modelo->getFilasAnimacion() > 1 && modelo->getEnMovimiento()) {
            // --- MODO CAMINAR ---
            // Tu PNG tiene el caminar ARRIBA (Fila 0). 
            // Por tanto, el índice va de 0 a 7. Ya no sumamos 'cols'.
            int frame_caminar = modelo->getPasosDados() % cols;
            frame_index = frame_caminar;
        }
        else {
            // --- MODO IDLE ---
            // Tu PNG tiene el IDLE ABAJO (Fila 1).
            // Sumamos 'cols' para saltar a la segunda fila (índices 8 a 15).
            int ahora = glutGet(GLUT_ELAPSED_TIME);
            int ms_por_frame = modelo->getTiempoAnimacion();
            int frame_idle = (ahora / ms_por_frame) % cols;
            frame_index = cols + frame_idle;
        }

        // Le decimos a ETSIDI: "Ponte en este frame exacto"
        anim->setState(frame_index, true);
        anim->flip(hacer_flip, false);

        anim->setPos(x + tamCasilla / 2.0 + offset_x,
            y + tamCasilla + modelo->getOffsetY());
        anim->setSize(tam, tam);
        anim->draw();
    }
    else {
        if (sprite != nullptr) {
            sprite->flip(hacer_flip, false);
            sprite->setPos(x, y);
            sprite->setSize(tam, tam);
            sprite->draw();
        }
    }
}

DibujoPersonaje::~DibujoPersonaje() {
    delete sprite;
    delete anim;
}