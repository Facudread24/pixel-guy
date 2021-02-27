#include "EscenaMenuInicial.h"
#include "EscenaPuntuaciones.h"
#include "EscenaJuego.h"
#include "Gameplay.h"
#include "Tipos_Fondo.h"

std::string* _stringtext;

EscenaMenuInicial::EscenaMenuInicial()
{
	int pos_Y = 200;//posicion general a cada palabra

	// ------- INICIALIZACION DE PUNTEROS --------------------

	_Mouse = new sf::Mouse;//crea el puntero para usarlo
	_Titulo = new sf::Text[5];//crea vector de texto
	_SpriteFondo = new sf::Sprite;//crea el fondo
	_stringtext = new std::string[5];//crea texto de string
	_SeguimientoMouse = new sf::CircleShape;
	_TexturaFondo = new sf::Texture;
	_FuenteTexto = new sf::Font;

	_stringtext[0] = "PIXEL GUY";
	_stringtext[1] = "BELLAVISTIS - RIVAS - ROSAMILIA";
	_stringtext[2] = ">		JUGAR";
	_stringtext[3] = ">		PUNTUACIONES";
	_stringtext[4] = ">		SALIR";

	// ---------- FIN DE INICIALIZACION -----------------------

	_SeguimientoMouse->setRadius(5);
	_SeguimientoMouse->setFillColor(sf::Color::Transparent);

	_TexturaFondo->loadFromFile("recursos/FondoMenu.png");
	_SpriteFondo->setTexture(*_TexturaFondo);
	_SpriteFondo->setScale(1.41f, 1.41f);
	_SpriteFondo->setColor(sf::Color(90, 90, 90, 255));


	_FuenteTexto->loadFromFile("recursos/fuentes/LLPIXEL3.ttf");

	for (int i = 0; i < 5; i++)
	{
		_Titulo[i].setCharacterSize(20);
		_Titulo[i].setFont(*_FuenteTexto);
		_Titulo[i].setString(_stringtext[i]);
		_Titulo[i].setFillColor(sf::Color(106, 255, 221));
		_Titulo[i].setPosition({ (float)350, (float)pos_Y });

		pos_Y += 35;
	}
	_Titulo[0].setCharacterSize(80);
	_Titulo[0].setPosition(230, 50);
	_Titulo[1].setPosition(270, 140);
	_Titulo[1].setFillColor(sf::Color(236, 255, 0));



	newMusic();
	setFondo(TipoFondo::Menu);
	this->FileSelect(this->getFondo());
	this->getMusic()->play();
	this->getMusic()->setVolume(50);
	this->getMusic()->setLoop(true);
}

void EscenaMenuInicial::updatee_es(float lapso, sf::RenderWindow& _w)
{
	_w.setMouseCursorVisible(true);
	_SeguimientoMouse->setPosition((float)_Mouse->getPosition(_w).x, (float)_Mouse->getPosition(_w).y);

	for (int i = 2; i < 5; i++)
	{
		if (_Titulo[i].getGlobalBounds().intersects(_SeguimientoMouse->getGlobalBounds()))
		{
			_Titulo[i].setFillColor(sf::Color(255, 99, 236));
			if (_Mouse->isButtonPressed(sf::Mouse::Left))
			{
				switch (i)
				{
				case 2:
					getMusic()->stop();
					_w.setMouseCursorVisible(false);
					Gameplay::getInstancia().cambiar_Escena(new EscenaJuego);
					break;
				case 3:
					getMusic()->stop();
					Gameplay::getInstancia().cambiar_Escena(new EscenaPuntuaciones);
					break;
				case 4:
					_w.close();
					break;

				}
			}
		}
		else _Titulo[i].setFillColor(sf::Color(255, 255, 255));
	}
}


void EscenaMenuInicial::draw_es(sf::RenderWindow& _w)
{
	_w.draw(*_SpriteFondo);
	for (int i = 0; i < 5; i++)_w.draw(_Titulo[i]);
}

EscenaMenuInicial::~EscenaMenuInicial()
{
	//delete[] _Titulo;
	//delete[] _stringtext;
	//delete _FuenteTexto;

	//delete _TexturaFondo;
	//delete _SpriteFondo;
	
	//delete _Mouse;
	//delete _SeguimientoMouse;
	// OK
	
}
