#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include <string>
#include "EscenaBase.h"
#include <vector>
class Gameplay
{
private:
	sf::RenderWindow _window;
	EscenaBase* actual;
	EscenaBase* siguiente;
	sf::Clock clock;

	void processEvents();
	void update_game();
	void draw_game();
	
	static Gameplay *instancia;
	Gameplay();
	
public:
	
	//bucle de juego
	void run();
	///cambiar escena
	void cambiar_Escena(EscenaBase* escena);
	// intancia de juego (diseño singleton)
	static Gameplay &getInstancia();
	// Juego, ventana, escena inicial
	static Gameplay &create(const sf::VideoMode& videoMode, EscenaBase* escena, const std::string& nombre = "");
	
};

