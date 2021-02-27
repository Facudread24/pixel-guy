#include "EscenaJuego.h"
#include "Personaje.h"
#include "Mouse.h"
#include "Voladores.h"
#include "SFML/graphics.hpp"
#include "Bullet.h"
#include "Score.h"
#include "Boss.h"
#include "Tipos_Fondo.h"
#include "Gameplay.h"
#include "EscenaFinalMalo.h"
#include "EscenaFinalBueno.h"
#include "EscenaMenuInicial.h"
#include "disparos.h"

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>

const std::string& puntos = "SCORE: ";
const std::string& NOMBRE = "Mr.ROBOTO: ";

using namespace std;

bool pausa = false;

int _CantidadBalas; //Variable para saber cuantas balas hay en el vector "bull"
int _BalasFalse = 0;	//Variable para contar cuantas balas hay en false
int _Balas_False_enemy = 0;	//Variable para contar cuantas balas hay en false DE ENEMIGOS
int _EnemigosFalse = 0;
int seg = 0;
EscenaJuego::EscenaJuego()
{
	itemBand = true;
	band_Boss = true;
	GoodEnd = false;
	BadEnd = false;
	reloj.restart();
	fuente.loadFromFile("recursos/fuentes/LLPIXEL3.ttf");
	textoPuntos.setFont(fuente);
	textoBoss.setFont(fuente);
	PUNTOST.setFont(fuente);
	TextFondo.loadFromFile("recursos/Fondo.png");

	PUNTOST.setString(puntos);
	PUNTOST.setPosition(sf::Vector2f(0, 0));
	PUNTOST.setScale({ 0.8,0.8 });

	iconoMuni.loadFromFile("recursos/LogoMuni3.png");
	municion.setTexture(iconoMuni);
	municion.setPosition({ 225,1 });
	municion.setScale({ 0.09,0.09 });
	cantbalas.setFont(fuente);
	SpFondo.setTexture(TextFondo);
	SpFondo.setScale(1.41f, 1.41f);

	newMusic();
	setFondo(TipoFondo::EscenaJuego);
	this->FileSelect(this->getFondo());
	this->getMusic()->play();
	this->getMusic()->setVolume(30);
	this->getMusic()->setLoop(true);

	personaje = new Personaje(sf::Vector2f(500, 380));
	cursor = new Mouse(sf::Vector2f(0, 0));
	_ScoreArchivo = new Score;
	_arm = new Arma(personaje->getBox().getPosition());

	add(personaje);
	add(_arm);
	add(cursor);

	crear_enemy_vol(_score, 1);
	crear_enemy_cam(_score, 1);

	timer.restart();
	timer2.restart();
	clock.restart();
	clockBala.restart();

	_score = 7800;

}

