/**
 * @file Modos_juego.h
 * @brief Define la enumeración global de los estados de la máquina de estados del juego.
 *
 * @details Contiene la clase enumerada `Modos_juego`, que actúa como el vocabulario central
 * para el enrutamiento de la aplicación en `main.cpp`. Al estandarizar los estados (Menú,
 * Partida, Arena de Combate, Pantalla Final, etc.), permite que las distintas clases devuelvan
 * el estado al que van a pasar.
 */

#pragma once

enum class Modos_juego {
    Pantalla_carga, MENU, Pantalla_Ranking,
    Eleccion_1jugador, Eleccion_2jugadores, Eleccion2_1jugador, Partida, Salir_partida,Pantalla_Final,Arena_Combate 
};