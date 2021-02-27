#pragma once
#include "SFML/Graphics.hpp"
class Entidad {

public:
	virtual void updatee_e(float a) = 0;
	virtual void draw_enty(sf::RenderWindow& w) = 0;

};