#pragma once
class MunicionPersonaje
{
private:
	int cantidad_balas;
	bool puedo_disparar;
public:
	MunicionPersonaje(int cantidad_balas_iniciales);

	int getCantidadBalas();
	bool getPuedoDisparar();
	void organizarMunicion(int balas);
};

