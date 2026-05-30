/**
 * @file habilidades_profes.h
 * @brief Define la jerarquía de habilidades activas y su menú de gestión para los líderes (Profesores).
 *
 * @details Implementa un sistema de clases derivado de una clase base abstracta (`Habilidad`) para
 * encapsular la lógica única de cada poder especial (Teleport, Revivir, Inmovilizar, Curar, Escudo,
 * Inmunidad). Además, define la clase `Menu_habilidades` como contenedor que gestiona el inventario
 * de habilidades de cada líder, validando si una acción ya ha sido consumida y ejecutando su efecto
 * específico sobre un objetivo o casilla determinada.
 */

#pragma once
#include <string>
#include <vector>
#include <memory>

class Personaje;
class Casilla;

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

class HabilidadCurar : public Habilidad {
public:
    HabilidadCurar() : Habilidad("Curar") {}
    bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) override;
};

class HabilidadEscudo : public Habilidad {
public:
    HabilidadEscudo() : Habilidad("Escudo") {}
    bool usar(Personaje* usuario, Personaje* objetivo, Casilla* destino) override;
};

class HabilidadInmunidad : public Habilidad {
public:
    HabilidadInmunidad() : Habilidad("Inmunidad") {}
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