#include "MunicionPersonaje.h"
#include <iostream>

MunicionPersonaje::MunicionPersonaje(int cantidad_balas_iniciales = 50)
{
    cantidad_balas = cantidad_balas_iniciales;
    puedo_disparar = true;
}

int MunicionPersonaje::getCantidadBalas()
{
    return cantidad_balas;
}

bool MunicionPersonaje::getPuedoDisparar()
{
    return puedo_disparar;
}

void MunicionPersonaje::organizarMunicion(int balas)
{
    if (cantidad_balas + balas <= 0)
    {
        cantidad_balas = 0;
        puedo_disparar = false;
    }
    else if(cantidad_balas + balas < 4)
    {
            cantidad_balas = cantidad_balas + balas;
            puedo_disparar = false;
    }
    else {
        cantidad_balas += balas;
        puedo_disparar = true;
    }
}
