#pragma once
#include "SFML\Graphics.hpp"
#include "Voladores.h"
#include "Caminadores.h"
#include "Boss.h"
class Voladores;
class Caminadores;
class Boss;
#include "Arma.h"

class Bullet : public Entidad
{
private:	
	sf::Vector2f playerCenter;
	sf::Vector2f mousePos;
	sf::Vector2f aimDir;
	sf::Vector2f aimdDirNorm;
	sf::Vector2f currVelocity;
	sf::RectangleShape shape;
	sf::CircleShape PROBANDO;
	int alto = 2;
	int ancho = 2;
	float maxSpeed = 0.99f;
	sf::Clock clock;
	bool _estado;
public: 
	// contructor principal
	Bullet(sf::Vector2f pos, sf::Vector2f posM, sf::Vector2f origen,float rotation);
	// velocidad de la bala
	//void velocidad(int tipo); // 
	//void direccion(sf::RenderWindow _w);
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& w) override;

	sf::RectangleShape getBullet();
	void cambiarestado();
	bool collideWithBull(Voladores& vol);
	bool collideWithBullBoss(Boss& _Boss);
	bool collideWithBullcam(Caminadores& cam);
	bool getestado();
	~Bullet();
};


