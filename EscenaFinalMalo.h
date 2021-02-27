#pragma once
#include "EscenaBase.h"
#include  "Score.h"
#include "Input.h"
#include <SFML/Graphics.hpp>
class EscenaFinalMalo : public EscenaBase
{
private:
	sf::Texture* _TexturaFondo;
	sf::Sprite* _SpriteFondo;
	sf::Text* _Cartel;
	sf::Font* _Font;

	inputGUI* _Ingreso;
	sf::Clock _Rel;
	sf::Clock _Rel2;

	Score* _Score;
	const char* _Nombre;

public:
	EscenaFinalMalo();

	const char* eliminarUltChar();
	void guardarArchivoScore();
	void process_event(const sf::Event& e);
	void updatee_es(float lapso, sf::RenderWindow& _w);
	void draw_es(sf::RenderWindow& _w);

	~EscenaFinalMalo();
};

