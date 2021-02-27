#include "disparos.h"
#include <iostream>

disparos::disparos(sf::Vector2f PosEne,int tipo, bool lado)
{
	_estado = true;
	tipo_E = tipo;
	UbicacionXY = PosEne;
	enemylado = lado;
	velocidad(tipo_E);

}
void disparos::velocidad(int tipo) {

	switch (tipo)
	{
	case 1:
		speedX.x = 0;
		speedX.y = 4.5f;
		ShotBull.setPosition(UbicacionXY.x + 35, UbicacionXY.y + 43);
		ShotBull.setFillColor(sf::Color::Red);
		ShotBull.setSize({ 5.0f, 15.0f });
		break;
	case 2:
		speedX.x = 0;
		speedX.y = 2.5f;
		ShotBull.setPosition(UbicacionXY.x + 20, UbicacionXY.y + 43);
		ShotBull.setSize({ 15,40 });
		ShotBull.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		speedX.x = 0;
		speedX.y = 5.5f;
		ShotBull.setPosition(UbicacionXY.x + 3, UbicacionXY.y + 20);
		ShotBull.setSize({ 5.0f, 15.0f });
		ShotBull.setFillColor(sf::Color::Magenta);
		break;
	case 4:
		if (enemylado)
		{
			speedX.x = 5.5f;
			speedX.y = 0;
			ShotBull.setPosition(UbicacionXY.x +60, UbicacionXY.y + 20);
		}
		else {
			speedX.x = -5.5f;
			speedX.y = 0;
			ShotBull.setPosition(UbicacionXY.x + 3, UbicacionXY.y + 20);
		}
		ShotBull.setSize({ 15.0f, 5.0f });
		ShotBull.setFillColor(sf::Color::Yellow);
		break;
	case 5:
		speedX.x = 0;
		speedX.y = 5.5f;
		ShotBull.setPosition(UbicacionXY.x + 20, UbicacionXY.y + 70);
		ShotBull.setSize({ 5.0f, 17.0f });
		ShotBull.setFillColor(sf::Color::Blue);
		break;
	case 6:
		if (enemylado)
		{
			speedX.x = -3.f;
			speedX.y = 0;
			ShotBull.setPosition(UbicacionXY.x, UbicacionXY.y+50);
		}
		else {
			speedX.x = 0;
			speedX.y = 1.0f;
			ShotBull.setPosition(UbicacionXY.x, UbicacionXY.y);
		}
		ShotBull.setSize({ 7.0f, 12.0f });
		ShotBull.setFillColor(sf::Color(rand()%225, rand() % 225, rand() % 225));
		break;
	default:
		break;
	}
}
void disparos::updatee_e(float lapso)
{
	if (tipo_E==1 || tipo_E == 2 || tipo_E == 3 || tipo_E == 4 || tipo_E == 5 || tipo_E == 6)
	{
		ShotBull.move(speedX.x, speedX.y);
	}
}

void disparos::draw_enty(sf::RenderWindow& w)
{
	if (_estado)
	{
		w.draw(ShotBull);
	}
}
void disparos::cambiarestado()
{
	_estado = false;
}
sf::Vector2f disparos::getUbi()
{
	return UbicacionXY;
}

bool disparos::getestado()
{
	return _estado;
}

sf::RectangleShape& disparos::getShotBull()
{
	return ShotBull;
}

disparos::~disparos()
{

}
