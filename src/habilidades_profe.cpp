#include "habilidades_profes.h"
#include "personaje.h"
#include "Casilla.h"

bool Menu_habilidades::usarTeleport(Personaje* usuario, Casilla* destino) {
    if (teleport_usado || usuario == nullptr || destino == nullptr) return false;
    if (destino->getPersonaje() != nullptr) return false;

    Casilla* origen = usuario->getCasillaActual();
    if (origen == nullptr) return false;

    origen->setPersonaje(nullptr);
    destino->setPersonaje(usuario);
    usuario->setCasillaActual(destino);

    teleport_usado = true;
    return true;
}

bool Menu_habilidades::usarRevivir(Personaje* usuario, Personaje* objetivo) {
    if (revivir_usado || usuario == nullptr || objetivo == nullptr) return false;
    if (objetivo->getTurno() != usuario->getTurno()) return false;
    if (objetivo->estaVivo()) return false;

    objetivo->setVida(objetivo->getVidaMax());
    revivir_usado = true;
    return true;
}

bool Menu_habilidades::usarInmovilizar(Personaje* usuario, Personaje* objetivo) {
    if (inmovilizar_usado || usuario == nullptr || objetivo == nullptr) return false;
    if (objetivo->getTurno() == usuario->getTurno()) return false;
    if (!objetivo->estaVivo()) return false;

    objetivo->setInmovilizado(true);
    inmovilizar_usado = true;
    return true;
}