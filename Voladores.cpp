#include "Voladores.h"
#include "Bullet.h"
#include <stdio.h>
#include <iostream>

using namespace std;
bool flag = true;
bool flag2 = true;
Voladores::Voladores(int puntos, int tipo)
{
	estado = true;
	_puntos = puntos;
	_tipo = tipo;

	//NUMERO ALEATORIO ENTRE  3 Y 6
	balasSoltadas = 3 + rand() % 6;
	
	if (flag == true)
	{
		spawnPoint.x = -1;
		spawnPoint.y = float(rand() % 300);
		flag = false;
	}
	else
	{
		spawnPoint.x = 810;
		spawnPoint.y = float(rand() % 300);
		flag = true;
	}

	enemig = true;

	switch (tipo)
	{
	case 1:
		setearSprite("recursos/Enemigo_1.png");
		Type = 5;
		disparOk = true;
		enemyRe = new sf::Clock();
		enemyRe->restart();
		score = 50;
		break;
	case 2:
		setearSprite("recursos/Enemigo_2.png");
		_Sprite.setScale(sf::Vector2f(1.5f, 1.5f));
		spawnPoint.y += 5;
		score = 90;
		break;
	case 3:
		setearSprite("recursos/Enemigo_9.png");

		spawnPoint.x = float(X_rand());
		spawnPoint.y = 0;
		score = 110;
		break;
	case 4:
		setearSprite("recursos/Enemigo_10.png");

		Type = 1;
		disparOk = true;
		enemyRe = new sf::Clock();
		enemyRe->restart();
		spawnPoint.x = float(X_rand());
		spawnPoint.y = 0;
		score = 150;
		break;
	case 5:
		setearSprite("recursos/Enemigo_5.png");

		Type = 2;
		disparOk = true;
		enemyRe = new sf::Clock();
		enemyRe->restart();
		spawnPoint.x = float(X_rand());
		spawnPoint.y = 310;
		score = 175;
		break;
	case 6:
		setearSprite("recursos/Enemigo_7.png");

		spawnPoint.x = float(X_rand());
		spawnPoint.y = 0;
		score = 200;
		break;
	}

	setearPosXY(spawnPoint);

	velocidad.x = 0;
	velocidad.y = 0;
}
/// LOS SPRITES TIENEN DISTINTOS MOVIMIENTOS 

void Voladores::updatee_e(float lapso)
{
	/*******************ENEMIGO 1***********/
	if (_tipo == 1)
	{
		if (spawnPoint.x < 0)
		{
			_Sprite.move(velocidad.x + 3, 0);
		}
		else
		{
			_Sprite.move(velocidad.x - 3, 0);
		}
	}
	/*******************ENEMIGO 2**********************/
	if (_tipo == 2)
	{
		if (spawnPoint.x <= 0)
		{
			if (enemig == true)
			{
				_Sprite.move(velocidad.x + 1, velocidad.y + 2);
				if (_Sprite.getPosition().y >= 300)
				{
					enemig = false;
				}
			}
			else
			{
				_Sprite.move(velocidad.x + 1, velocidad.y - 2);
				if (_Sprite.getPosition().y <= 0)
				{
					enemig = true;
				}
			}
		}
		else
		{
			if (enemig == true)
			{
				_Sprite.move(velocidad.x - 1, velocidad.y + 2);
				if (_Sprite.getPosition().y >= 300)
				{
					enemig = false;
				}
			}
			else
			{
				_Sprite.move(velocidad.x - 1, velocidad.y - 2);
				if (_Sprite.getPosition().y <= 0)
				{
					enemig = true;
				}
			}
		}
	}
	/**********************ENEMIGO 3*************************/
	if (_tipo == 3)
	{
		_Sprite.move(0, velocidad.y + 3);
	}
	/**********************ENEMIGO 4*************************/
	if (_tipo == 4 )
	{
		if (clock.getElapsedTime().asSeconds() > 20)
		{
			estado = false;
			_Sprite.move(0, velocidad.y - 20);
		}
	}
	/**********************ENEMIGO 5*************************/
	if (_tipo == 5)
	{
		if (clock2.getElapsedTime().asSeconds() > 15)
		{
			estado = false;
			_Sprite.move(0, velocidad.y + 80);
		}
	}
	/**********************ENEMIGO 6*************************/
	if (_tipo == 6)
	{
		_Sprite.move(0, velocidad.y + 6);
	}
}

void Voladores::draw_enty(sf::RenderWindow& _w)
{
	if (estado != false)
	{
		_w.draw(_Sprite);
	}
}

int Voladores::X_rand()
{
	return rand() % 800;
}

int Voladores::y_rand()
{
	return rand() % 300;
}

bool Voladores::colision_bala(Bullet& bala)
{
	return bala.collideWithBull(*this);
}

sf::Sprite& Voladores::getEnemy1()
{
	return _Sprite;
}

Voladores::~Voladores() {
	if (enemyRe!=nullptr)
	{
		delete enemyRe;
	}
}