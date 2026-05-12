#include "dibujo_personajes.h"
#include "MotorGrafico.h"

DibujoPersonaje::DibujoPersonaje(Personaje* p)
    : modelo(p), sprite(nullptr), anim(nullptr)
{
    std::string ruta = "assets/personajes_imagenes/" + p->getNombreSprite() + ".png";

    if (p->getFramesIdle() > 1) {
        anim = new ETSIDI::SpriteSequence(ruta.c_str(),
            p->getFramesIdle(), 1, p->getTiempoAnimacion(), true);
    }
    else {
        sprite = new ETSIDI::Sprite(ruta.c_str());
    }
}

DibujoPersonaje::~DibujoPersonaje() {
    delete sprite;
    delete anim;
}

void DibujoPersonaje::dibujar(float x, float y) {
    float tam = modelo->getTamanoSprite();
    float tamCasilla = MotorGrafico::TAM;

    if (anim != nullptr) {
        // SpriteSequence: origen en el centro
        anim->loop();
        anim->setPos(x + tamCasilla/2.0 + modelo->getOffsetX(),
                     y + tamCasilla + modelo->getOffsetY());
        anim->setSize(tam, tam);
        anim->draw();
    }
    else {
        // Sprite: origen en esquina inferior izquierda
        sprite->setPos(x, y);
        sprite->setSize(tam, tam);
        sprite->draw();
    }
}