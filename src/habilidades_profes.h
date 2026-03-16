#pragma once

enum class habilidades {
	TELEPORT,
	REVIVIR,
	INMOVILIZA,
};

class Menu_habilidades {
public:
	Menu_habilidades() {}

	void Usar_habilidad(habilidades a){
		switch (a) {
		case habilidades::TELEPORT: usar_tp(); break;
		case habilidades::REVIVIR: usar_revivir(); break;
		case habilidades::INMOVILIZA: usar_inmoviliza(); break;

		}
	}
private:
	void usar_tp();
	void usar_revivir();
	void usar_inmoviliza();
};

