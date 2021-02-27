#include "Caminadores.h"
#include "Bullet.h"
#include "Enemigo.h"

bool band3 = true;

Caminadores::Caminadores(int puntos, int tipo_caminador)
{
	_point = puntos;
	_tipo = tipo_caminador;
	estado = true;
	//NUMERO ALEATORIO ENTRE  3 Y 6

	balasSoltadas = 3 + rand() % 6;
	
	if (band3 == true)
	{
		spawnPoint.x = 812;
		band3 = false;
		lad = false;
	}
	else
	{
		spawnPoint.x = -6;
		band3 = true;
		lad = true;
	}

	switch (_tipo)
	{
	case 1:
		setearSprite("recursos/Enemigo_6.png");

		spawnPoint.y = 380;
		score = 50;
		break;
	case 2:
		setearSprite("recursos/Enemigo_3.png");
		score = 70;
		spawnPoint.y = 428;
		break;
	case 3:
		setearSprite("recursos/Enemigo_8.png");
		score = 90;
		spawnPoint.y = 495;
		spawnPoint.x = float(rand() % 800);
		break;
	case 4:
		setearSprite("recursos/Enemigo_11.png");

		Type = 3;
		disparOk = true;
		enemyRe = new sf::Clock();
		enemyRe->restart();

		score = 110;
		spawnPoint.y = 425;
		break;
	case 5:
		setearSprite("recursos/Enemigo_4.png");

		Type = 4;
		disparOk = true;
		enemyRe = new sf::Clock();
		enemyRe->restart();
		lado = lad;
		score = 180;
		spawnPoint.y = 428;
		break;
	}

	setearPosXY(spawnPoint);

	velocidad.x = 0;
	velocidad.y = 0;
}

void Caminadores::updatee_e(float lapso)
{
	if (_tipo == 1)
	{
		if (spawnPoint.x < 0) getSprite().move(velocidad.x + 2, 0);

		else getSprite().move(velocidad.x - 2, 0);
	}
	else if (_point >= 1000 && _tipo == 1)
	{
		if (spawnPoint.x < 0) getSprite().move(velocidad.x + 5, 0);

		else getSprite().move(velocidad.x - 5, 0);
	}
	/***********************enemigo 2************************/
	if (_tipo == 2)
	{
		if (spawnPoint.x < 0) getSprite().move(velocidad.x + 6, 0);

		else getSprite().move(velocidad.x - 6, 0);
		
	}
	/***********************enemigo 3************************/
	if (_tipo == 3)
	{
		if (clock2.getElapsedTime().asSeconds() > 1) {
			getSprite().move(0, -8);
		}
	}
	/***********************enemigo 4************************/
	if (_tipo == 4)
	{
		if (spawnPoint.x <= 0)
		{
			getSprite().move(velocidad.x + 2, -1);
			
		}
		else
		{
			getSprite().move(velocidad.x - 2, -1);
		}
	}
	/***********************enemigo 5************************/
	if (_tipo == 5)
	{
		if (clock.getElapsedTime().asSeconds() > 5) {

			estado = false;
			if (!lad)
			{
				getSprite().move(velocidad.x + 10, 0);
			}
			else
			{
				getSprite().move(velocidad.x - 10, 0);
			}
			clock.restart();
		}
	}
}
void Caminadores::draw_enty(sf::RenderWindow& _w)
{
	if (estado != false)
	{
		_w.draw(_Sprite);
	}
}
bool Caminadores::colision_bala(Bullet& bala)
{
	return bala.collideWithBullcam(*this);
}

sf::Sprite& Caminadores::getEnemy1()
{
	return getSprite();
}

Caminadores::~Caminadores()
{

}
