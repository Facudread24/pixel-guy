#include "EscenaFinalMalo.h"
#include "Gameplay.h"
#include "EscenaMenuInicial.h"
#include <SFML/Graphics.hpp>

EscenaFinalMalo::EscenaFinalMalo()
{
	_TexturaFondo = new sf::Texture;
	_SpriteFondo = new sf::Sprite;
	_Cartel = new sf::Text;
	_Font = new sf::Font;
	_Score = new Score();
	_Nombre = new const char[4];

	_Font->loadFromFile("recursos/fuentes/LLPIXEL3.ttf");

	_Ingreso = new inputGUI(_Font, 10.0f);

	_TexturaFondo->loadFromFile("recursos/Fondo4.png");
	_SpriteFondo->setTexture(*_TexturaFondo);
	_SpriteFondo->setScale(0.9f, 0.8f);

	_Cartel->setString("POR TU CULPA NUESTRO MUNDO ES INHABITABLE... \nPOR FAVOR INGRESA TU NOMBRE PARA ACORDARNOS DE TI");
	_Cartel->setFont(*_Font);
	_Cartel->setCharacterSize(20);
	_Cartel->setPosition({ 10, 520 });

	_Ingreso->setStringSubtitulo("NOMBRE:");
	_Ingreso->setPos(650.0f, 543.0f);
	_Ingreso->setLimiteIngreso(4);

	newMusic();
	setFondo(TipoFondo::EscenaGameOverbad);
	this->FileSelect(this->getFondo());
	this->getMusic()->play();
	this->getMusic()->setVolume(50);
	this->getMusic()->setLoop(true);

	_Rel.restart();
}

void EscenaFinalMalo::process_event(const sf::Event& e)
{
	if(_Rel.getElapsedTime().asSeconds() > 1) _Ingreso->callEventoIngreso(e);
}

void EscenaFinalMalo::updatee_es(float lapso, sf::RenderWindow& _w)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (_Rel2.getElapsedTime().asSeconds() > 1)	// USO UN RELOJ POR SI ACASO 
		{
			
			_Nombre = eliminarUltChar();	// PASO EL STRING DE LO QUE INGRESE EL USUARIO A UNA VARIABLE AU

			// TODO: MAYBE UNA VERIFICACION DE NOMBRE? 
	
			guardarArchivoScore();

			_Rel2.restart();
		}

		Gameplay::getInstancia().cambiar_Escena(new EscenaMenuInicial);
	}

}

const char* EscenaFinalMalo::eliminarUltChar()		// PARA BORRAR EL ULTIMO CARACTER DEL INPUT QUE POR LO GENERAL 
													// ES UN "_"
{
	char* asad;
	int tamString = 0;

	asad = new char[4];

	strcpy(asad, _Ingreso->getIngreso().getTexto().c_str());

	tamString = _Ingreso->getIngreso().getTexto().size();

	if (--tamString > 0) asad[tamString] = '\0';

	return asad;
}

void EscenaFinalMalo::guardarArchivoScore()
{
	int pos = contarRegistros() - 1;

	// YA GUARDE ANTES LOS PUNTOS AHORA EL NOMBRE
	if (pos < 0)	
	{
		return;		// SI NO PUDE LEER EL ARCHIVO CORRECTAMENTE ME VOY
	}
	else
	{
		_Score->leerpuntos(pos);		// LEO EL ARCHIVO

		_Score->setNombre(_Nombre);		// LE PASO EL NOMBRE Y SOBRE ESCRIBO
		_Score->SobreEscribir(pos);
	}
}


void EscenaFinalMalo::draw_es(sf::RenderWindow& _w)
{
	_w.draw(*_SpriteFondo);
	_w.draw(*_Cartel);
	_Ingreso->draw(_w);
}

EscenaFinalMalo::~EscenaFinalMalo()
{
	delete _TexturaFondo;
	delete _SpriteFondo;
	delete _Cartel;
	delete _Font;
	delete _Ingreso;
	//delete[] _Nombre;
	delMusic();
}