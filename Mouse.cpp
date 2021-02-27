#include "Mouse.h"

Mouse::Mouse(const sf::Vector2f& pos)
{
	_mouse.loadFromFile("recursos/cursor.png");
	_sMouse.setTexture(_mouse);
	_sMouse.setScale(sf::Vector2f(0.3f,0.3f));
	_sMouse.setPosition(pos);
	
}

void Mouse::updatee_e(float lapso)
{
	
}

void Mouse::update_pos(sf::RenderWindow& _w)
{
	float base = (sf::Mouse::getPosition(_w).x) - 45;
	float altura = (sf::Mouse::getPosition(_w).y) - 25;
	_sMouse.setPosition(sf::Vector2f(base, altura));

}

void Mouse::draw_enty(sf::RenderWindow& _w)
{
	update_pos(_w);
	_w.draw(_sMouse);
}

sf::Sprite& Mouse::getMouse()
{
	return _sMouse;
}
