#pragma once
#include "EscenaBase.h"

class EscenaPuntuaciones: public EscenaBase
{
private:
	sf::Texture* _TexturaFondo;
	sf::Sprite* _SpriteFondo;
	sf::RectangleShape* _BordeVentana;

	sf::Mouse _m;
	sf::CircleShape* _SeguimientoMouse;

	int* CantidadRegistros;

	sf::Clock delay;

	// TEXTO
	sf::Font* _FuenteTexto;
	sf::Text* _ArrayTitulos;
	// 0 TITULO PRINCIPAL
	// 1 TITULO NOMBRE
	// 2 TITULO PUNTAJE

	sf::Text* _ArrayNombres;
	sf::Text* _ArrayPuntuaciones;
	sf::Text* _TextoVolver;

	//void liberarMemoria();

public:
	EscenaPuntuaciones();
	void updatee_es(float lapso, sf::RenderWindow& _w);
	void draw_es(sf::RenderWindow& _w);
	~EscenaPuntuaciones();
};

