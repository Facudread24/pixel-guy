#include "EscenaPuntuaciones.h"
#include "Score.h"
#include "Gameplay.h"
#include "EscenaMenuInicial.h"
#include "Tipos_Fondo.h"
#include <iostream>

const std::string _stringvolver = ">      VOLVER";

void cargarVector(Score* v)
{
	int pos = 0;
	int i = 0;
	Score a;

	while (a.leerpuntos(pos++))
	{
		v[i] = a;
		i++;
	}
}

// A utility function to swap two elements  
void swap(Score* a, Score* b)
{
	Score t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
	the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
	to left of pivot and all greater elements to right
	of pivot */
int partition(Score arr[], int low, int high)
{
	int pivot = arr[high].getpuntos(); // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (arr[j].getpuntos() > pivot)
		{
			i++; // increment index of smaller element  
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
	arr[] --> Array to be sorted,
	low --> Starting index,
	high --> Ending index */
void quickSort(Score arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Function to print an array */
void printArray(Score arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		std::cout << arr[i].getpuntos() << " ";
	std::cout << std::endl;
}


void cargaScoreAlto(Score* v, int* Maximo)
{
	int n = contarRegistros();
	quickSort(v, 0, n - 1);

	//std::cout << "Sorted array: \n";

	//printArray(v, n);
	for (int i = 0; i < 5; i++) Maximo[i] = v[i].getpuntos();

}

const char* buscarNombre(int puntosComparacion)
{
	Score* _auxScore;
	_auxScore = new Score;
	FILE* pf;
	int pos = 0;
	pf = fopen("puntos.dat", "rb");
	if (pf == NULL) {
		//std::cout << "Error al abrir el archivo puntos.dat" << std::endl;
		return "XXXX";
	}
	while (_auxScore->leerpuntos(pos++))
	{
		if (_auxScore->getpuntos() == puntosComparacion)
		{
			fclose(pf);
			return _auxScore->getNombre();
		}
	}
	//std::cout << "Error al encontrar el nombre en el archivo puntos.dat" << std::endl;
	fclose(pf);
	delete _auxScore;
	return "XXXX";

}


void asignarArray(sf::Text* Nombre, sf::Text* Puntuacion)
{
	int _cantidadRegistros = contarRegistros();

	// CREO VECTORES DINAMICOS PARA ADMINISTRAR LA MEMORIA
	int* ScoreCincoMasAltos;
	Score* _arrayScore;

	ScoreCincoMasAltos = new int[5];

	if (_cantidadRegistros != 0)
	{
		_arrayScore = new Score[_cantidadRegistros];

		for (int i = 0; i < _cantidadRegistros; i++)
		{
			_arrayScore[i].setpuntos(0);
		}


		int pos = 0;

		std::cout << _cantidadRegistros << std::endl;
		// -----------------------------------------------

		// EN ESTE ARRAY LE ASIGNO A CADA POSICION 0 PARA QUE NO TENGA BASURA
		for (int i = 0; i < 5; i++) ScoreCincoMasAltos[i] = 0;

		// CARGO EL ARCHIVO DE SCORE EN MEMORIA

		cargarVector(_arrayScore);

		// METODO PARA ORDENAR LOS PUNTAJES MAS ALTOS Y ORDENARLOS
		cargaScoreAlto(_arrayScore, ScoreCincoMasAltos);

		// POR ULTIMO LE ASIGNO A LOS TEXTOS LOS VALORES DE LAS PUNTUACIONES Y VECTORES

		if (_cantidadRegistros >= 5)
		{
			for (int i = 0; i < 5; i++)
			{
				// ASIGNAR NOMBRES
				Nombre[i].setString(buscarNombre(ScoreCincoMasAltos[i]));
				// ASIGNAR PUNTUACIONES
				Puntuacion[i].setString(std::to_string(ScoreCincoMasAltos[i]));

				// MOSTRADO POR CONSOLA
				//std::cout << ScoreCincoMasAltos[i] << std::endl;
				//std::cout << "-----------------------------" << std::endl;
			}
		}
		else
		{
			while (pos != _cantidadRegistros)
			{
				// ASIGNAR NOMBRES
				Nombre[pos].setString(buscarNombre(ScoreCincoMasAltos[pos]));
				// ASIGNAR PUNTUACIONES
				Puntuacion[pos].setString(std::to_string(ScoreCincoMasAltos[pos]));

				// MOSTRADO POR CONSOLA
				//std::cout << ScoreCincoMasAltos[i] << std::endl;
				//std::cout << "-----------------------------" << std::endl;
				pos++;
			}
		}

		delete[] _arrayScore;
	}
	else
	{
		for (int i = 0; i < 5; i++) ScoreCincoMasAltos[i] = 0;
	}
	delete[] ScoreCincoMasAltos;
}

EscenaPuntuaciones::EscenaPuntuaciones()
{
	// ---- INICIALIZACION DE PUNTEROS ------------------

	_TexturaFondo = new sf::Texture();
	_SpriteFondo = new sf::Sprite();
	_SeguimientoMouse = new sf::CircleShape();
	_BordeVentana = new sf::RectangleShape();

	_TextoVolver = new sf::Text;
	_FuenteTexto = new sf::Font;

	_ArrayTitulos = new sf::Text[3];
	_ArrayNombres = new sf::Text[5];
	_ArrayPuntuaciones = new sf::Text[5];

	CantidadRegistros = new int;

	// ------- FIN DE INICIALIZACION ---------------------

	int pos_y = 150;
	int pos_x = 350;

	_SeguimientoMouse->setRadius(5);
	_SeguimientoMouse->setFillColor(sf::Color::Transparent);

	_BordeVentana->setOutlineColor(sf::Color::White);
	_BordeVentana->setOutlineThickness(1);
	_BordeVentana->setFillColor(sf::Color::Transparent);
	_BordeVentana->setSize({ 860, 580 });
	_BordeVentana->setPosition(8.0f, 8.0f);

	_TexturaFondo->loadFromFile("recursos/FondoPuntuacion.png");
	_SpriteFondo->setTexture(*_TexturaFondo);
	_SpriteFondo->setScale(1.41f, 1.41f);


	_FuenteTexto->loadFromFile("recursos/fuentes/LLPIXEL3.ttf");

	//*CantidadRegistros = contarRegistros();

	for (int i = 0; i < 5; i++)
	{
		_ArrayNombres[i].setCharacterSize(18);
		_ArrayPuntuaciones[i].setCharacterSize(18);

		_ArrayNombres[i].setFillColor(sf::Color::White);
		_ArrayPuntuaciones[i].setFillColor(sf::Color::White);

		_ArrayNombres[i].setFont(*_FuenteTexto);
		_ArrayPuntuaciones[i].setFont(*_FuenteTexto);

		_ArrayNombres[i].setPosition({ (float)pos_x, (float)pos_y });
		_ArrayPuntuaciones[i].setPosition({ (float)pos_x + 100, (float)pos_y });

		_ArrayNombres[i].setString("XXXX");
		_ArrayPuntuaciones[i].setString("0");

		pos_y += 60;
	}

	asignarArray(_ArrayNombres, _ArrayPuntuaciones);

	_TextoVolver->setFillColor(sf::Color::White);
	_TextoVolver->setCharacterSize(20);
	_TextoVolver->setFont(*_FuenteTexto);
	_TextoVolver->setString(_stringvolver);
	_TextoVolver->setPosition({ 20, 550 });

	for (int i = 0; i < 3; i++)
	{
		_ArrayTitulos[i].setFillColor(sf::Color::White);
		_ArrayTitulos[i].setCharacterSize(20);
		_ArrayTitulos[i].setFont(*_FuenteTexto);
	}

	_ArrayTitulos[0].setPosition(250, 35);
	_ArrayTitulos[0].setCharacterSize(30);
	_ArrayTitulos[0].setString("TABLA DE PUNTUACIONES");

	_ArrayTitulos[1].setPosition(330, 100);
	_ArrayTitulos[1].setString("NOMBRE");

	_ArrayTitulos[2].setPosition(430, 100);
	_ArrayTitulos[2].setString("PUNTAJE");
	
	newMusic();
	setFondo(TipoFondo::EscenaPuntuaciones);
	this->FileSelect(this->getFondo());
	this->getMusic()->play();
	this->getMusic()->setVolume(50);
	this->getMusic()->setLoop(true);
}

void EscenaPuntuaciones::updatee_es(float lapso, sf::RenderWindow& _w)
{
	sf::Mouse _m;

	// ----------- ESTO ES PARA EL CURSOR ----------------------

	_SeguimientoMouse->setPosition((float)_m.getPosition(_w).x, (float)_m.getPosition(_w).y);

	if (_TextoVolver->getGlobalBounds().intersects(_SeguimientoMouse->getGlobalBounds()))
	{
		_TextoVolver->setFillColor(sf::Color(90, 90, 90));
		if (_m.isButtonPressed(sf::Mouse::Left) && delay.getElapsedTime().asSeconds() > 0.5)
		{
			delay.restart();
			getMusic()->stop();
			Gameplay::getInstancia().cambiar_Escena(new EscenaMenuInicial);
		}
	}

	else _TextoVolver->setFillColor(sf::Color::White);

	// ---------- FIN DEL FUNCIONAMIENTO DEL CURSOR -----------------

}

void EscenaPuntuaciones::draw_es(sf::RenderWindow& _w)
{
	_w.draw(*_SpriteFondo);

	for (int i = 0; i < 3; i++)
	{
		_w.draw(_ArrayTitulos[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		_w.draw(_ArrayNombres[i]);
		_w.draw(_ArrayPuntuaciones[i]);
	}
	_w.draw(*_TextoVolver);
	_w.draw(*_BordeVentana);
}

EscenaPuntuaciones::~EscenaPuntuaciones()
{
	// std::cout << "Me borre" << std::endl;
	// OK
	delete CantidadRegistros;
	delete _SeguimientoMouse;

	delete _TexturaFondo;
	delete _SpriteFondo;
	delete _BordeVentana;

	delete _TextoVolver;
	delete _FuenteTexto;
	delete[] _ArrayTitulos;
	delete[] _ArrayNombres;
	delete[] _ArrayPuntuaciones;
	delMusic();
}
