/**
 * @file ArenaCombate.h
 * @brief Define la clase ArenaCombate, encargada de gestionar la fase de combate en tiempo real.
 *
 * @details Esta clase toma el control cuando dos personajes colisionan en el tablero principal.
 * Gestiona el entorno de la arena (cuadrícula 15x15), el procesamiento de inputs del usuario
 * (tanto para un jugador como para modo multijugador local), la inteligencia artificial del rival
 * en el modo de 1 jugador, la generación y colisión de proyectiles, y los temporizadores
 * de movimiento y ataque basados en las estadísticas individuales de cada personaje.
 */

#pragma once
#include "personaje.h"
#include "Modos_juego.h"
#include "ETSIDI.h"
#include <vector>

// Forward declaration para evitar include circular con Tablero.h
enum class FaseCiclo;
class Proyectil;

//El personaje LOCAL es aquel que se encuentra en la casilla mientras el INVASOR es el personaje que se desplaza a la casilla
enum class ResultadoCombate //Declaramos los posibles resultados que se producen en el combate
{
	Gana_Local, Gana_Invasor
};

class ArenaCombate
{
public:
	
	static constexpr float TAM_CASILLA = 45.0f;
	static constexpr float INICIO_ARENA_X = -337.5f;
	static constexpr float INICIO_ARENA_Y = -337.5f;

	ArenaCombate();
	~ArenaCombate();

	void iniciarCombate(Personaje* local, Personaje* invasor, int modo, FaseCiclo fase); //Iniciar y finalizar el combate
	void finalizarCombate();
	bool combateTerminado() const; //Confirmar que el combate acabo y pasar el resultado del combate
	ResultadoCombate getResultado() const;
	void dibuja();
	void teclado(unsigned char key);
	void tecladoEspecial(int key);
	void teclaLevantada(unsigned char key);
	void teclaEspecialLevantada(int key);
	Personaje* getLocal()   const { return local_; }
	Personaje* getInvasor() const { return invasor_; }

	void update(int x, int y);
	Modos_juego click(int x, int y);
	void dibujaPopup();
	void dibujarProyectiles();

	struct PosArena
	{
		int fila, columna;
	};
	PosArena getPosLocal()   const { return posLocal_; }
	PosArena getPosInvasor() const { return posInvasor_; }

	void actualizar();
	bool mostrandoCartel() const { return mostrandoCartel_; }
	void dibujaCartel();

private:
	Personaje* local_ = nullptr; //Declaración de los personajes
	Personaje* invasor_ = nullptr;
	int modo_ = 1;
	// En modo 1: indica si el humano controla local_ (true) o invasor_ (false).
	// El humano siempre lleva su propio bando, sea defensor o atacante del choque.
	bool humanoControlaLocal_ = false;

	std::vector<Proyectil*> proyectiles_;

	static const int Filas_Arena = 15;
	static const int Columnas_Arena = 15;

	

	PosArena posLocal_;
	PosArena posInvasor_;

	bool combateTerminado_ = false; //Estado del combate 
	ResultadoCombate resultado_ = ResultadoCombate::Gana_Local;

	void resolverResultado(); //Método para trabajar intero
	bool moverEnArena(PosArena& pos, int df, int dc);

	ETSIDI::Sprite* fondo_arena = nullptr;
	ETSIDI::Sprite* abandonar_partida;
	ETSIDI::Sprite* indicador_pregunta = nullptr;
	ETSIDI::Sprite* popup_normas;
	ETSIDI::Sprite* popup_salir;
	bool mostrar_popup = false;
	int boton_activo = 0;
	bool mostrar_popup_normas = false;

	//Lógica de Ataque
	//Temporizadores de ataque (ms)
	int tiempoUltimoAtaqueLocal_ = 0;
	int tiempoUltimoAtaqueInvasor_ = 0;
	static const int COOLDOWN_ATAQUE = 750;
	static const int COOLDOWN_ATAQUE_IA = 1500;

	//Métodos de ataque
	void aplicarAtaque(Personaje* atacante, Personaje* defensor);

	//IA de la maquina en modo 1 jugador: el invasor persigue y ataca al jugador.
	void moverMaquina();

	//Teclas pulsadas
	bool teclaW = false;
	bool teclaS = false;
	bool teclaA = false;
	bool teclaD = false;

	bool teclaArriba = false;
	bool teclaAbajo = false;
	bool teclaIzquierda = false;
	bool teclaDerecha = false;

	// Temporizadores de movimiento independientes (basados en la estadística de velocidad)
	int tiempoUltimoMovimientoLocal_ = 0;
	int tiempoUltimoMovimientoInvasor_ = 0;

	// Bonus de daño por ventaja de terreno (0 = sin ventaja)
	// Se calcula en iniciarCombate y se aplica en aplicarAtaque.
	int bonusDanioLocal_ = 0;
	int bonusDanioInvasor_ = 0;

	ETSIDI::Sprite* cartel_gana_manana_ = nullptr;
	ETSIDI::Sprite* cartel_gana_tarde_ = nullptr;
	bool mostrandoCartel_ = false;
	int  tiempoCartel_ = 0;          // ms en que empezó a mostrarse
	static const int DURACION_CARTEL = 3000; // 3 segundos

	// Temporizadores para combinar la animación estática con la dinámica en la arena
	int tiempo_parada_local_ = 0;
	int tiempo_parada_invasor_ = 0;
	static const int RETARDO_IDLE = 350; // ms de espera antes de volver a estar quieto

};