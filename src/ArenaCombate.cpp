#include "ArenaCombate.h"
#include "MotorGrafico.h"
#include "personaje.h"
#include "tipo_personaje.h"
#include <GL/freeglut.h>
#include "Proyectil.h"
#include "Tablero.h"   // FaseCiclo + EstadoCasilla (no hay ciclo: .cpp incluye .h, no al revés)
#include "Partida.h"

// Convierte posición en cuadrícula a coordenadas OpenGL
static float arenaToX(int columna) {
	return -245.0f + columna * 45.0f+22.5f;
}
static float arenaToY(int fila) {
	return -245.0f + fila * 45.0f+22.5f;
}

void ArenaCombate::iniciarCombate(Personaje* local, Personaje* invasor, int modo, FaseCiclo fase)
{
	local_ = local;
	invasor_ = invasor;
	modo_ = modo;

	posLocal_ = { 5,2 };
	posInvasor_ = { 5,8 };

	// Inicializar en la arena a cada turno siempre en su respectivo lado
	if (local_->getTurno() == Turno::TURNO_DE_MANANA) {
		posLocal_ = { 5, 2 };   
		posInvasor_ = { 5, 8 }; 

		local_->setMirandoDerecha(true);
		local_->setMirandoIzquierda(false);
		if (invasor_) {
			invasor_->setMirandoDerecha(false);
			invasor_->setMirandoIzquierda(true);
		}
	}
	else {
		posLocal_ = { 5, 8 };   
		posInvasor_ = { 5, 2 }; 

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

	//Ventaja de terreno: bonus de daño
	static const int BONUS_TERRENO_PCT = 25; // % de daño extra

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
		teclaW = true;
		break;
	case 's':
		teclaS = true;
		break;
	case 'a':
		teclaA = true;
		if (local_) {
			local_->setMirandoDerecha(false);
			local_->setMirandoIzquierda(true);
		}
		break;
	case 'd':
		teclaD = true;
		if (local_) {
			local_->setMirandoDerecha(true);
			local_->setMirandoIzquierda(false);
		}
		break;

		// Ataque jugador 1 (espacio) — funciona en modo 1 y 2
	case 32: {
		int ahora = glutGet(GLUT_ELAPSED_TIME);
		if (ahora - tiempoUltimoAtaqueLocal_ >= COOLDOWN_ATAQUE) {
			aplicarAtaque(local_, invasor_);
			tiempoUltimoAtaqueLocal_ = ahora;
		}
		break;
	}

		// Ataque jugador 2 (Enter) — solo modo 2 jugadores
	case 13: {
		if (modo_ == 2) {
			int ahora = glutGet(GLUT_ELAPSED_TIME);
			if (ahora - tiempoUltimoAtaqueInvasor_ >= COOLDOWN_ATAQUE) {
				aplicarAtaque(invasor_, local_);
				tiempoUltimoAtaqueInvasor_ = ahora;
			}
		}
		break;
	} 
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
	case GLUT_KEY_UP:    teclaArriba = true;
		break;

	case GLUT_KEY_DOWN:  teclaAbajo = true;
		break;

	case GLUT_KEY_LEFT:  
		teclaIzquierda = true;
		if (invasor_) {
			invasor_->setMirandoDerecha(false);
			invasor_->setMirandoIzquierda(true);
		}
		break;

	case GLUT_KEY_RIGHT:
		teclaDerecha = true; 
		if (invasor_) {
			invasor_->setMirandoDerecha(true);
			invasor_->setMirandoIzquierda(false);
		}
		break;
	}
}

