#include "Input.h"

inputGUI::inputGUI(sf::Font* fuente, float posY)
{
	subtitulo = new sf::Text;
	ingreso = new TextBox;

	subtitulo->setPosition(55, posY);
	subtitulo->setCharacterSize(20);
	subtitulo->setFillColor(sf::Color::White);
	subtitulo->setString("INGRESAR NOMBRE");
	subtitulo->setFont(*fuente);

	ingreso->setFuente(*fuente);
	ingreso->setSelected(true);
}


void inputGUI::setPos(float x, float y)
{
	subtitulo->setPosition(x, y);
	ingreso->setPosition({ x + 110, y+2 });
}

void inputGUI::setStringSubtitulo(const char* _subtitulo)
{
	subtitulo->setString(_subtitulo);
}

void inputGUI::setLimiteIngreso(int lim)
{
	ingreso->setLimit(true, lim);
}

void inputGUI::setTextoIngreso(std::string _textIng)
{
	ingreso->setTexto(_textIng);
}

inputGUI::~inputGUI()
{
	delete subtitulo;
	delete ingreso;
}

void inputGUI::callEventoIngreso(sf::Event evento)
{
	ingreso->typedOn(&evento);
}

void inputGUI::draw(sf::RenderWindow& ventana)
{
	ventana.draw(*subtitulo);
	ingreso->drawTo(ventana);
}


