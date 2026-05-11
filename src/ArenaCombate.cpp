#include "ArenaCombate.h"
#include <GL/freeglut.h>

ArenaCombate::ArenaCombate()
{
	posLocal_ = { 5,1 };
	posInvasor_ = { 5,9 };
}

void ArenaCombate::iniciarCombate(Personaje* local, Personaje* invasor, int modo)
{
	local_ = local;
	invasor_ = invasor;
	modo_ = modo;

	posLocal_ = { 5,1 };
	posInvasor_ = { 5,9 };

	combateTerminado_ = false;
	resultado_ = ResultadoCombate::Gana_Local;
}

bool ArenaCombate::moverEnArena(PosArena& pos, int df, int dc)
{
	int nuevaFila = pos.fila + df;
	int nuevaColumna = pos.columna + dc;

	if (nuevaFila < 0 || nuevaFila >= Filas_Arena)
		return false;
	if (nuevaColumna < 0 || nuevaColumna >= Columnas_Arena)
		return false;

	if (nuevaFila == posLocal_.fila && nuevaColumna == posLocal_.columna)
		return false;
	if (nuevaFila == posInvasor_.fila && nuevaColumna == posInvasor_.columna)
		return false;

	pos.fila = nuevaFila;
	pos.columna = nuevaColumna;
	return true;
}
//Movimiento del Jugador 1 en el modo de 1vs1 y en el modo contra la máquina
void ArenaCombate::teclado(unsigned char key)
{
	if (combateTerminado_)
		return;

	switch (key)
	{
	case 'w':
		moverEnArena(posLocal_, -1, 0);
		break;
	case 's':
		moverEnArena(posLocal_, 1, 0);
		break;
	case 'a':
		moverEnArena(posLocal_, 0, -1);
		break;
	case 'd':
		moverEnArena(posLocal_, 0, 1);
		break;
	}
}
//Movimiento del jugador 2 en el modo 1vs1
void ArenaCombate::tecladoEspecial(int key)
{
	if (combateTerminado_)
		return;
	if (modo_ != 2)
		return;

	switch (key)
	{
	case GLUT_KEY_UP:
		moverEnArena(posInvasor_, -1, 0);
		break;
	case GLUT_KEY_DOWN:
		moverEnArena(posInvasor_, 1, 0);
		break;
	case GLUT_KEY_LEFT:
		moverEnArena(posInvasor_, 0, -1);
		break;
	case GLUT_KEY_RIGHT:
		moverEnArena(posInvasor_, 0, 1);
		break;
	}
}

void ArenaCombate::finalizarCombate()
{
	local_ = nullptr;
	invasor_ = nullptr;
}

void ArenaCombate::resolverResultado()
{
	combateTerminado_ = true;
	if (local_->estaVivo())
	{
		resultado_ = ResultadoCombate::Gana_Local;
	}
	else
	{
		resultado_ = ResultadoCombate::Gana_Invasor;
	}
}

bool ArenaCombate::combateTerminado() const
{
	return combateTerminado_;
}

ResultadoCombate ArenaCombate::getResultado() const
{
	return resultado_;
}