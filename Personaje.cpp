#include "Personaje.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

Personaje::Personaje(const sf::Vector2f& pos)
{
	
	_texturaP.loadFromFile("recursos/pp.png");

	// ACA SE PUEDE SETEAR LA MUNICION INICIAL DEL PJ
	municion = new MunicionPersonaje(30);
	box.setFillColor(sf::Color::Transparent);
	//box.setOutlineColor(sf::Color(255, 0, 0, 255));
	//box.setOutlineThickness(2);
	box.setPosition(pos);
	box.setSize({ 15,40 });
	_spriteP.setTexture(_texturaP);
	_spriteP.setPosition(pos);
	_spriteP.setScale(1.30f, 1.30f);
	_fps_sprite = 0;
	division.x = 4;
	division.y = 3;
	_estado = ESTADOS::QUIETO_DER;
	set_frame(_spriteP);

	//Probando
	moverseIzq = true;
	moverseDer = true;

	soundbuffer.loadFromFile("recursos/audio/paso.wav");
	paso.setBuffer(soundbuffer);
	paso.setVolume(100);
	sounddaño.loadFromFile("recursos/Audio/daño.wav");
	daño.setBuffer(sounddaño);
	daño.setVolume(100);
}

void Personaje::checkearColisiones()
{
	//////////////////////////////////////////////////////////////////
	//	VERIFICION LA COLISION DE LOS BORDES DERECHOS DE LA VENTANA /
	////////////////////////////////////////////////////////////////

	if (_spriteP.getPosition().x >= 800.0f) moverseDer = false;
	else moverseDer = true;

	/////////////////////////////////////////////////////////////////////
	//	VERIFICACION LA COLISION DE LOS BORDES IZQUIERDOS DE LA VENTANA/
	///////////////////////////////////////////////////////////////////

	if (_spriteP.getPosition().x <= 0.0f) moverseIzq = false;
	else moverseIzq = true;

	////////////////////////////////////////////////////////////////
	//	VERIFICACION LA COLISION DEL PISO						 //
	//////////////////////////////////////////////////////////////
	if (_spriteP.getPosition().y >= 380.5f)
	{
		_spriteP.setPosition(_spriteP.getPosition().x, 380.0f);
		_estado = ESTADOS::QUIETO;
	}

	//if (!moverseIzq) std::cout << "NO ME PUEDO MOVER A LA IZQUIERDA" << std::endl;
	//if (!moverseDer) std::cout << "NO ME PUEDO MOVER A LA DERECHA" << std::endl;
}

void Personaje::cmd()
{
	if (_estado == ESTADOS::QUIETO || _estado == ESTADOS::QUIETO_DER || _estado == ESTADOS::QUIETO_IZQ)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			paso.play();
			frame.x = 3;
			_estado = ESTADOS::CAMINANDO_DER;
			lado = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			paso.play();
			_estado = ESTADOS::CAMINANDO_IZQ;
			frame.x = 1;
			set_frame(_spriteP);
			lado = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_estado = ESTADOS::SALTO;
			_vel_salto = 25;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				_estado = ESTADOS::SALTO_DIAG_DER;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				_estado = ESTADOS::SALTO_DIAG_IZQ;
			}
		}
	}
}

