#include "EscenaBase.h"
#include "Entidad.h"
#include <iostream>
using namespace std;
EscenaBase::EscenaBase()
{
}

void EscenaBase::updatee_es(float lapso, sf::RenderWindow& _w)
{
	for (auto e : entidades) {
		e->updatee_e(lapso);
	}
	
	//eliminar
	for (auto b : borrar) {
		auto it = find(entidades.begin(), entidades.end(), b);
		if (it != entidades.end()) {
			entidades.erase(it);
		}
	}
}

void EscenaBase::draw_es(sf::RenderWindow& _w)
{
	for (auto e : entidades)
	{
		e->draw_enty(_w);
	}
	
}

void EscenaBase::add(Entidad* e)
{
	entidades.push_back(e);
}

void EscenaBase::remove(Entidad* e)
{
	borrar.push_back(e);
}

void EscenaBase::process_event(const sf::Event& e)
{


}

EscenaBase::~EscenaBase()
{
}
void EscenaBase::setFondo(TipoFondo fondo) {
	tipo = fondo;
}

void EscenaBase::newMusic() {
	musica = new sf::Music;
}
void EscenaBase::delMusic() {
	delete musica;
}
void EscenaBase::FileSelect(TipoFondo fondo) {
	switch (fondo) {
	case TipoFondo::Menu:
		getMusic()->openFromFile("recursos/Audio/menUp.wav");
		break;
	case TipoFondo::EscenaJuego:
		getMusic()->openFromFile("recursos/Audio/escenaJuego.wav");
		break;
	case TipoFondo::EscenaGameOverGood:
		getMusic()->openFromFile("recursos/Audio/finalbueno.wav");
		break;
	case TipoFondo::EscenaGameOverbad:
		getMusic()->openFromFile("recursos/Audio/finalmalo.wav");
		break;
	case TipoFondo::EscenaPuntuaciones:
		getMusic()->openFromFile("recursos/Audio/puntuaciones.wav");
		break;
	case TipoFondo::Escenacontroles:
		getMusic()->openFromFile("recursos/Audio/escenacontrol.wav");
		break;
	case TipoFondo::Jefe:
		getMusic()->openFromFile("recursos/Audio/boss.wav");
		break;
	}
}