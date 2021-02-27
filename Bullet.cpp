#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Personaje.h"
#include "Mouse.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "Caminadores.h"

using namespace std;
int cont = 0;
Bullet::Bullet(sf::Vector2f pos, sf::Vector2f posM, sf::Vector2f origen, float rotation)
{
	_estado = true;

	shape.setSize(sf::Vector2f(7.0f, 7.0f));
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	shape.setFillColor(sf::Color(r, g, b));
	shape.setPosition(pos);
	shape.setOrigin(origen);
	shape.setRotation(rotation);
	
	//cout << "ES X" << endl;
	//cout << shape[i].getPosition().x<<endl;
	//cout << "ES Y" << endl;
	//cout << shape[i].getPosition().y << endl;

	playerCenter = pos;
	mousePos = posM;
	currVelocity = sf::Vector2f(0.f, 0.f);
	aimDir = mousePos - playerCenter;
	aimDir.x += rand() % 100 - 50;
	aimDir.y += rand() % 100 - 50;
	float div = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	aimdDirNorm = aimDir / div;
	currVelocity = (aimdDirNorm * maxSpeed);
	currVelocity = currVelocity / 0.11f;
}

void Bullet::updatee_e(float lapso)
{
	shape.move(currVelocity);
}

void Bullet::draw_enty(sf::RenderWindow& w)
{
	if (_estado != false)
	{
		w.draw(shape);
	}
}


sf::RectangleShape Bullet::getBullet()
{
	return this->shape;
}

void Bullet::cambiarestado()
{
	_estado = false;
}

bool Bullet::collideWithBull(Voladores& vol) {
	sf::FloatRect charRect = vol.getEnemy1().getGlobalBounds();
	sf::FloatRect bullRect = getBullet().getGlobalBounds();

	return bullRect.intersects(charRect);

}

bool Bullet::collideWithBullBoss(Boss& _Boss)
{
	sf::FloatRect charRect = _Boss.getSprite().getGlobalBounds();
	sf::FloatRect bullRect = getBullet().getGlobalBounds();

	return bullRect.intersects(charRect);

}

bool Bullet::collideWithBullcam(Caminadores& cam)
{
	sf::FloatRect charRect = cam.getEnemy1().getGlobalBounds();
	sf::FloatRect bullRect = getBullet().getGlobalBounds();

	return bullRect.intersects(charRect);

}

bool Bullet::getestado()
{
	return _estado;

}

Bullet::~Bullet()
{

}