#pragma once

enum class habilidades {
    TELEPORT,
    REVIVIR,
    INMOVILIZA,
};

class Menu_habilidades {
public:
    Menu_habilidades() {}

    void Usar_habilidad(habilidades a, int& vida, int vidaMax,
        int& posX, int& posY, bool& inmovilizado) {
        switch (a) {
        case habilidades::TELEPORT:   usar_tp(posX, posY, 0, 0); break;
        case habilidades::REVIVIR:    usar_revivir(vida, vidaMax); break;
        case habilidades::INMOVILIZA: usar_inmoviliza(inmovilizado); break;
        }
    }

private:

    void usar_tp(int& posX, int& posY, int destX, int destY) {
        posX = destX;
        posY = destY;
    }

    void usar_revivir(int& vida, int vidaMax) {
        if (vida <= 0)
            vida = vidaMax;
    }

    void usar_inmoviliza(bool& inmovilizado) {
        inmovilizado = true;
    }
};