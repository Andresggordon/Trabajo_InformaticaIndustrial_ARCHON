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
	ArenaCombate();
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


	std::vector<Proyectil*> proyectiles_;

	static const int Filas_Arena = 11;
	static const int Columnas_Arena = 11;

	PosArena posLocal_;
	PosArena posInvasor_;

	bool combateTerminado_ = false; //Estado del combate 
	ResultadoCombate resultado_ = ResultadoCombate::Gana_Local;

	void resolverResultado(); //Método para trabajar intero
	bool moverEnArena(PosArena& pos, int df, int dc);

	ETSIDI::Sprite* fondo_arena = nullptr;
	ETSIDI::Sprite* abandonar_partida;
	ETSIDI::Sprite* popup_salir;
	bool mostrar_popup = false;
	int boton_activo = 0;

	//Lógica de Ataque
	//Temporizadores de ataque (ms)
	int tiempoUltimoAtaqueLocal_ = 0;
	int tiempoUltimoAtaqueInvasor_ = 0;
	static const int COOLDOWN_ATAQUE = 750;

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

	int tiempoUltimoMovimiento_ = 0;
	static const int INTERVALO_MOVIMIENTO = 250;

	//Cadencias propias de la IA de la arena (solo modo 1 jugador)
	int tiempoUltimoMovimientoIA_ = 0;
	static const int INTERVALO_MOVIMIENTO_IA = 150;
	static const int INTERVALO_ATAQUE_IA = 600;

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


	~ArenaCombate();
};