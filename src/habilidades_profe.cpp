#include "habilidades_profes.h"
#include "personaje.h"
#include "Casilla.h"

Menu_habilidades::Menu_habilidades() {
    habilidades.push_back(std::make_unique<HabilidadTeleport>());
    habilidades.push_back(std::make_unique<HabilidadRevivir>());
    habilidades.push_back(std::make_unique<HabilidadInmovilizar>());
    habilidades.push_back(std::make_unique<HabilidadCurar>());       
    habilidades.push_back(std::make_unique<HabilidadEscudo>()); 
    habilidades.push_back(std::make_unique<HabilidadInmunidad>());
}

bool Menu_habilidades::activarHabilidad(int i, Personaje* u, Personaje* o, Casilla* d) {
    if (i < 0 || i >= (int)habilidades.size()) return false;
    return habilidades[i]->usar(u, o, d);
}

bool        Menu_habilidades::puedeUsar(int i)    const { return habilidades[i]->puedeUsar(); }
std::string Menu_habilidades::getNombre(int i)    const { return habilidades[i]->getNombre(); }
int         Menu_habilidades::numHabilidades()    const { return (int)habilidades.size(); }

bool HabilidadTeleport::usar(Personaje* usuario, Personaje* /*objetivo*/, Casilla* destino) {
    if (usada || !usuario || !destino) return false;
    if (destino->getPersonaje() != nullptr) return false;

    Casilla* origen = usuario->getCasillaActual();
    if (!origen) return false;

    origen->setPersonaje(nullptr);
    destino->setPersonaje(usuario);
    usuario->setCasillaActual(destino);
    usada = true;
    return true;
}


bool HabilidadRevivir::usar(Personaje* usuario, Personaje* objetivo, Casilla* /*destino*/) {
    if (usada) return false;
    usada = true;
    return true;
}

bool HabilidadInmovilizar::usar(Personaje* usuario, Personaje* objetivo, Casilla* /*destino*/) {
    if (usada || !usuario || !objetivo) return false;
    if (objetivo->getTurno() == usuario->getTurno()) return false;
    if (!objetivo->estaVivo()) return false;

    objetivo->setInmovilizado(true);
    usada = true;
    return true;
}

bool HabilidadCurar::usar(Personaje* usuario, Personaje* objetivo, Casilla* /*destino*/) {
    if (usada || !usuario || !objetivo) return false;
    if (objetivo->getTurno() != usuario->getTurno()) return false;  // solo aliados
    if (!objetivo->estaVivo()) return false;                         // debe estar vivo
    if (objetivo->getVidaActual() == objetivo->getVidaMax()) return false; // ya tiene vida llena

    objetivo->curar(objetivo->getVidaMax() / 2);  // cura la mitad de la vida máxima
    usada = true;
    return true;
}

bool HabilidadEscudo::usar(Personaje* usuario, Personaje* objetivo, Casilla* /*destino*/) {
    if (usada || !usuario || !objetivo) return false;
    if (objetivo->getTurno() != usuario->getTurno()) return false;  // solo aliados
    if (!objetivo->estaVivo()) return false;

    objetivo->setEscudo(true);
    usada = true;
    return true;
}

bool HabilidadInmunidad::usar(Personaje* usuario, Personaje* objetivo, Casilla*) {
    if (usada || !usuario || !objetivo) return false;
    if (objetivo->getTurno() != usuario->getTurno()) return false;
    if (!objetivo->estaVivo()) return false;

    objetivo->setInmune(true); 
    usada = true;
    return true;
}
