#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "entidad.h"
#include "disparos.h"
class Bullet;

class Enemigo : public Entidad
{
protected:
	sf::Texture _Textura;
	sf::Sprite _Sprite;
	sf::Vector2f _PosicionXY;
	sf::Clock *enemyRe;

	int score;
	int balasSoltadas;
	bool estado;
	int Type;
	bool disparOk;
	bool lado;
public:

	void setearSprite(const std::string UB_RECURSO);

	void setearPosXY(sf::Vector2f pos);

	virtual bool colision_bala(Bullet& bala) = 0;
	
	sf::Sprite& getSprite() { return _Sprite; }

	int getScore();
	sf::Clock& getclock();
	void muerto();
	bool getEstado();
	bool getPuedoDisparar();
	bool getlado();
	int getbalasSoltadas();
	int getType();
};