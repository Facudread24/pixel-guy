#pragma once
#include "EscenaBase.h"
#include "Input.h"
#include "Score.h"
#include <SFML/Graphics.hpp>
class EscenaFinalBueno : public EscenaBase
{
private:
	sf::Texture* _TexturaFondo;
	sf::Sprite* _SpriteFondo;
	sf::Text* _Cartel;
	sf::Font* _Font;

	inputGUI* _Ingreso;
	sf::Clock _Rel2;
	sf::Clock _Rel;

	const char* _Nombre;
	Score* _Score;

public:
	EscenaFinalBueno();
	void process_event(const sf::Event& e);
	void updatee_es(float lapso, sf::RenderWindow& _w);
	void draw_es(sf::RenderWindow& _w);
	void guardarArchivoScore();
	const char* eliminarUltChar();

	~EscenaFinalBueno();
};

