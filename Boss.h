#pragma once
#include "Enemigo.h"
#include "bullet.h"
class Boss: public Enemigo
{
private:
	sf::Vector2f spawnPoint;
	sf::Clock clock;

	int Life;
	int _point;
	bool balas;
public:
	
	Boss(int Puntos);
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& _w) override;
	bool colision_bala(Bullet& bala);
	int getLife();
	void setLife(int colisiona);
	bool getbool();
};

