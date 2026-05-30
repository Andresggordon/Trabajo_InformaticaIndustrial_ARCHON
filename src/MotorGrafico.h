/**
 * @file MotorGrafico.h
 * @brief Define el motor de renderizado y dibujo mediante el patrón Singleton.
 *
 * @details Centraliza absolutamente todas las llamadas a OpenGL y ETSIDI para el renderizado.
 * Esta clase extrae la responsabilidad gráfica del coordinador lógico (`Partida`) y se encarga
 * de pintar el tablero, las piezas, las animaciones, la arena de combate, las barras de vida
 * y la interfaz de usuario (HUD), aplicando constantes espaciales estandarizadas.
 */

#pragma once
#include "Tablero.h"
#include "ETSIDI.h"
#include <GL/freeglut.h>
#include <vector>
#include <functional>

class Personaje;

class MotorGrafico {
public:
    static constexpr float TAM = 60.0f;
    static constexpr float INICIO_X = -270.0f;
    static constexpr float INICIO_Y = -270.0f;

    static MotorGrafico& get_instance() {
        static MotorGrafico instance;
        return instance;
    }

    static void dibujaAviso();
    static float tiempoAviso;       
    static std::string mensajeAviso;

    void dibujar();
    void dibujarArena();
    void dibujarBarrasHP(Personaje* local, Personaje* invasor);

    // FUNCIONES DE DIBUJO (Trasladadas desde Partida para cumplir normativa)
    void dibujaSeleccion(Personaje* seleccionado, const std::vector<Casilla*>& iluminadas);
    void dibujaHabilidades(Personaje* p, bool m_teleport, bool m_inmovilizar, bool m_revivir, bool m_curar, bool m_escudo, bool m_inmunidad);
    void dibujaInmovilizados(const Tablero& t);
    void dibujaBarrasVida(const Tablero& t, Personaje* p);
    void dibujarVidaPanel(Personaje* p);
    void dibujaEscudos(const Tablero& t);
    void dibujaInmunidad(const Tablero& t);
    void dibujaTemporizador(int tiempo_restante, bool activo);
    void dibujaCartelSaltarIntro();
    void dibujarIndicacionesHabilidades(int id_habilidad);


private:
    MotorGrafico() = default;
    void dibujarTextoBitmap(float x, float y, const char* texto);
    void dibujarTablero(const Tablero& t);
    void dibujarPersonajes(const Tablero& t, Personaje* seleccionado = nullptr);
    void dibujaCuadrado(float x, float y, float r, float g, float b);
    void dibujarPersonajesArena(Personaje* local, Personaje* invasor);
    void dibujarFondoArena();
    void dibujarBarraVida(float x, float y, Personaje* p);
    void dibujarVidaTexto(float x, float y, Personaje* p);
    void dibujarRecuadroEstado(const Tablero& t, float r, float g, float b, std::function<bool(Personaje*)> condicion);
    void setColorVida(float porcentaje);

};