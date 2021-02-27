#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "entidad.h"
class disparos : public Entidad
{
private:
	sf::RectangleShape ShotBull;
	sf::Vector2f speedX;
	sf::Vector2f UbicacionXY;

	sf::Clock reloj;
	int tipo_E;
	bool _estado;
	bool enemylado;
public:
	disparos(sf::Vector2f PosEne,int tipo,bool lado);
	void velocidad(int tipo);
	void updatee_e(float lapso) override;
	void draw_enty(sf::RenderWindow& w) override;
	void cambiarestado();

	sf::Vector2f getUbi();

	bool getestado();
	sf::RectangleShape& getShotBull();
	
	~disparos();
};