void ArenaCombate::finalizarCombate()
{
	// Limpiar proyectiles pendientes
	for (auto p : proyectiles_) {
		delete p;
	}
	proyectiles_.clear();

	// Resetear teclas
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

void ArenaCombate::resolverResultado() {
    combateTerminado_ = true;
    if (local_->estaVivo()) {
        resultado_ = ResultadoCombate::Gana_Local;
        Partida::get_instance().registrarMuerto(invasor_);
    } else {
        resultado_ = ResultadoCombate::Gana_Invasor;
        Partida::get_instance().registrarMuerto(local_);
    }
    //activa cartel
    mostrandoCartel_ = true;
    tiempoCartel_    = glutGet(GLUT_ELAPSED_TIME);
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
	fondo_arena = new ETSIDI::Sprite("assets/menu_imagenes/GulagDefinitivo.png", 0, 0, 600, 600);
	abandonar_partida = new ETSIDI::Sprite("assets/menu_imagenes/boton_abandonar.png", 0, 0, 800, 800);
	popup_salir = new ETSIDI::Sprite("assets/menu_imagenes/popup_salir.png", 0, 0, 800, 800);
	posLocal_ = { 5, 2 };
	posInvasor_ = { 5, 8 };

	cartel_gana_manana_ = new ETSIDI::Sprite("assets/menu_imagenes/cartel_gana_manana_.png", 0, 0, 400, 400);
	cartel_gana_tarde_ = new ETSIDI::Sprite("assets/menu_imagenes/cartel_gana_tarde_.png", 0, 0, 400, 400);
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
	if (atacante == nullptr || defensor == nullptr) return;
	if (combateTerminado_) return;

	/*int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol = abs(posLocal_.columna - posInvasor_.columna);
	int distancia = max(distFila, distCol);

	int alcance = atacante->getArma().getAlcance();
	if (distancia > alcance) return;*/

	bool esLocal = (atacante == local_);
	float ox = arenaToX(esLocal ? posLocal_.columna : posInvasor_.columna);
	float oy = arenaToY(esLocal ? posLocal_.fila : posInvasor_.fila);
	float dx = arenaToX(esLocal ? posInvasor_.columna : posLocal_.columna);
	float dy = arenaToY(esLocal ? posInvasor_.fila : posLocal_.fila);
	float velocidad = atacante->getVelocidadProyectil();

	// Daño base + bonus de terreno según quién ataca
	int dano = atacante->getArma().getDanio() + (esLocal ? bonusDanioLocal_ : bonusDanioInvasor_);

	proyectiles_.push_back(new Proyectil(ox, oy, dx, dy,
		dano,
		velocidad,
		atacante->getNombreProyectil(),
		esLocal));
}

void ArenaCombate::actualizar() {
	// 1. Lógica de pausa
	if (mostrandoCartel_) {
		if (glutGet(GLUT_ELAPSED_TIME) - tiempoCartel_ >= DURACION_CARTEL)
			mostrandoCartel_ = false;
		return;
	}
	if (combateTerminado_) return;

	// 2. Sincronización de Animaciones (Estados)
	if (local_ != nullptr) {
		bool moviendo_local = (teclaW || teclaS || teclaA || teclaD);
		local_->setEnMovimiento(moviendo_local);
	}
	if (invasor_ != nullptr) {
		if (modo_ == 2) {
			bool moviendo_invasor = (teclaArriba || teclaAbajo || teclaIzquierda || teclaDerecha);
			invasor_->setEnMovimiento(moviendo_invasor);
		}
	}

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// 3. Movimiento de Proyectiles (Siempre se actualizan)
	for (auto p : proyectiles_)
		p->actualizar();

	// 4. Colisiones (Aquí está la magia)
	float xLocal = arenaToX(posLocal_.columna);
	float yLocal = arenaToY(posLocal_.fila);
	float xInvasor = arenaToX(posInvasor_.columna);
	float yInvasor = arenaToY(posInvasor_.fila);

	// Calculamos distancia una vez para no repetir código
	int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol = abs(posLocal_.columna - posInvasor_.columna);
	int distancia = max(distFila, distCol);

	for (auto p : proyectiles_) {
		// Impacto LOCAL -> INVASOR
		if (p->esDeLocal() && p->ColisionaCon(xInvasor, yInvasor, 60.0f)) {
			p->marcarLlegado();
			if (distancia <= local_->getArma().getAlcance()) {
				if (invasor_ != nullptr && invasor_->estaVivo()) {
					invasor_->recibirDano(p->getDano());
					if (!invasor_->estaVivo()) resolverResultado();
				}
			}
		}
		// Impacto INVASOR -> LOCAL
		else if (!p->esDeLocal() && p->ColisionaCon(xLocal, yLocal, 60.0f)) {
			p->marcarLlegado();
			if (distancia <= invasor_->getArma().getAlcance()) {
				if (local_ != nullptr && local_->estaVivo()) {
					local_->recibirDano(p->getDano());
					if (!local_->estaVivo()) resolverResultado();
				}
			}
		}
	}

	// 5. Limpieza de proyectiles
	for (auto it = proyectiles_.begin(); it != proyectiles_.end();) {
		if ((*it)->haLlegado()) { delete* it; it = proyectiles_.erase(it); }
		else { ++it; }
	}

	// 6. Movimiento de personajes (con cooldown)
	if (ahora - tiempoUltimoMovimiento_ >= INTERVALO_MOVIMIENTO) {
		if (teclaW && moverEnArena(posLocal_, 1, 0))  local_->incrementarPasos();
		if (teclaS && moverEnArena(posLocal_, -1, 0)) local_->incrementarPasos();
		if (teclaA && moverEnArena(posLocal_, 0, -1)) local_->incrementarPasos();
		if (teclaD && moverEnArena(posLocal_, 0, 1))  local_->incrementarPasos();

		if (modo_ == 2) {
			if (teclaArriba && moverEnArena(posInvasor_, 1, 0))    invasor_->incrementarPasos();
			if (teclaAbajo && moverEnArena(posInvasor_, -1, 0))    invasor_->incrementarPasos();
			if (teclaIzquierda && moverEnArena(posInvasor_, 0, -1)) invasor_->incrementarPasos();
			if (teclaDerecha && moverEnArena(posInvasor_, 0, 1))   invasor_->incrementarPasos();
		}
		tiempoUltimoMovimiento_ = ahora;
	}
}

void ArenaCombate::moverMaquina() {
	// La maquina (invasor_) persigue al jugador (local_) y le ataca cuando
	// lo tiene a tiro. Solo se llama en modo 1 jugador: no afecta al modo 2.
	if (combateTerminado_) return;
	if (invasor_ == nullptr || local_ == nullptr) return;

	int ahora = glutGet(GLUT_ELAPSED_TIME);

	int distFila = abs(posLocal_.fila - posInvasor_.fila);
	int distCol = abs(posLocal_.columna - posInvasor_.columna);
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

		
		if (posInvasor_.columna < posLocal_.columna) {
			dc = 1;
			if (invasor_) {
				invasor_->setMirandoDerecha(true);
				invasor_->setMirandoIzquierda(false);
			}
		}
		else if (posInvasor_.columna > posLocal_.columna) {
			dc = -1;
			if (invasor_) {
				invasor_->setMirandoDerecha(false);
				invasor_->setMirandoIzquierda(true);
			}
		}

		
		
			if (!moverEnArena(posInvasor_, df, dc)) {
				if (df != 0) {
					if (moverEnArena(posInvasor_, df, 0)) invasor_->incrementarPasos();
				}
				else if (dc != 0) {
					if (moverEnArena(posInvasor_, 0, dc)) invasor_->incrementarPasos();
				}
			}
			else {
				// Si logró moverse en diagonal o directamente
				invasor_->incrementarPasos();
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

void ArenaCombate::dibujarProyectiles() {
	for (auto p : proyectiles_)
		p->dibujar();
}


void ArenaCombate::dibujaCartel() {
	if (!mostrandoCartel_) return;

	// Determinamos quién ganó y miramos su turno
	Personaje* ganador = (resultado_ == ResultadoCombate::Gana_Local) ? local_ : invasor_;

	if (ganador != nullptr && ganador->getTurno() == Turno::TURNO_DE_TARDE)
		cartel_gana_tarde_->draw();
	else
		cartel_gana_manana_->draw();
}