#include "ArenaCombate.h"
#include "MotorGrafico.h"
#include "personaje.h"
#include "tipo_personaje.h"
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

	mostrar_popup = false;

	int ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempoUltimoAtaqueLocal_ = ahora;
	tiempoUltimoAtaqueInvasor_ = ahora;

	tiempoUltimoMovimiento_ = glutGet(GLUT_ELAPSED_TIME);
	tiempoUltimoMovimientoIA_ = ahora;
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
		teclaW=true;
		break;
	case 's':
		teclaS=true;
		break;
	case 'a':
		teclaA=true;
		break;
	case 'd':
		teclaD=true;
		break;

		// Ataque jugador 1 (espacio) — funciona en modo 1 y 2
	case 32:
		aplicarAtaque(local_, invasor_);
		break;

		// Ataque jugador 2 (Enter) — solo modo 2 jugadores
	case 13:
		if (modo_ == 2)
			aplicarAtaque(invasor_, local_);
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
	popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
	posLocal_ = { 5, 2 };
	posInvasor_ = { 5, 8 };
}

void ArenaCombate::dibuja() {
	fondo_arena->draw();
}

void ArenaCombate::dibujaPopup()
{
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
	return Modos_juego::Arena_Combate;
} 

void ArenaCombate::aplicarAtaque(Personaje* atacante, Personaje* defensor) {
	// Calcular distancia entre los dos personajes en la cuadrícula
	int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol = abs(posLocal_.columna - posInvasor_.columna);
	int distancia = max(distFila, distCol);

	// Comprobar que el atacante tiene alcance suficiente
	int alcance = atacante->getArma().getAlcance();
	if (distancia > alcance) return;  // fuera de rango

	// Aplicar daño
	defensor->recibirDano(atacante->getArma().getDanio());

	// Comprobar si murió
	if (!defensor->estaVivo())
		resolverResultado();
}

void ArenaCombate::actualizar() {
	if (combateTerminado_) return;

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	if (ahora - tiempoUltimoMovimiento_ >= INTERVALO_MOVIMIENTO) {
		if (teclaW) moverEnArena(posLocal_, 1, 0);
		if (teclaS) moverEnArena(posLocal_, -1, 0);
		if (teclaA) moverEnArena(posLocal_, 0, -1);
		if (teclaD) moverEnArena(posLocal_, 0, 1);
		tiempoUltimoMovimiento_ = ahora;
	}

	// En modo 1 jugador la maquina controla al invasor_.
	if (modo_ == 1) moverMaquina();
}

void ArenaCombate::moverMaquina() {
	// La maquina (invasor_) persigue al jugador (local_) y le ataca cuando
	// lo tiene a tiro. Solo se llama en modo 1 jugador: no afecta al modo 2.
	if (combateTerminado_) return;
	if (invasor_ == nullptr || local_ == nullptr) return;

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol  = abs(posLocal_.columna - posInvasor_.columna);
	int distancia = max(distFila, distCol);
	int alcance = invasor_->getArma().getAlcance();

	// 1. Si esta a tiro, atacar con su propia cadencia.
	if (distancia <= alcance) {
		if (ahora - tiempoUltimoAtaqueInvasor_ >= INTERVALO_ATAQUE_IA) {
			aplicarAtaque(invasor_, local_);
			tiempoUltimoAtaqueInvasor_ = ahora;
		}
		return;
	}

	// 2. Si esta lejos, un paso hacia el jugador con su propia cadencia.
	if (ahora - tiempoUltimoMovimientoIA_ >= INTERVALO_MOVIMIENTO_IA) {
		int df = 0, dc = 0;
		if (posInvasor_.fila < posLocal_.fila) df = 1;
		else if (posInvasor_.fila > posLocal_.fila) df = -1;
		if (posInvasor_.columna < posLocal_.columna) dc = 1;
		else if (posInvasor_.columna > posLocal_.columna) dc = -1;

		// Intentar la diagonal; si esa celda esta bloqueada, probar por ejes.
		if (!moverEnArena(posInvasor_, df, dc)) {
			if (df != 0) moverEnArena(posInvasor_, df, 0);
			else if (dc != 0) moverEnArena(posInvasor_, 0, dc);
		}
		tiempoUltimoMovimientoIA_ = ahora;
	}
}

void ArenaCombate::teclaLevantada(unsigned char key) {
	switch (key) {
	case 'w': teclaW = false; break;
	case 's': teclaS = false; break;
	case 'a': teclaA = false; break;
	case 'd': teclaD = false; break;
	}
}
