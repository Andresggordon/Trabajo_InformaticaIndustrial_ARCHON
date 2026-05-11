#pragma once
#include <vector>

enum class EstadoCasilla { BLANCA_FIJA, AZUL_FIJA, DINAMICA };
class Personaje;

class Casilla {
public:
    Casilla();

    // ── Enlace entre casillas ─────────────────────────────────────────────
    // Registra una casilla vecina con su desplazamiento relativo (dx, dy).
    // El Tablero llama a esto al inicializarse para construir la red.
    void agregarCasillaVecina(Casilla* c, int dx, int dy);


    // ── Legalidad en el movimiento ─────────────────────────────────────────────
    // Decide si el personaje p puede moverse desde ESTA casilla hasta c_destino.
    // Recibe const Personaje& porque:
    //   · Solo necesita consultar datos del personaje (radio, tipo de movimiento)
    //   · No debe modificarlo — const lo garantiza
    //   · & para no copiar el objeto entero 
    bool puedeMoverseA(const Casilla& c_destino, const Personaje& p) const; //Por qué const Personaje &p?
    

    // ── Personaje que ocupa esta casilla ──────────────────────────────────
    Personaje* getPersonaje() const;
    void setPersonaje(Personaje* p);
    
    // ── Estado de la casilla ─────────────────────────────────────────
    EstadoCasilla getEstado() const;
    void setEstado(EstadoCasilla e);
    
    // ── Coordenadas de la casilla en el tablero ─────────────────────────────────────────
    int getCol() const;
    int getFila() const;
    void setPosicion(int fila, int columna);

private:
    EstadoCasilla estado;
    Personaje* personaje;  // puntero, no propietario, la casilla tampoco es que pueda destruir al personaje, en eso son independientes

    int fila_, col_; //Posición de la casilla en el tablero es privada porque no la debe cambiar cualquiera
    
    struct CasillaVecina {
        Casilla* casilla;
        int dx, dy; 
    };

    
    std::vector<CasillaVecina> casillasvecinas; 
};