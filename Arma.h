#pragma once
#include "entidad.h"
#include "Mouse.h"

class Arma: public Entidad
{
private:
	sf::Sprite arma;
	sf::Texture texturaArma;
	sf::Texture texturaArma2;

	sf::CircleShape circle;
	sf::Vector2f Pospersonaje;
	sf::Vector2f mousposit;
	float rotation;
	bool lado;
public:
	Arma(sf::Vector2f(pos));
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& _w) override;
	void setposmos(sf::Vector2f(mospos));
	void setpospers(sf::Vector2f(perspos));
	sf::Sprite& getarm();
	sf::CircleShape& getcircle();
	float getRotacion();
	float getRotacionCirculo();
	void setlad(bool);
	~Arma();
};

