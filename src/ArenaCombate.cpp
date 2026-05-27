/**
 * @file ArenaCombate.cpp
 * @brief Programación y control de la Arena de combate
 *
 * @details Centraliza todo lo relacionado con el combate en la arena.
 * Tiene el control de donde colocar a los personajes y de como se mueven y de como atacan por la arena dependiendo del tipo de personaje.
 * Además, marca el resultado de quien gana la partida y quien muere durante el combate.
 *
 */

#include "ArenaCombate.h"
#include "MotorGrafico.h"
#include "personaje.h"
#include "tipo_personaje.h"
#include <GL/freeglut.h>
#include "Proyectil.h"
#include "Tablero.h"   
#include "Partida.h"

// Obtenemos las coordenadas de los personajes para poder controlar su movimiento en la arena
static float arenaToX(int columna) {
	return -245.0f + columna * 45.0f+22.5f;
}
static float arenaToY(int fila) {
	return -245.0f + fila * 45.0f+22.5f;
}
//La función coge la información del choque en el tablero y coloca a los personajes en la arena.
// Además si hay un bonus por estar en la casilla, calcula el extra de daño que hará el personaje durante el combate
void ArenaCombate::iniciarCombate(Personaje* local, Personaje* invasor, int modo, FaseCiclo fase)
{
	local_ = local;
	invasor_ = invasor;
	modo_ = modo;

	
	if (modo_ == 1) {
		Turno bandoHumano = (equipo_j1 == 1) ? Turno::TURNO_DE_MANANA
		                                     : Turno::TURNO_DE_TARDE;
		humanoControlaLocal_ = (local_ != nullptr && local_->getTurno() == bandoHumano);
	} else {
		humanoControlaLocal_ = false; 
	}

	if (local_!=nullptr && local_->getTurno() == Turno::TURNO_DE_MANANA) {
		posLocal_ = { 5, 0};   
		posInvasor_ = { 5, 10 }; 

		local_->setMirandoDerecha(true);
		local_->setMirandoIzquierda(false);
		if (invasor_) {
			invasor_->setMirandoDerecha(false);
			invasor_->setMirandoIzquierda(true);
		}
	}
	else {
		posLocal_ = { 5, 10 };   
		posInvasor_ = { 5, 0 }; 

		local_->setMirandoDerecha(false);
		local_->setMirandoIzquierda(true);
		if (invasor_) {
			invasor_->setMirandoDerecha(true);
			invasor_->setMirandoIzquierda(false);
		}
	}

	combateTerminado_ = false;
	resultado_ = ResultadoCombate::Gana_Local;

	mostrar_popup = false;

	int ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempoUltimoAtaqueLocal_ = ahora;
	tiempoUltimoAtaqueInvasor_ = ahora;

	tiempoUltimoMovimiento_ = glutGet(GLUT_ELAPSED_TIME);
	tiempoUltimoMovimientoIA_ = ahora;

	static const int BONUS_TERRENO_PCT = 25; 

	bonusDanioLocal_ = 0;
	bonusDanioInvasor_ = 0;

	auto calcularBonus = [&](Personaje* p) -> int {
		if (p == nullptr || p->getCasillaActual() == nullptr) return 0;
		EstadoCasilla ec = p->getCasillaActual()->getEstado();
		Turno t = p->getTurno();
		bool ventaja = false;
		if (ec == EstadoCasilla::BLANCA_FIJA) {
			ventaja = (t == Turno::TURNO_DE_MANANA);
		}
		else if (ec == EstadoCasilla::AZUL_FIJA) {
			ventaja = (t == Turno::TURNO_DE_TARDE);
		}
		else { // DINAMICA
			bool faseClara = (fase == FaseCiclo::MEDIODIA ||
				fase == FaseCiclo::AMANECER ||
				fase == FaseCiclo::MADRUGADA);
			ventaja = (faseClara && t == Turno::TURNO_DE_MANANA) ||
				(!faseClara && t == Turno::TURNO_DE_TARDE);
		}
		return ventaja ? (p->getArma().getDanio() * BONUS_TERRENO_PCT / 100) : 0;
		};

	bonusDanioLocal_ = calcularBonus(local_);
	bonusDanioInvasor_ = calcularBonus(invasor_);
}
//Para que el personaje se pueda mover, primero hay que comprobar que el destino esta dentro de la arena jugable
//Luego, comprueba que no esta siendo ocupada esa posición para poder moverse. La arena es 11x11.
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
//Para moverse en tablero, el jugador uasará las teclas WASD. Mientras el ataque se usará el espacio.
//En el modo de 2 jugadores, el turno de tarde atacará con el enter.
void ArenaCombate::teclado(unsigned char key)
{
	if (combateTerminado_)
		return;

	Personaje* pManana = (local_->getTurno() == Turno::TURNO_DE_MANANA) ? local_ : invasor_;
	Personaje* pTarde = (local_->getTurno() == Turno::TURNO_DE_TARDE) ? local_ : invasor_;

	Personaje* pHumano = nullptr;
	if (modo_ == 1) {
		Turno bandoHumano = (equipo_j1 == 1) ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;
		pHumano = (bandoHumano == Turno::TURNO_DE_MANANA) ? pManana : pTarde;
	}
	else {
		pHumano = pManana;  
	}
	Personaje* pRival = (pHumano == pManana) ? pTarde : pManana;
	int& cooldownHumano = (pHumano == local_) ? tiempoUltimoAtaqueLocal_
		: tiempoUltimoAtaqueInvasor_;
	int& cooldownTarde = (pTarde == local_) ? tiempoUltimoAtaqueLocal_
		: tiempoUltimoAtaqueInvasor_;

	switch (key)
	{
	case 'w':
		teclaW = true;
		break;
	case 's':
		teclaS = true;
		break;
	case 'a':
		teclaA = true;
		{
			if (pHumano) {
				pHumano->setMirandoDerecha(false);
				pHumano->setMirandoIzquierda(true);
			}
		}
		break;
	case 'd':
		teclaD = true;
		{
			
			if (pHumano) {
				pHumano->setMirandoDerecha(true);
				pHumano->setMirandoIzquierda(false);
			}
		}
		break;

	case 32: {
		int ahora = glutGet(GLUT_ELAPSED_TIME);
		if (ahora - cooldownHumano >= COOLDOWN_ATAQUE) {
			aplicarAtaque(pHumano, pRival);
			cooldownHumano = ahora;
		}
		break;
	}

	case 13: {
		if (modo_ == 2) {
			int ahora = glutGet(GLUT_ELAPSED_TIME);
			if (ahora - cooldownTarde >= COOLDOWN_ATAQUE) {
				aplicarAtaque(pTarde, pManana);
				cooldownTarde = ahora;
			}
		}
		break;
	} 
	}
}
//En el modo de dos jugadores, el equipo de tarde se moverá con las flechas del teclado.
void ArenaCombate::tecladoEspecial(int key)
{
	if (combateTerminado_)
		return;
	if (modo_ != 2)
		return;

	Personaje* pTarde = (local_->getTurno() == Turno::TURNO_DE_TARDE) ? local_ : invasor_;

	switch (key)
	{
	case GLUT_KEY_UP:    teclaArriba = true;
		break;

	case GLUT_KEY_DOWN:  teclaAbajo = true;
		break;

	case GLUT_KEY_LEFT:  
		teclaIzquierda = true;
		if (pTarde) {
			pTarde->setMirandoDerecha(false);
			pTarde->setMirandoIzquierda(true);
		}
		break;

	case GLUT_KEY_RIGHT:
		teclaDerecha = true; 
		if (pTarde) {
			pTarde->setMirandoDerecha(true);
			pTarde->setMirandoIzquierda(false);
		}
		break;
	}
}
//Una vez termina el combate, resetea todas las variables para que cuando se vuelva a la arena se empiece desde el principio
void ArenaCombate::finalizarCombate()
{
	
	for (auto p : proyectiles_) {
		delete p;
	}
	proyectiles_.clear();

	
	teclaW = false;
	teclaS = false;
	teclaA = false;
	teclaD = false;
	teclaArriba = false;
	teclaAbajo = false;
	teclaIzquierda = false;
	teclaDerecha = false;

	local_ = nullptr;
	invasor_ = nullptr;
}
//Una vez termine, determina el resultado de la arena y pasa la información al tablero inicial, además de activar el cartel correspondiente
void ArenaCombate::resolverResultado() {
    combateTerminado_ = true;
    if (local_->estaVivo()) {
        resultado_ = ResultadoCombate::Gana_Local;
        Partida::get_instance().registrarMuerto(invasor_);
    } else {
        resultado_ = ResultadoCombate::Gana_Invasor;
        Partida::get_instance().registrarMuerto(local_);
    }
   
    mostrandoCartel_ = true;
    tiempoCartel_    = glutGet(GLUT_ELAPSED_TIME);
}
//Devuelve que ha terminado el combate
bool ArenaCombate::combateTerminado() const
{
	return combateTerminado_;
}
//Coge el resultado de la arena
ResultadoCombate ArenaCombate::getResultado() const
{
	return resultado_;
}
//El constructor de la clase, se encarga de guardar las imágenes y las posiciones de los personajes en la arena.
ArenaCombate::ArenaCombate() {
	fondo_arena = new ETSIDI::Sprite("assets/menu_imagenes/ArenaCombate.png", 0, 0, 800, 800);
	abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
	popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
	posLocal_ = { 5, 0 };
	posInvasor_ = { 5, 11 };

	cartel_gana_manana_ = new ETSIDI::Sprite("assets/menu_imagenes/cartel_gana_manana_.png", 0, 0, 400, 400);
	cartel_gana_tarde_ = new ETSIDI::Sprite("assets/menu_imagenes/cartel_gana_tarde_.png", 0, 0, 400, 400);
}
//Función para pintar la arena de combate en la pantalla
void ArenaCombate::dibuja() {
	fondo_arena->draw();
}
//Función para pintar el mensaje de abandonar partida
void ArenaCombate::dibujaPopup()
{
	abandonar_partida->draw();
	if (mostrar_popup) popup_salir->draw();
}
//Actualiza los mensajes en la pantalla
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
//Detecta el click del ordenador, además de iniciar y parar la música
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
//Controlamos que se aplique el ataque correctamente cuando el proyectil choca con el jugador rival
void ArenaCombate::aplicarAtaque(Personaje* atacante, Personaje* defensor) {
	if (atacante == nullptr || defensor == nullptr) return;
	if (combateTerminado_) return;

	bool esLocal = (atacante == local_);
	float ox = arenaToX(esLocal ? posLocal_.columna : posInvasor_.columna);
	float oy = arenaToY(esLocal ? posLocal_.fila : posInvasor_.fila);
	float dx = arenaToX(esLocal ? posInvasor_.columna : posLocal_.columna);
	float dy = arenaToY(esLocal ? posInvasor_.fila : posLocal_.fila);
	float velocidad = atacante->getVelocidadProyectil();
	int   dano = atacante->getArma().getDanio() +
		(esLocal ? bonusDanioLocal_ : bonusDanioInvasor_);

	proyectiles_.push_back(new Proyectil(ox, oy, dx, dy,
		dano,
		velocidad,
		atacante->getNombreProyectil(),
		esLocal, atacante->getArma().getAlcance()));
}
//Se va actualizando el combate en tiempo real, controlando el movimiento de los personajes, los ataques y la vida de cada personaje.
//Además de controlar el movimiento y la colisión de los choques
void ArenaCombate::actualizar() {
	
	if (mostrandoCartel_) {
		if (glutGet(GLUT_ELAPSED_TIME) - tiempoCartel_ >= DURACION_CARTEL)
			mostrandoCartel_ = false;
		return;
	}
	if (combateTerminado_) return;

	
	Personaje* pManana = (local_->getTurno() == Turno::TURNO_DE_MANANA) ? local_ : invasor_;
	Personaje* pTarde = (local_->getTurno() == Turno::TURNO_DE_TARDE) ? local_ : invasor_;

	
	if (modo_ == 2) {
		
		if (pManana != nullptr) pManana->setEnMovimiento(teclaW || teclaS || teclaA || teclaD);
		if (pTarde != nullptr)  pTarde->setEnMovimiento(teclaArriba || teclaAbajo || teclaIzquierda || teclaDerecha);
	}
	else {
		
		Turno bandoHumano = (equipo_j1 == 1) ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;
		Personaje* pHumano = (bandoHumano == Turno::TURNO_DE_MANANA) ? pManana : pTarde;

		if (pHumano != nullptr) pHumano->setEnMovimiento(teclaW || teclaS || teclaA || teclaD);
	}

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	
	for (auto p : proyectiles_)
		p->actualizar();

	
	float xLocal = arenaToX(posLocal_.columna);
	float yLocal = arenaToY(posLocal_.fila);
	float xInvasor = arenaToX(posInvasor_.columna);
	float yInvasor = arenaToY(posInvasor_.fila);

	int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol = abs(posLocal_.columna - posInvasor_.columna);
	int distancia = max(distFila, distCol);

	for (auto p : proyectiles_) {
		
		if (p->esDeLocal() && p->ColisionaCon(xInvasor, yInvasor, 60.0f)) {
			p->marcarLlegado();
			if (distancia <= local_->getArma().getAlcance()) {
				if (invasor_ != nullptr && invasor_->estaVivo()) {
					if (invasor_->getEscudo()) {
						invasor_->decrementarEscudo();
					}
					else {
						invasor_->recibirDano(p->getDano());
						if (!invasor_->estaVivo()) resolverResultado();
					}
				}
			}
		}
		
		else if (!p->esDeLocal() && p->ColisionaCon(xLocal, yLocal, 60.0f)) {
			p->marcarLlegado();
			if (distancia <= invasor_->getArma().getAlcance()) {
				if (local_ != nullptr && local_->estaVivo()) {
					if (local_->getEscudo()) {
						local_->decrementarEscudo();
					}
					else {
						local_->recibirDano(p->getDano());
						if (!local_->estaVivo()) resolverResultado();
					}
				}
			}
		}
	}

	
	for (auto it = proyectiles_.begin(); it != proyectiles_.end();) {
		if ((*it)->haLlegado()) { delete* it; it = proyectiles_.erase(it); }
		else { ++it; }
	}

	
	if (ahora - tiempoUltimoMovimiento_ >= INTERVALO_MOVIMIENTO) {

		PosArena& posManana = (pManana == local_) ? posLocal_ : posInvasor_;
		PosArena& posTarde = (pTarde == local_) ? posLocal_ : posInvasor_;

		if (modo_ == 2) {
			
			if (teclaW && moverEnArena(posManana, 1, 0)) pManana->incrementarPasos();
			if (teclaS && moverEnArena(posManana, -1, 0)) pManana->incrementarPasos();
			if (teclaA && moverEnArena(posManana, 0, -1)) pManana->incrementarPasos();
			if (teclaD && moverEnArena(posManana, 0, 1)) pManana->incrementarPasos();

			
			if (teclaArriba && moverEnArena(posTarde, 1, 0)) pTarde->incrementarPasos();
			if (teclaAbajo && moverEnArena(posTarde, -1, 0)) pTarde->incrementarPasos();
			if (teclaIzquierda && moverEnArena(posTarde, 0, -1)) pTarde->incrementarPasos();
			if (teclaDerecha && moverEnArena(posTarde, 0, 1)) pTarde->incrementarPasos();
		}
		else {
			
			Turno bandoHumano = (equipo_j1 == 1) ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;
			Personaje* pHumano = (bandoHumano == Turno::TURNO_DE_MANANA) ? pManana : pTarde;
			PosArena& posHumano = (pHumano == local_) ? posLocal_ : posInvasor_;

			if (teclaW && moverEnArena(posHumano, 1, 0)) pHumano->incrementarPasos();
			if (teclaS && moverEnArena(posHumano, -1, 0)) pHumano->incrementarPasos();
			if (teclaA && moverEnArena(posHumano, 0, -1)) pHumano->incrementarPasos();
			if (teclaD && moverEnArena(posHumano, 0, 1)) pHumano->incrementarPasos();
		}
		tiempoUltimoMovimiento_ = ahora;
	}
	if (modo_ == 1) moverMaquina();
}
//Controlamos el movimiento y el ataque de la máquina en el modo de 1 jugador en la arena.
//Busca estar siempre a tiro del humano para poder disparar.
//Controla el turno que no escoge el jugador.
void ArenaCombate::moverMaquina() {
	if (combateTerminado_) return;
	if (invasor_ == nullptr || local_ == nullptr) return;

	Turno bandoHumano = (equipo_j1 == 1) ? Turno::TURNO_DE_MANANA : Turno::TURNO_DE_TARDE;
	Personaje* piezaHumano = (local_->getTurno() == bandoHumano) ? local_ : invasor_;
	Personaje* piezaIA = (piezaHumano == local_) ? invasor_ : local_;
	PosArena& posHumano = (piezaHumano == local_) ? posLocal_ : posInvasor_;
	PosArena& posIA = (piezaIA == local_) ? posLocal_ : posInvasor_;
	int& tiempoAtaqueIA = (piezaIA == local_) ? tiempoUltimoAtaqueLocal_
		: tiempoUltimoAtaqueInvasor_;

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	int distFila = abs(posHumano.fila - posIA.fila);
	int distCol  = abs(posHumano.columna - posIA.columna);
	int distancia = max(distFila, distCol);
	int alcance = piezaIA->getArma().getAlcance();

	
	if (distancia <= alcance) {
		piezaIA->setEnMovimiento(false); 
		if (ahora - tiempoAtaqueIA >= COOLDOWN_ATAQUE_IA) {
			aplicarAtaque(piezaIA, piezaHumano);
			tiempoAtaqueIA = ahora;
		}
		return;   
	}

	
	if (ahora - tiempoUltimoMovimientoIA_ < INTERVALO_MOVIMIENTO_IA) return;

	int df = 0, dc = 0;
	if (posIA.fila < posHumano.fila) df = 1;
	else if (posIA.fila > posHumano.fila) df = -1;

	if (posIA.columna < posHumano.columna) {
		dc = 1;
		piezaIA->setMirandoDerecha(true);
		piezaIA->setMirandoIzquierda(false);
	}
	else if (posIA.columna > posHumano.columna) {
		dc = -1;
		piezaIA->setMirandoDerecha(false);
		piezaIA->setMirandoIzquierda(true);
	}

	
	bool movido = false;
	if (moverEnArena(posIA, df, dc)) {
		movido = true;
	}
	else if (df != 0 && moverEnArena(posIA, df, 0)) {
		movido = true;
	}
	else if (dc != 0 && moverEnArena(posIA, 0, dc)) {
		movido = true;
	}

	if (movido) {
		piezaIA->incrementarPasos();
		piezaIA->setEnMovimiento(true);
	}
	tiempoUltimoMovimientoIA_ = ahora;
}
//Podemos hacer que se pueda mover y atacar a la vez mediante la detección de varios botones a la vez.
void ArenaCombate::teclaLevantada(unsigned char key) {
	switch (key) {
	case 'w': teclaW = false; break;
	case 's': teclaS = false; break;
	case 'a': teclaA = false; break;
	case 'd': teclaD = false; break;
	}
}
//Igual que el anterior.
void ArenaCombate::teclaEspecialLevantada(int key) {
	switch (key)
	{
	case GLUT_KEY_UP:
		teclaArriba = false;
		break;
	case GLUT_KEY_DOWN:
		teclaAbajo = false;
		break;
	case GLUT_KEY_LEFT:
		teclaIzquierda = false;
		break;
	case GLUT_KEY_RIGHT:
		teclaDerecha = false;
		break;
	}
}
//Función para pintar los proyectiles de cada personaje.
void ArenaCombate::dibujarProyectiles() {
	for (auto p : proyectiles_)
		p->dibujar();
}

//Una vez obtenido el resultado, dibujamos el cartel de que turno ha ganado si mañana o tarde.
void ArenaCombate::dibujaCartel() {
	if (!mostrandoCartel_) return;

	
	Personaje* ganador = (resultado_ == ResultadoCombate::Gana_Local) ? local_ : invasor_;

	if (ganador != nullptr && ganador->getTurno() == Turno::TURNO_DE_TARDE)
		cartel_gana_tarde_->draw();
	else
		cartel_gana_manana_->draw();
}