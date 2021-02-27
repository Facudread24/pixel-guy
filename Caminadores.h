#pragma once
#include "entidad.h"
#include "Enemigo.h"
#include "Item.h"

class Bullet;

class Caminadores: public Enemigo
{
private:
	sf::Clock clock;
	sf::Clock clock2;
	sf::Vector2f velocidad;
	sf::Vector2f spawnPoint;
	int _point;
	int _tipo;
	bool lad;
public:

	Caminadores(int puntos, int tipo_caminador);
	
	void updatee_e(float lapso)override;

	void draw_enty(sf::RenderWindow& _w) override;

	bool colision_bala(Bullet& bala);

	sf::Sprite& getEnemy1();

	~Caminadores();
};

