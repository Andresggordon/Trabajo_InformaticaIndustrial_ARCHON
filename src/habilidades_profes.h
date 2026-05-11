#pragma once

enum class habilidades {
    TELEPORT,
    REVIVIR,
    INMOVILIZA,
};

class Menu_habilidades {
public:
    Menu_habilidades() {}
    void resetHabilidad() { habilidadUsada = false; }

    bool Usar_habilidad(habilidades a, int& vida, int vidaMax,
        int& posX, int& posY, bool& inmovilizado, int destX = 0, int destY = 0) {
        return true;
    }

private:

    bool habilidadUsada = false;

};