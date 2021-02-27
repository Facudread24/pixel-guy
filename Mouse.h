#pragma once
#include "SFML/Graphics.hpp"
#include "entidad.h"
class Mouse: public Entidad
{
private:
	sf::Texture _mouse;
	sf::Sprite _sMouse;
public:
	Mouse(const sf::Vector2f& pos);
	void updatee_e(float lapso) override;
	void update_pos(sf::RenderWindow& _w);
	void draw_enty(sf::RenderWindow& _w) override;
	
	sf::Sprite& getMouse();
};

