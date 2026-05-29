/**
 * @file Personaje.h
 * @brief Definición de la clase base Personaje.
 *
 * @details Modela la entidad principal que interactúa en el tablero. Almacena
 * la salud, estadísticas de combate, estado actual (inmovilizado, escudo, etc.)
 * y orientación visual de cada luchador. Actúa como clase padre (base) para
 * los distintos tipos de personajes (profesores, objetos, etc.).
 */

#pragma once
#include <string>
#include "stats.h"
#include "habilidades_profes.h"

class Casilla;

enum class Turno { TURNO_DE_MANANA, TURNO_DE_TARDE };
enum class Movimiento { TIERRA, AIRE};
enum class ResultadoMover { OK, ILEGAL, CHOQUE };

class Personaje {
public:
    Personaje(std::string nombre_, int vida_, Turno turno_, Movimiento movimiento_, stats arma_, int velocidad_, int radio_mov_, Casilla& casillaInicial);    virtual ~Personaje();

    // --- CARACTERÍSTICAS VIRTUALES (A sobreescribir por subclases) ---
    virtual std::string getNombreSprite()    const = 0;
    virtual float       getTamanoSprite()    const = 0;
    virtual std::string getNombreCarta()     const = 0;
    virtual int         getFilasAnimacion()  const { return 1; }
    virtual int         getFramesIdle()      const { return 1; }
    virtual int         getTiempoAnimacion() const { return 500; }
    virtual float       getOffsetX()         const { return 0.0f; }
    virtual float       getOffsetY()         const { return 0.0f; }
    virtual std::string getNombreProyectil() const { return ""; }
    virtual Menu_habilidades* getMenu() { return nullptr; }
    virtual bool        esLider() const { return false; }

    // --- MÉTODOS DE LÓGICA Y COMBATE ---
    ResultadoMover mover(Casilla& destino);
    void recibirDano(int cantidad_);
    void curar(int cantidad_);
    bool estaVivo() const;

    // --- GETTERS ---
    std::string getNombre()          const;
    int         getPosX()            const;
    int         getPosY()            const;
    Casilla* getCasillaActual()   const;
    float       getPorcentajeVida()  const;
    int         getVidaActual()      const;
    int         getVidaMax()         const;
    stats       getArma()            const { return arma; }
    Movimiento  getMovimiento()      const { return movimiento; }
    Turno       getTurno()           const { return turno; }
    bool        estaEncarcelado()    const { return encarcelado; }
    bool        getInmovilizado()    const { return turnos_inmovilizado > 0; }
    bool        getEscudo()          const { return escudo_activo; }
    bool        getInmune()          const { return inmune_activo; }
    int         getPasosDados()      const { return pasos_dados; }
    bool        getEnMovimiento()    const { return en_movimiento; }
    bool        getMirandoDerecha()  const { return mirando_derecha; }
    bool        getMirandoIzquierda() const { return mirando_izquierda; }
    int getRadioMovimiento() const { return radio_movimiento; }

    // --- SETTERS Y ESTADOS ---
    void setCasillaActual(Casilla* c);
    void setVida(int v) { vida_actual = v; }
    void setInmovilizado(bool b) { turnos_inmovilizado = b ? 1 : 0; }
    void decrementarInmovilizacion() { if (turnos_inmovilizado > 0) turnos_inmovilizado--; }
    void setEscudo(bool b) { escudo_activo = b; }
    void decrementarEscudo() { escudo_activo = false; }
    void setInmune(bool b) { inmune_activo = b; }
    void decrementarInmunidad() { inmune_activo = false; }
    void incrementarPasos() { pasos_dados++; }
    void setEnMovimiento(bool b) { en_movimiento = b; }
    void setMirandoDerecha(bool b) { mirando_derecha = b; }
    void setMirandoIzquierda(bool b) { mirando_izquierda = b; }

    // --- TRANSICIONES VISUALES (Animación en Tablero) ---
    void iniciarAnimacionMovimiento(float x_origen, float y_origen, float x_destino, float y_destino);
    void actualizarPosicionVisual();
    float getPosXVisual() const { return posX_visual_; }
    float getPosYVisual() const { return posY_visual_; }
    bool estaEnTransicion() const { return en_transicion_; }

    // Calcula cuánto tarda visualmente en cruzar una casilla para no dar trompicones
    int getDuracionAnimacion() const {
        int vel = velocidad_movimiento > 0 ? velocidad_movimiento : 1;
        return 1000 / vel;
    }

    //Para conocer si ha habido teletransporte o no
    bool getTeletransportado() const { return recien_teletransportado; }
    void setTeletransportado(bool b) { recien_teletransportado = b; }

    int getVelocidadMovimiento() const { return velocidad_movimiento; }



protected:
    // Atributos base
    std::string nombre;
    int         vida_Max;
    int         vida_actual;
    int velocidad_movimiento;
    int radio_movimiento;
    Turno       turno;
    Movimiento  movimiento;
    stats       arma;
    Casilla* casilla_actual;

    // Estados alterados
    bool        encarcelado = false;
    int         turnos_inmovilizado = 0;
    bool        escudo_activo = false;
    bool        inmune_activo = false;

    // Estado visual (Arena de combate)
    bool mirando_derecha = true;
    bool mirando_izquierda = true;
    bool en_movimiento = false;
    int pasos_dados = 0;

    // Animación de desplazamiento (Lerp)
    bool en_transicion_ = false;
    float posX_visual_ = 0.0f;
    float posY_visual_ = 0.0f;
    float posX_destino_ = 0.0f;
    float posY_destino_ = 0.0f;
    int tiempo_inicio_animacion_ = 0;

    bool recien_teletransportado = false;
};