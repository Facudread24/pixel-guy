#include "Score.h"

int contarRegistros()
{
	FILE* p;
	p = fopen("Puntos.dat", "rb");
	if (p == NULL) {
		return 0;
	}
	int cant;
	Score aux;
	fseek(p, 0, 2);
	//0 INICIO SEEK_SET
	//1 cursor SEEL_CUT
	//2 FIN SEEK_END
	cant = ftell(p);
	fclose(p);


	return cant / sizeof(aux);
}

Score::Score()
{
	_puntos = 0;
	setNombre("NN");
}

void Score::guardarpuntos()
{
	FILE *p;
	p = fopen("Puntos.dat", "ab");
	if (p==NULL)
	{
		return;
	}
	fwrite(this , sizeof *this, 1, p);
	fclose(p);
}


bool Score::leerpuntos(int pos)
{
	FILE* p;
	p = fopen("puntos.dat", "rb");
	if (p == NULL)
	{
		return false;
	}
	fseek(p, sizeof * this * pos, 0);
	bool leyo = fread(this , sizeof *this, 1, p);
	fclose(p);
	return leyo;
}

void Score::setpuntos(int puntos)
{
	_puntos = puntos;
}

void Score::setNombre(const char* nombre)
{
	strcpy(_nombre, nombre);
}

void Score::SobreEscribir(int _pos)
{
	FILE* p;
	p = fopen("puntos.dat", "rb+");
	if (p == NULL)
	{
		return;
	}
	fseek(p, sizeof * this * _pos, 0);
	fwrite(this, sizeof * this, 1, p);

	fclose(p);
}

int Score::getpuntos()
{
	return _puntos;
}

const char* Score::getNombre()
{
	return _nombre;
}

