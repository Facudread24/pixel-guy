#pragma once
#include "entidad.h"

int contarRegistros();

class Score
{
private:
	
	int _puntos;
	char _nombre[5];
public:

	Score();
	
	void guardarpuntos();
	bool leerpuntos(int pos);
	void setNombre(const char* nombre);
	void setpuntos(int puntos);
	Score operator= (Score aux)
	{
		_puntos = aux.getpuntos();
		strcpy(_nombre, aux.getNombre());
		return *this;
	}
	void SobreEscribir(int);
	int getpuntos();

	const char* getNombre();

};

