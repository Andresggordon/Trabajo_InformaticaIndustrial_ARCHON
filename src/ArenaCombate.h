#pragma once
#include "personaje.h"
#include "Modos_juego.h"

//El personaje LOCAL es aquel que se encuentra en la casilla mientras el INVASOR es el personaje que se desplaza a la casilla

enum class ResultadoCombate //Declaramos los posibles resultados que se producen en el combate
{
	Gana_Local, Gana_Invasor
};

class ArenaCombate
{
public:
	ArenaCombate();
	void iniciarCombate(Personaje* local, Personaje* invasor, int modo); //Iniciar y finalizar el combate
	void finalizarCombate();
	bool combateTerminado() const; //Confirmar que el combate acabo y pasar el resultado del combate
	ResultadoCombate getResultado() const;

	void teclado(unsigned char key);
	void tecladoEspecial(int key);

private:
	Personaje* local_ = nullptr; //Declaración de los personajes
	Personaje* invasor_ = nullptr;
	int modo_ = 1;

	static const int Filas_Arena = 11;
	static const int Columnas_Arena = 11;

	struct PosArena
	{
		int fila, columna;
	};
	PosArena posLocal_;
	PosArena posInvasor_;

	bool combateTerminado_ = false; //Estado del combate 
	ResultadoCombate resultado_ = ResultadoCombate::Gana_Local;

	void resolverResultado(); //Método para trabajar intero
	bool moverEnArena(PosArena& pos, int df, int dc);
};