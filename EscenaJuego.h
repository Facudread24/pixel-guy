#pragma once
#include "Mouse.h"
#include "EscenaBase.h"
#include "Personaje.h"
#include "Bullet.h"
#include "Enemigo.h"
#include "Caminadores.h"
#include "Voladores.h"
#include "Boss.h"
#include <vector>
#include "Item.h"
#include "Score.h"
#include "Arma.h"
#include "disparos.h"
class EscenaJuego: public EscenaBase
{
private:
	Voladores* volrs;
	Caminadores* camin;
	Personaje* personaje;
	Mouse* cursor;
	Bullet* bullet;
	Enemigo* enemigo;
	Boss* _Boss;
	Item* _Item;
	Arma* _arm;
	disparos* disp;

	std::vector<Bullet*>bull;
	std::vector<disparos*>dparo;
	std::vector<Enemigo*>vector_enemigos;
	Score* _ScoreArchivo;

	sf::Clock timer; //controla cada cuanto aparecer un enemigo vol 
	sf::Clock timer2; //controla cada cuanto aparecer un enemigo cam
	sf::Clock item; // aparicion de item
	sf::Clock clockItem; // borro de item
	sf::Clock clock; // disparo personaje
	sf::Clock clockBala; //cada cunato sale
	sf::Clock reloj; // disparo boss
	sf::Clock RelojPausa; // reloj de pausa

	sf::Texture TextFondo;// textura fondo mapa
	sf::Sprite SpFondo; // fondo sprite

	sf::Text PUNTOST;
	sf::Text Nboss;
	sf::Text textoPuntos;
	sf::Text cantbalas;
	sf::Text textoBoss;
	sf::Font fuente;
	sf::Texture iconoMuni;
	sf::Sprite municion;
	sf::Color letras;

	//musica
	sf::SoundBuffer soundbuffer;
	sf::Sound escopeta;
	sf::SoundBuffer Rayosound;
	sf::Sound rayo;

	int _score;
	int tipode;
	int cont=0;
	int _CantidadEnemigos;
	bool itemBand;
	bool band_Boss;

	bool GoodEnd;
	bool BadEnd;
public:

	EscenaJuego();
	void updatee_es(float lapso, sf::RenderWindow& _w);
	void draw_es(sf::RenderWindow& _w);

	void crear_enemy_vol(int puntos, int tipo);
	void crear_enemy_cam(int puntos, int tipo);
	void crear_bala();
	void crear_bala_enemy();
	int tipo(int _score);
	void organizar_vector_enemigos();

	void balafuera(Bullet& bal);
	void balaChoque(Bullet& bal);
	void balaEnemigo(disparos& bal);
	void enemigoFuera(Enemigo& enemigo);

	void cmdBalas();
	void creacionEnemigos();
	void ending();

	~EscenaJuego();
};



