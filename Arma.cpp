#include "Arma.h"
#include <iostream>
using namespace std;

const float PI = 3.14159265;

Arma::Arma(sf::Vector2f(pos))
{
	texturaArma.loadFromFile("recursos/arma.png");
	texturaArma2.loadFromFile("recursos/arma2.png");
	//circle.setFillColor(sf::Color::Red);
	circle.setPosition(pos);
	circle.setRadius(5);
	arma.setTexture(texturaArma);
	arma.setScale({ 0.8f,0.8f });
	arma.setOrigin(0,0);	
	lado = false;
}

void Arma::updatee_e(float lapso)
{
	//calculo angulo
	float dx = Pospersonaje.x - (int)mousposit.x;
	float dy = Pospersonaje.y - (int)mousposit.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	if (lado == false)
	{
		arma.setTexture(texturaArma);
		arma.setPosition({ Pospersonaje.x + 3,Pospersonaje.y + 23 });
		arma.setOrigin
		(
			arma.getGlobalBounds().width / 4.f,
			arma.getGlobalBounds().height / 8.f
		);
		arma.setRotation(rotation + 180);
		
		circle.setOrigin
		(
			circle.getGlobalBounds().width - 60,
			circle.getGlobalBounds().height - 30
		);
		circle.setPosition(arma.getPosition().x, arma.getPosition().y);
	}
	else
	{
		arma.setTexture(texturaArma2);
		arma.setPosition({ Pospersonaje.x + 10,Pospersonaje.y + 20 });
		
		arma.setOrigin
		(
			arma.getLocalBounds().width-30,
			arma.getLocalBounds().height/8.f
		);
		arma.setRotation(rotation);
		circle.setOrigin
		(
			circle.getGlobalBounds().width-50,
			circle.getGlobalBounds().height+15
		);
		circle.setPosition(arma.getPosition().x, arma.getPosition().y);
	}
	circle.setRotation(rotation+180);
	
}

void Arma::draw_enty(sf::RenderWindow& _w)
{
	_w.draw(arma);
	//_w.draw(circle);
}

void Arma::setposmos(sf::Vector2f(mospos))
{
	mousposit = mospos;
}

void Arma::setpospers(sf::Vector2f(perspos))
{
	Pospersonaje = perspos;	
}
sf::Sprite& Arma::getarm()
{
	return arma;
}

sf::CircleShape& Arma::getcircle()
{
	return circle;
}
float Arma::getRotacion()
{
	return rotation;
}
float Arma::getRotacionCirculo()
{
	return circle.getRotation();
}
void Arma::setlad(bool flag)
{
	lado = flag;
}
Arma::~Arma()
{

}