void EscenaJuego::updatee_es(float lapso, sf::RenderWindow& _w)
{
	ending();

	if (RelojPausa.getElapsedTime().asSeconds()>1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pausa == false) {
			pausa = true;
			RelojPausa.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pausa == true) {
			pausa = false;
			RelojPausa.restart();
		}
		
	}
	
	if (!pausa) {
		std::string aux;
		std::stringstream buff;
		std::string aux_Boss;
		std::stringstream buff_boss;
		std::string aux_balas;
		std::stringstream buff_balas;
		letras = (sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
		tipode = tipo(_score);

		//movimiento del personaje
		personaje->cmd();
		//Posicion del mouse
		_arm->setposmos(cursor->getMouse().getPosition());
		//pos de la caja del personaje
		_arm->setpospers(personaje->getBox().getPosition());
		_arm->setlad(personaje->getlado());
		// COLISIONES con entidades
		personaje->checkearColisiones();


		if (clockBala.getElapsedTime().asSeconds() > 5)
		{
			if (personaje->isDead()) BadEnd = true;
			clockBala.restart();
		}

		// SACAR COMENTADO PARA VER LA POSICION DEL PERSONAJE
		//std::cout << personaje->getCordenadas().x;
		//std::cout << "\t\t" << personaje->getCordenadas().y << std::endl;


			// METODOS PARA LOS ENEMIGOS
		// ------------------------

		creacionEnemigos();				// CREAR ENEMIGOS EN UN TIEMPO DETERMINADO
		organizar_vector_enemigos();	// EL VECTOR ENEMIGOS SE ORGANIZA

		// METODOS PARA LAS BALAS
		// ------------------------
		cmdBalas();						// CREAR BALAS
		crear_bala_enemy();				// CREA LA BALA DE LOS ENEMIGOS

		if (personaje->isDead()==true)
		{
			BadEnd == true;
		}

		if (_score >= 8000 && band_Boss == true)
		{
			setFondo(TipoFondo::Jefe);
			this->FileSelect(this->getFondo());
			this->getMusic()->play();
			this->getMusic()->setVolume(30);
			this->getMusic()->setLoop(true);
			_Boss = new Boss(_score);
			add(_Boss);
			band_Boss = false;
			_Item = new Item(2);
			_Item->getItem().setPosition(250, 435);
			add(_Item);
			Nboss.setFont(fuente);
			Nboss.setString(NOMBRE);
			Nboss.setPosition(sf::Vector2f(350, 520));
			Nboss.setScale({ 0.8,0.8 });
		}
		if (band_Boss == false)
		{
			if (_Boss->getbool()==true)
			{
				if (reloj.getElapsedTime().asSeconds() > 1)
				{
					disp = new disparos(sf::Vector2f(_Boss->getSprite().getPosition()), 6, _Boss->getbool());
					dparo.push_back(disp);
					add(disp);
					reloj.restart();
				}
			}
			else
			{
				if (reloj.getElapsedTime().asMilliseconds()>240)
				{
					disp = new disparos(sf::Vector2f(_Boss->getSprite().getPosition().x+20, _Boss->getSprite().getPosition().y + 120), 6, _Boss->getbool());
					dparo.push_back(disp);
					add(disp);
					if (_Boss->getLife()<=50 && _Boss->getLife() >= 25)
					{
						disp = new disparos(sf::Vector2f(_Boss->getSprite().getPosition().x + 170, _Boss->getSprite().getPosition().y + 125), 6, _Boss->getbool());
						dparo.push_back(disp);
						add(disp);
					}
					reloj.restart();
				}
			}
			
			
			if (personaje->getBox().getGlobalBounds().intersects(_Item->getItem().getGlobalBounds()) && _Item->getband() == false)
			{
				personaje->getMunicion().organizarMunicion(150);
				_Item->Bye();
				remove(_Item);
			}

			if (_Boss->getSprite().getGlobalBounds().intersects(personaje->getBox().getGlobalBounds())) {

				personaje->IDaño();
				personaje->getMunicion().organizarMunicion(-4);
			}

			if (_Boss->getLife() <= 0)
			{
				GoodEnd = true;
			}
		}

		if (cont <= 3 && _score > 2000 && _score<7500 && item.getElapsedTime().asSeconds() > rand() % 120 + 60 && itemBand == true)
		{
			Rayosound.loadFromFile("recursos/Audio/Rayo.wav");
			rayo.setBuffer(Rayosound);
			rayo.setVolume(100);
			rayo.play();
			_Item = new Item(1);
			add(_Item);
			itemBand = false;
			cont++;
		}
		if (itemBand == false)
		{
			if (_Item->getItem().getPosition().y < 435)
			{
				_Item->getItem().move({ 0,8 });
			}
			else
			{
				_Item->getItem().move({ 0,0 });
			}
			if (personaje->getBox().getGlobalBounds().intersects(_Item->getItem().getGlobalBounds()) && _Item->getband() == false)
			{
				_Item->Bye();
				remove(_Item);
				itemBand = true;
				item.restart();
				personaje->setvelocidad(12.0f);
			}
			else if (clockItem.getElapsedTime().asSeconds() > 8 && _Item->getband() == false) // BORRA ITEM CADA 8 SEG
			{
				_Item->Bye();
				remove(_Item);
				itemBand = true;
				item.restart();
			}
		}

		buff << _score;
		aux = buff.str();
		buff_balas << personaje->getMunicion().getCantidadBalas();
		aux_balas = buff_balas.str();


		textoPuntos.setString(aux);
		textoPuntos.setPosition({ 125,1 });
		textoPuntos.setScale({ 0.8,0.8 });
		textoPuntos.setFillColor(letras);
		if (band_Boss == false) {

			buff_boss << _Boss->getLife();
			aux_Boss = buff_boss.str();
			textoBoss.setString(aux_Boss);
			textoBoss.setPosition({ 520,520 });
			textoBoss.setScale({ 0.8,0.8 });
			textoBoss.setFillColor(letras);
			buff_boss.str("");
			Nboss.setFillColor(letras);
		}
		PUNTOST.setFillColor(letras);


		cantbalas.setString(aux_balas);
		cantbalas.setPosition({ 265,1 });
		cantbalas.setScale({ 0.8,0.8 });
		cantbalas.setFillColor(letras);

		EscenaBase::updatee_es(lapso, _w);

		buff.str("");
		buff_balas.str("");

		//std::cout << "POSICION DE Y:" << endl;
		//std::cout << enemigo->getSprite().getPosition().y << std::endl;
	}
}

