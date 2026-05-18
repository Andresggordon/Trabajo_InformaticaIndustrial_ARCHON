#pragma once
#include <string>
#include <vector>
#include <memory>

class Personaje;
class Casilla;

// ────────────────────────────────────────
// CLASE BASE ABSTRACTA
// ────────────────────────────────────────
class Habilidad {
public:
    explicit Habilidad(const std::string& nombre)
        : nombre(nombre), usada(false) {
    }

    virtual ~Habilidad() = default;

    virtual bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) = 0;

    bool        puedeUsar()   const { return !usada; }
    std::string getNombre()   const { return nombre; }

protected:
    std::string nombre;
    bool        usada;
};

// ────────────────────────────────────────
// SUBCLASES (una por habilidad)
// ────────────────────────────────────────
class HabilidadTeleport : public Habilidad {
public:
    HabilidadTeleport() : Habilidad("Teleport") {}
    bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) override;
};

class HabilidadRevivir : public Habilidad {
public:
    HabilidadRevivir() : Habilidad("Revivir") {}
    bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) override;
};

class HabilidadInmovilizar : public Habilidad {
public:
    HabilidadInmovilizar() : Habilidad("Inmovilizar") {}
    bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) override;
};

class Menu_habilidades {
public:
    Menu_habilidades();

    bool        activarHabilidad(int indice, Personaje* usuario, Personaje* objetivo, Casilla* destino);
    bool        puedeUsar(int indice)      const;
    std::string getNombre(int indice)      const;
    int         numHabilidades()           const;

private:
    std::vector<std::unique_ptr<Habilidad>> habilidades;
};