#pragma once
#include "entidad.h"

class Item: public Entidad
{
private:
	sf::Sprite item;
	sf::Texture textitem;
	bool desaparecer;
	int _Tipo;
public:
	Item(int tipo);
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& _w) override;
	void Bye();
	sf::Sprite& getItem();
	bool getband();
	int getTipo();
	~Item();
};

