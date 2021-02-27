#pragma once
#include <SFML/Graphics.hpp>
#include "TextoIngreso.h"

//CLASE QUE CUMPLE CON LA FUNCION DE CREAR UNA CAJA DE TEXTO CON UN SUBTITULO
class inputGUI
{
private:

	sf::Text* subtitulo;
	TextBox* ingreso;

public:
	inputGUI()
	{
		subtitulo = new sf::Text;
		ingreso = new TextBox;
	}

	inputGUI(sf::Font* fuente, float posY = 80);

	//GETS

	sf::Text getText() { return *subtitulo; }

	//SETS

	void setPos(float x, float y);	//SETEA LA POSICION TANTO DEL SUBTITULO COMO DE LA CAJA EN LA VENTANA SEGUN LOS PARAMETROS QUE SE LE MANDEN
	void setStringSubtitulo(const char* _subtitulo);
	void setLimiteIngreso(int lim);
	void setTextoIngreso(std::string _textIng);

	//METODOS

	void draw(sf::RenderWindow& ventana);
	void callEventoIngreso(sf::Event evento);

	TextBox& getIngreso() { return *ingreso; }

	~inputGUI();
};