void EscenaJuego::draw_es(sf::RenderWindow& _w)
{
	_w.draw(SpFondo);
	_w.draw(municion);
	_w.draw(textoPuntos);
	_w.draw(PUNTOST);
	if (band_Boss == false) {
		_w.draw(Nboss);
		_w.draw(textoBoss);
	}
	_w.draw(cantbalas);
	EscenaBase::draw_es(_w);
}

void EscenaJuego::crear_enemy_vol(int puntos, int tipo)
{
	enemigo = new Voladores(puntos,tipo);

	vector_enemigos.push_back(enemigo);
	add(enemigo);
}

void EscenaJuego::crear_enemy_cam(int puntos, int tipo)
{

	enemigo = new Caminadores(puntos, tipo);

	vector_enemigos.push_back(enemigo);
	add(enemigo);
}
void EscenaJuego::ending()
{
	if (GoodEnd)
	{
		Gameplay::getInstancia().cambiar_Escena(new EscenaFinalBueno());
		_ScoreArchivo->setpuntos(_score);
		_ScoreArchivo->guardarpuntos();
	}
	if (BadEnd)
	{
		Gameplay::getInstancia().cambiar_Escena(new EscenaFinalMalo());
		_ScoreArchivo->setpuntos(_score);
		_ScoreArchivo->guardarpuntos();
	}

}
void EscenaJuego::cmdBalas()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > 1)
	{
		if (personaje->getMunicion().getPuedoDisparar())
		{
			crear_bala();
			personaje->getMunicion().organizarMunicion(-4);
			clock.restart();
		}
	}
}
void EscenaJuego::crear_bala()
{
	soundbuffer.loadFromFile("recursos/audio/escopeta.wav");
	escopeta.setBuffer(soundbuffer);
	escopeta.setVolume(100);
	escopeta.play();

	for (int i = 0; i < 4; i++) {
		bullet = new Bullet(sf::Vector2f(_arm->getcircle().getPosition()), sf::Vector2f(cursor->getMouse().getPosition()),
			_arm->getcircle().getOrigin(),_arm->getRotacionCirculo());
		bull.push_back(bullet);
		add(bullet);
	}
}
void EscenaJuego::crear_bala_enemy()
{
	for (int i = 0; i < vector_enemigos.size(); i++)
	{
		if ((vector_enemigos[i]->getType() == 1 || 
			vector_enemigos[i]->getType() == 2	|| 
			vector_enemigos[i]->getType() == 3	||
			vector_enemigos[i]->getType() == 4	||
			vector_enemigos[i]->getType() == 5) &&
			vector_enemigos[i]->getPuedoDisparar()==true)
		{
			if (vector_enemigos[i]->getclock().getElapsedTime().asSeconds()>2)
			{
				disp = new disparos(sf::Vector2f(vector_enemigos[i]->getSprite().getPosition()), vector_enemigos[i]->getType(), vector_enemigos[i]->getlado());
				dparo.push_back(disp);
				add(disp);
				vector_enemigos[i]->getclock().restart();
			}
		}
	}
	
}
int EscenaJuego::tipo(int _score)
{
	if (_score >= 0 && _score <= 500)
	{
		return 1;
	}
	if (_score > 500 && _score <= 1000)
	{
		return rand() % 2 + 1;
	}
	if (_score > 1000 && _score <= 1500)
	{
		return rand() % 3 + 1;
	}
	if (_score > 1500 && _score <= 2000)
	{
		return rand() % 4 + 1;
	}
	if (_score >= 2000 && _score <= 2500)
	{
		return rand() % 5 + 1;
	}
	if (_score >= 2500 && _score <= 8000)
	{
		return rand() % 6 + 1;
	}
}

