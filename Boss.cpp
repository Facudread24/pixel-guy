#include "Boss.h"
#include "Enemigo.h"
#include<iostream>

bool band = true;
Boss::Boss(int puntos)
{
	setearSprite("recursos/Boss.png");
	setearPosXY({ 780,381 });
	getSprite().setScale(0.5f, 0.5f);
	_point = puntos;
	Life = 100;
	Type = 5;
	enemyRe = new sf::Clock();
	enemyRe->restart();
	balas = true;
}

void Boss::updatee_e(float lapso)
{
	enemyRe->restart();
	if (Life==100)
	{
		score = rand()%50+1;
		balas = true;
	}
	else if (Life>40 && Life<=80)
	{
		balas = false;
		score = rand() % 60 + 1;
		if (getSprite().getPosition().y > 5) {
			getSprite().move(0, -6);
		}
		else if(band==true){
			getSprite().setScale({ 1,1 });
			getSprite().move(-8, 0);
			if (getSprite().getPosition().x <= -3) {
				band = false;
			}
		}
		else if (band == false) {
			getSprite().move(8, 0);
			if (getSprite().getPosition().x >= 680) {
				band = true;
			}
		}
	}
	else if (Life <= 40)
	{
		score = rand() % 80 + 1;
		if (getSprite().getPosition().y > 5) {
			getSprite().move(0, -3);
		}
		if (clock.getElapsedTime().asSeconds() > 2) {
			getSprite().move(0, 8);
			if (getSprite().getPosition().y >= 381) {
				clock.restart();
			}
		}
		else if (band == true) {
			getSprite().move(-8, 0);
			if (getSprite().getPosition().x <= -3) {
				band = false;
			}
		}
		else if (band == false) {
			getSprite().move(8, 0);
			if (getSprite().getPosition().x >= 680) {
				band = true;
			}
		}
	}
	//POS BOSS
	//std::cout << getSprite().getPosition().x;
	//std::cout << "\t\t" << getSprite().getPosition().y << std::endl;
}

void Boss::draw_enty(sf::RenderWindow& _w)
{
	_w.draw(_Sprite);
}

bool Boss::colision_bala(Bullet& bala)
{
	return bala.collideWithBullBoss(*this);
}

int Boss::getLife()
{
	return Life;
}

void Boss::setLife(int colisiona)
{
	Life -= colisiona;
}

bool Boss::getbool()
{
	return balas;
}
