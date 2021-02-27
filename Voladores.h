#pragma once
#include "Enemigo.h"
#include "entidad.h"

class Bullet;

class Voladores : public Enemigo 
{
private:

	sf::Vector2f velocidad;
	sf::Vector2f spawnPoint;

	sf::Clock clock;
	sf::Clock clock2;
	bool enemig;


	int _puntos;
	int _tipo;
	int Ene_type;

public:

	Voladores(int puntos, int tipo);
	
	void updatee_e(float lapso)override;
	
	void draw_enty(sf::RenderWindow& _w) override;

	int X_rand();
	int y_rand();

	bool colision_bala(Bullet& bala);
	sf::Sprite& getEnemy1();

	~Voladores();
};