void EscenaJuego::creacionEnemigos()
{
	if (_score<2500)
	{
		seg = 2;
	}
	else
	{
		seg = 1;
	}
	if (_score < 8000) {

		if (timer.getElapsedTime().asSeconds() > seg) {	//CAMBIAR DEPENDIENDO LOS PUNTOS

			crear_enemy_vol(_score, tipode);

			timer.restart();
		}

		//crear nuevo enemigo en un determinado tiempo (caminadores)
		if (timer2.getElapsedTime().asSeconds() > seg)
		{
			if (tipode != 6)
			{
				crear_enemy_cam(_score, tipode);
				timer2.restart();
			}
		}
	}
}

int _it = 0;

void EscenaJuego::organizar_vector_enemigos()
{
	//std::cout << "Balas en total: " << bull.size() << std::endl;
	//std::cout << "Enemigues en total: " << vector_enemigos.size() << std::endl;

	// Eliminar balas 
	for (int i = 0; i < bull.size(); i++)
	{
		balafuera(*bull[i]);
		balaChoque(*bull[i]);
		//std::cout << i << ". X: " << bull[i]->getBullet().getPosition().x << "\t\t";
		//std::cout << "Y: " << bull[i]->getBullet().getPosition().y << std::endl;;
	}
	
	// Eliminar balas Enemigo 
	for (int i = 0; i < dparo.size(); i++)
	{
		balaEnemigo(*dparo[i]);
	}

	// Eliminar enemigos
	for (int i = 0; i < vector_enemigos.size(); i++)
	{
		enemigoFuera(*vector_enemigos[i]);
	}

	//std::cout << "--------------------------------- " << std::endl;

	while (_BalasFalse != 0)		// Ya está, se borran correctamente al salir de la pantalla ---------------------	:) 
	{
		if (!bull[_it]->getestado())
		{
			if (!bull.empty() && _it <= bull.size())
			{
				bull.erase(next(begin(bull), +_it));
				_BalasFalse--;
				_it = 0;
			}
		}
		else _it++;
	}

	_it = 0;

	while (_EnemigosFalse != 0)
	{
		if (!vector_enemigos[_it]->getEstado())
		{
			if (!vector_enemigos.empty() && _it <= vector_enemigos.size())
			{
				vector_enemigos.erase(next(begin(vector_enemigos), +_it));
				_EnemigosFalse--;
				_it = 0;
			}
		}
		else _it++;
	}

	_it = 0;

	
	while (_Balas_False_enemy != 0) //BALAS DE ENEMIGOS CONTROLO LOS ESTADOS
	{
		if (!dparo[_it]->getestado())
		{
			if (!dparo.empty() && _it <= dparo.size())
			{
				dparo.erase(next(begin(dparo), +_it));
				_Balas_False_enemy--;
				_it = 0;
			}
		}
		else _it++;
	}
	_it = 0;
}


void EscenaJuego::balafuera(Bullet& bal)
{
	//borra afuera de la ventana -- ok
	if (bal.getBullet().getPosition().y < -10 ||
		bal.getBullet().getPosition().y > 600 ||
		bal.getBullet().getPosition().x > 850 ||
		bal.getBullet().getPosition().x < -10)
	{

		bal.cambiarestado();
		_BalasFalse++;
	}
}

