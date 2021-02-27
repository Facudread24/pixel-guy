#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "entidad.h"
#include <vector>
#include "Tipos_Fondo.h"
class EscenaBase
{
private:
	std::vector <Entidad*> entidades;
	std::vector <Entidad*> borrar;

	sf::Music* musica;
	TipoFondo tipo;
public:
	//CONSTRUCTOR DE ESCENA
	EscenaBase();
	// ACTUALIZA ESCENA
	virtual void updatee_es(float lapso, sf::RenderWindow& _w);
	// DIBUJA ESCENA
	virtual void draw_es(sf::RenderWindow& _w);
	// DIBUJA UN OBJETO DE LA ESCENA
	void add(Entidad* e);
	// ELIMINA UN OBJETO DE LA ESCENA
	void remove(Entidad* e);

	virtual void process_event(const sf::Event& e);
	virtual ~EscenaBase();


	//Musica
	sf::Music* getMusic() { return musica; }
	// musica=new sf::Music;
	void newMusic();
	// delete(musica);
	void delMusic();
	//Depende el fondo que tenga manda el tema;
	void FileSelect(TipoFondo fondo);

	//Fondo
	TipoFondo getFondo() { return tipo; }
	void setFondo(TipoFondo fondo);

};