void Personaje::updatee_e(float lapso)
{
	
	if (_sp_vel != 6.0f && clock.getElapsedTime().asSeconds() > 8) {
		_sp_vel = 6.0f;
	}
	//std::cout << "TENES " << municion->getCantidadBalas() << " BALAS" << std::endl;
	switch (_estado)
	{
	case QUIETO:
		//std::cout << "ESTOY QUIETO" << std::endl;
		break;
	case QUIETO_IZQ:
		//std::cout << "ESTOY QUIETO IZQ" << std::endl;
		frame.x = 1;
		frame.y = 0;
		_fps_sprite = 0;
		set_frame(_spriteP);
		break;
	case QUIETO_DER:
		//std::cout << "ESTOY QUIETO DER" << std::endl;
		frame.x = 3;
		frame.y = 0;
		_fps_sprite = 0;
		set_frame(_spriteP);
		break;
	case CAMINANDO_IZQ:
		//std::cout << "ESTOY CAMINANDO IZQ" << std::endl;
		if (_fps_sprite == 3)
		{
			frame.y++;
			_fps_sprite = 0;
		}
		if (frame.y < division.y)
		{
			_fps_sprite++;

			// SI NO SE PUEDE MOVER A LA IZQUIERDA, CAMBIO EL ESTADO A QUIETO 
			if (moverseIzq)_spriteP.move(-_sp_vel, 0);
			else _estado = ESTADOS::QUIETO_IZQ;

		}
		else
		{
			frame.y = 0;
			_estado = ESTADOS::QUIETO_IZQ;
		}
		set_frame(_spriteP);
		break;

	case CAMINANDO_DER:
		//std::cout << "ESTOY CAMINANDO DER" << std::endl;
		if (_fps_sprite == 3)
		{
			frame.y++;
			_fps_sprite = 0;
		}
		if (frame.y < division.y)
		{
			_fps_sprite++;

			// SI NO SE PUEDE MOVER A LA DERECHA, CAMBIO EL ESTADO A QUIETO 
			if(moverseDer)_spriteP.move(_sp_vel, 0);
			else _estado = ESTADOS::QUIETO_DER;

		}
		else
		{
			frame.y = 0;
			_estado = ESTADOS::QUIETO_DER;
		}
		set_frame(_spriteP);
		break;

	case SALTO:
		//std::cout << "ESTOY SALTANDO" << std::endl;
		_vel_salto -= 2;
		_spriteP.move(0, -_vel_salto);

		if (_spriteP.getPosition().y >= 381)
		{
			_spriteP.setPosition(_spriteP.getPosition().x, 380.0f);
			_estado = ESTADOS::QUIETO;
		}

		break;
	case SALTO_DIAG_DER:
		frame.x = 3;
		frame.y = 1;
		set_frame(_spriteP);

		_vel_salto -= 2;

		// SI NO SE PUEDE MOVER A LA DERECHA, BAJA EN LA MISMA POSICION DE X
		if (moverseDer) _spriteP.move(6, -_vel_salto);
		else _spriteP.move(0, -_vel_salto);

		if (_vel_salto <= -16)
		{
			frame.x = 3;
			frame.y = 0;
			set_frame(_spriteP);
		}
		break;
	case SALTO_DIAG_IZQ:
		frame.x = 1;
		frame.y = 2;
		set_frame(_spriteP);
		_vel_salto -= 2;

		// SI NO SE PUEDE MOVER A LA IZQUIERDA, BAJA EN LA MISMA POSICION DE X
		if (moverseIzq) _spriteP.move(-6, -_vel_salto);
		else _spriteP.move(0, -_vel_salto);

		if (_vel_salto <= -16)
		{
			frame.x = 1;
			frame.y = 0;
			set_frame(_spriteP);
		}
		break;
	
	}
	box.setPosition(_spriteP.getPosition().x+30.5f, _spriteP.getPosition().y + 35.0f);
	
}
//PASO EL PERSONAJE Y MIDO LOS FRAMES
void Personaje::set_frame(sf::Sprite& pers)
{
	sf::IntRect pos(frame.x * (pers.getTexture()->getSize().x / (division.x)), frame.y * (pers.getTexture()->getSize().y / division.y), pers.getTexture()->getSize().x / (division.x), pers.getTexture()->getSize().y / (division.y));
	pers.setTextureRect(pos);
}

void Personaje::setvelocidad(float velocidad)
{
	_sp_vel = velocidad;
	clock.restart();
}

MunicionPersonaje& Personaje::getMunicion()
{
	return *municion;
}

void Personaje::draw_enty(sf::RenderWindow& _w)
{
	_w.draw(_spriteP);
	_w.draw(box);
}

sf::Sprite& Personaje::getDrawn()
{
	return _spriteP;
}

sf::RectangleShape& Personaje::getBox()
{
	return box;
}

const sf::Vector2f& Personaje::getCordenadas()
{
	return _spriteP.getPosition();
}

void Personaje::IDaño()
{
	daño.play();
}

bool Personaje::isDead()
{
	if (this->getMunicion().getCantidadBalas() == 0 || this->getMunicion().getCantidadBalas() < 4) return true;
	else return false;
}

bool Personaje::getlado()
{
	return lado;
}