void EscenaJuego::balaChoque(Bullet& bal)
{
	int balasSoltadas = 0;
	int posicion = 0;

	for (const auto enemigo : vector_enemigos)
	{
		if (enemigo->colision_bala(bal))
		{
			// Borrado de balas
			bal.cambiarestado();
			_BalasFalse++;

			// ME PROPORCIONA UN SCORE
			_score += enemigo->getScore();

			// Y UNA CANTIDAD DE BALAS
			balasSoltadas = enemigo->getbalasSoltadas();

			// ORGANIZO LA MUNICION DEL PERSONAJE
			personaje->getMunicion().organizarMunicion(balasSoltadas);

			// --------------------------------------------------- /
			//				ORGANIZO LO QUE ES EL VECTOR

			// PREGUNTO SI EL VECTOR NO ESTA VACIO Y SI LA POSICION ACTUAL ES MENOR O IGUAL AL TAMAÑO DEL VECTOR

			if ((!vector_enemigos.empty()) && (posicion <= vector_enemigos.size()))
			{
				// SI SE CUMPLE
				vector_enemigos.erase(vector_enemigos.begin() + posicion);
				enemigo->muerto();
				//posicion--;
			}
		}
		else posicion++;
	}
	//colision con el boss y su desenlace
	if (!band_Boss)
	{
		if (_Boss->colision_bala(bal))
		{
			_Boss->setLife(rand() % 2 + 1);

			bal.cambiarestado();
			_BalasFalse++;
			_score += _Boss->getScore();

		}
	}
}

void EscenaJuego::balaEnemigo(disparos& bal)
{
	//borra afuera de la ventana -- ok
	if (bal.getShotBull().getPosition().y < -10 ||
		bal.getShotBull().getPosition().y > 600 ||
		bal.getShotBull().getPosition().x > 850 ||
		bal.getShotBull().getPosition().x < -10)
	{

		bal.cambiarestado();
		_Balas_False_enemy++;
	}

	//enemigo choca con personaje
	if (_score<3000)
	{
		if (bal.getShotBull().getGlobalBounds().intersects(personaje->getBox().getGlobalBounds()))
		{
			personaje->IDaño();
			bal.cambiarestado();
			_Balas_False_enemy++;
			personaje->getMunicion().organizarMunicion(-5);
		}
	}
	else
	{
		if (bal.getShotBull().getGlobalBounds().intersects(personaje->getBox().getGlobalBounds()))
		{
			personaje->IDaño();
			bal.cambiarestado();
			_Balas_False_enemy++;
			if (_score>=8000)
			{
				personaje->getMunicion().organizarMunicion(-4);
			}
			else
			{
				personaje->getMunicion().organizarMunicion(-10);
			}
			
		}
	}
	

	/*cout << "-------------------------------------" << endl;
	cout << dparo.size()endl;*/
}

void EscenaJuego::enemigoFuera(Enemigo& enemigo)
{

	if (enemigo.getSprite().getPosition().y < -50 ||
		enemigo.getSprite().getPosition().y > 600 ||
		enemigo.getSprite().getPosition().x > 850 ||
		enemigo.getSprite().getPosition().x < -50)
	{

		enemigo.muerto();
		_EnemigosFalse++;
	}
	//enemigo choca con personaje
	if (_score<3000)
	{
		if (enemigo.getSprite().getGlobalBounds().intersects(personaje->getBox().getGlobalBounds()))
		{
			personaje->IDaño();
			enemigo.muerto();
			_EnemigosFalse++;
			personaje->getMunicion().organizarMunicion(-5);
		}
	}
	else
	{	
		if (enemigo.getSprite().getGlobalBounds().intersects(personaje->getBox().getGlobalBounds()))
		{
			personaje->IDaño();
			enemigo.muerto();
			_EnemigosFalse++;
			if (_score >= 8000)
			{
				personaje->getMunicion().organizarMunicion(-4);
			}
			else
			{
				personaje->getMunicion().organizarMunicion(-10);
			}
		}
		
	}
	

}



EscenaJuego::~EscenaJuego()
{
	bull.~vector();
	vector_enemigos.~vector();
	delMusic();
	if (itemBand == false)
	{
		_Item->~Item();
	}
}
