#pragma once
#include <SFML/Graphics.hpp>
#include "EscenaBase.h"

class EscenaMenuInicial : public EscenaBase
{
private:
	sf::Texture* _TexturaFondo;
	sf::Sprite* _SpriteFondo;
	sf::Mouse* _Mouse;
	sf::CircleShape* _SeguimientoMouse;

	// TEXTO
	sf::Font* _FuenteTexto;
	sf::Text* _Titulo;

	// 0 TITULO
	// 1 SUBTITULO
	// 2 JUGAR
	// 3 PUNTUACIONES
	// 4 SALIR

public:
	EscenaMenuInicial();
	void updatee_es(float lapso, sf::RenderWindow& _w);
	void draw_es(sf::RenderWindow& _w);
	~EscenaMenuInicial();
};

