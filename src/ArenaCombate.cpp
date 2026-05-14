#include "ArenaCombate.h"
#include "MotorGrafico.h"
#include <GL/freeglut.h>

void ArenaCombate::iniciarCombate(Personaje* local, Personaje* invasor, int modo)
{
	local_ = local;
	invasor_ = invasor;
	modo_ = modo;

	posLocal_ = { 5,2 };
	posInvasor_ = { 5,8 };

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
		moverEnArena(posLocal_, 1, 0);
		break;
	case 's':
		moverEnArena(posLocal_, -1, 0);
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
		moverEnArena(posInvasor_, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		moverEnArena(posInvasor_, -1, 0);
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

ArenaCombate::ArenaCombate() {
	fondo_arena = new ETSIDI::Sprite("assets/menu_imagenes/ArenaCombate1.png", 0, 0, 600, 600);
	abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
	mostrar_popup = false;
	boton_activo = 0;
	posLocal_ = { 5, 2 };
	posInvasor_ = { 5, 8 };
}

void ArenaCombate::dibuja() {
	fondo_arena->draw();
	abandonar_partida->draw();
	if (mostrar_popup) popup_salir->draw();
}

void ArenaCombate::update(int x, int y) {
	int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
	int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
	int tam = min(ventana_w, ventana_h);
	int offsetX = (ventana_w - tam) / 2;
	int offsetY = (ventana_h - tam) / 2;
	float cx = ((x - offsetX) / (float)tam) * 800 - 400;
	float cy = 400 - ((y - offsetY) / (float)tam) * 800;

	if (!mostrar_popup) {
		if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274) boton_activo = 1;
		else boton_activo = 0;
	}
	else {
		if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) boton_activo = 2;
		else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4) boton_activo = 3;
		else boton_activo = 0;
	}
}

Modos_juego ArenaCombate::click(int x, int y) {
	int ventana_w = glutGet(GLUT_WINDOW_WIDTH);
	int ventana_h = glutGet(GLUT_WINDOW_HEIGHT);
	int tam = min(ventana_w, ventana_h);
	int offsetX = (ventana_w - tam) / 2;
	int offsetY = (ventana_h - tam) / 2;
	float cx = ((x - offsetX) / (float)tam) * 800 - 400;
	float cy = 400 - ((y - offsetY) / (float)tam) * 800;

	ETSIDI::play("assets/sonidos/click.mp3");

	int col = (int)((cx - MotorGrafico::INICIO_X) / MotorGrafico::TAM);
	int fil = (int)((cy - MotorGrafico::INICIO_Y) / MotorGrafico::TAM);

	if (mostrar_popup) {
		if (cx >= -153 && cx <= -57 && cy >= -43 && cy <= -5) {
			ETSIDI::stopMusica();
			ETSIDI::playMusica("assets/sonidos/menu.mp3", true);
			return Modos_juego::MENU;
		}
		else if (cx >= 15 && cx <= 108 && cy >= -46 && cy <= -4) mostrar_popup = false;
		return Modos_juego::Arena_Combate;
	}

	if (cx >= 304 && cx <= 342 && cy >= -354 && cy <= -274) {
		mostrar_popup = true;
		return Modos_juego::Arena_Combate;
	}
} 
