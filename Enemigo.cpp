#include "Enemigo.h"

void Enemigo::setearSprite(const std::string UB_RECURSO)
{
	Type = 0;
	disparOk = false;
	_Textura.loadFromFile(UB_RECURSO);
	_Sprite.setTexture(_Textura);
}

void Enemigo::setearPosXY(sf::Vector2f pos)
{
	this->_PosicionXY = pos;
	_Sprite.setPosition(_PosicionXY);
}

int Enemigo::getScore()
{
	return score;
}

sf::Clock& Enemigo::getclock()
{
	return *enemyRe;
}

void Enemigo::muerto()
{
	this->estado = false;
}

bool Enemigo::getEstado()
{
	return estado;
}

bool Enemigo::getPuedoDisparar()
{
	return disparOk;
}
bool Enemigo::getlado()
{
	return lado;
}
int Enemigo::getbalasSoltadas()
{
	return balasSoltadas;
}

int Enemigo::getType()
{
	return Type;
}
