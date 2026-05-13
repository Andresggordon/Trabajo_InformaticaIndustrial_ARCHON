#pragma once

class Personaje;
class Casilla;

class Menu_habilidades {
public:
    bool usarTeleport(Personaje* usuario, Casilla* destino);
    bool usarRevivir(Personaje* usuario, Personaje* objetivo);
    bool usarInmovilizar(Personaje* usuario, Personaje* objetivo);

    bool puedeUsarTeleport() const { return !teleport_usado; }
    bool puedeUsarRevivir() const { return !revivir_usado; }
    bool puedeUsarInmovilizar() const { return !inmovilizar_usado; }

private:
    bool teleport_usado = false;
    bool revivir_usado = false;
    bool inmovilizar_usado = false;
};