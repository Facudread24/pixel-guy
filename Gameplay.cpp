#include "Gameplay.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "EscenaBase.h"
#include "EscenaJuego.h"
#include <iostream>
using namespace std;
Gameplay* Gameplay::instancia = nullptr;
Gameplay::Gameplay() {}

Gameplay& Gameplay::create(const sf::VideoMode& videoMode, EscenaBase* scene, const std::string& nombre)
{
    if (instancia) {
    }
        else 
        {
            Gameplay &g = getInstancia();
            g._window.create(videoMode, nombre, sf::Style::Close);
            g.actual = scene;
            g.siguiente = nullptr;
            g._window.setFramerateLimit(60);
            g.clock.restart();
            g._window.setMouseCursorVisible(true);
            
        }
    return getInstancia();

}
//creo una instancia para el momento del juego
Gameplay& Gameplay::getInstancia()
{
    if (!instancia) {
        instancia = new Gameplay;
    }
    
    return *instancia;
}
void Gameplay::run()
{
    //GAME LOOP
    while (_window.isOpen() && actual != nullptr) {
        sf::Event e;
        while (_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                _window.close();
            }
            else if(e.type == sf::Event::TextEntered) {
                actual->process_event(e);
            }
        }
    
        //ACTUALIZAR
        update_game();

        //DIBUJAR
        draw_game();

        //controlo si es la ultima escena
        if (siguiente != nullptr) {
          
            actual->~EscenaBase();
            delete actual;

            actual = siguiente;
            siguiente = nullptr;
        }
    }
 
}

void Gameplay::processEvents()
{

}

void Gameplay::update_game()
{
    actual->updatee_es(clock.getElapsedTime().asSeconds(), _window);
    clock.restart();
}

void Gameplay::draw_game()
{
    _window.clear();
    actual->draw_es(_window);
    _window.display();
}

void Gameplay::cambiar_Escena(EscenaBase* escena)
{
    siguiente = escena;
}

