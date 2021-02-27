#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entidad.h"
#include "MunicionPersonaje.h"

enum ESTADOS {
QUIETO,
QUIETO_IZQ,
QUIETO_DER,
CAMINANDO_IZQ,
CAMINANDO_DER,
SALTO,
SALTO_DIAG_DER,
SALTO_DIAG_IZQ,
APRETAR_GATILLO

};

class Personaje: public Entidad{
private:
	sf::Texture _texturaP;
	sf::Sprite _spriteP;
	ESTADOS _estado;
	float _sp_vel = 6.0f;
	float _vel_salto = 0;
	sf::Vector2i division;
	sf::Vector2i frame;
	int _fps_sprite;
	sf::RectangleShape box;
	MunicionPersonaje *municion;

	//BOOLEANOS QUE SIRVEN PARA EL MOVIMIENTO DEL PERSONAJE 
	bool moverseIzq;
	bool moverseDer;

	bool lado = false;

	sf::Clock clock;

	sf::SoundBuffer soundbuffer;
	sf::Sound paso;
	sf::SoundBuffer sounddaño;
	sf::Sound daño;
public:
	//CONSTRUCTOR
	Personaje(const sf::Vector2f& pos);
	
	//METODO QUE SIRVE PARA VERIFICAR SI EXISTE ALGUNA COLISION CON ENEMIGOS O CON LA VENTANA
	void checkearColisiones();

	void cmd();
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& _w) override;
	void set_frame(sf::Sprite& pers);
	void setvelocidad(float velocidad);
	MunicionPersonaje& getMunicion();

	sf::Sprite& getDrawn();
	sf::RectangleShape& getBox();
	const sf::Vector2f& getCordenadas();

	void IDaño();
	bool isDead();
	bool getlado();
};