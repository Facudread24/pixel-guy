#include "Item.h"
Item::Item(int tipo) {
	desaparecer = false;
	if (tipo == 1)
	{
		textitem.loadFromFile("recursos/rayo.png");
		item.setTexture(textitem);
		item.setPosition(sf::Vector2f(rand() % 800, -1));
		_Tipo = 1;
	}
	else {
		textitem.loadFromFile("recursos/LogoMuni2.png");
		item.setTexture(textitem);
		item.setScale({ 0.10,0.10 });
		_Tipo = 2;
	}

}
void Item::updatee_e(float lapso)
{


}

void Item::draw_enty(sf::RenderWindow& _w)
{
	if (desaparecer!=true)
	{
		_w.draw(item);
	}	
}

void Item::Bye()
{
	desaparecer = true;
}

sf::Sprite& Item::getItem()
{
	return item;
}

bool Item::getband()
{
	return desaparecer;
}

int Item::getTipo()
{
	return _Tipo;
}

Item::~Item()
{

}
