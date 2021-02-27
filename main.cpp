#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include "EscenaMenuInicial.h"
#include "EscenaFinalBueno.h"
#include "EscenaFinalMalo.h"
#include <time.h>
#include <iostream>

int main()
{
    //semilla random
    srand(time(static_cast<time_t*>(0)));
    //primer escena
    EscenaBase* escena = new EscenaMenuInicial();
    //pantalla y escena
    Gameplay &g = Gameplay::create(sf::VideoMode(880, 600), escena, "PIXEL GUY");
    //empieza la cola de eventos
    g.run();

    return 0;
}