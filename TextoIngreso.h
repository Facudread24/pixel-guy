#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
private:
	sf::Text textbox;
	std::ostringstream texto;
	bool isSelected = false;
	bool hasLimit = false;
	bool _Enter = false;
	int limit;
	
	void inputLogic(int charTyped) {

		std::string auxString;
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		{
			texto << static_cast<char>(charTyped);

			auxString = texto.str();

			for (int i = 0; i < strlen(auxString.c_str()); i++)
			{
				if (auxString[i] >= 97 && auxString[i] <= 122)
				{
					auxString[i] = auxString[i] - 32;
				}
			}

			texto.str("");
			texto << auxString;
		}
		else
		{
			if (charTyped == DELETE_KEY)
			{
				if (texto.str().length() > 0)
				{
					borrarultimoChar();
				}
			}

		}
		textbox.setString(texto.str() + "_");

	}
	void borrarultimoChar()
	{
		std::string t = texto.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		texto.str("");
		texto << newT;

		textbox.setString(texto.str());
	}

public:
	TextBox();
	TextBox(int size, sf::Color Color, bool sel);

	void setTexto(std::string texto);

	void setFuente(sf::Font& fuente) { textbox.setFont(fuente); }
	void setPosition(sf::Vector2f pos) { textbox.setPosition(pos); }
	void setLimit(bool ToF) { hasLimit = ToF; }
	void drawTo(sf::RenderWindow& window) { window.draw(textbox); }
	void typedOn(sf::Event* input);
	void setEnterFalse();
	void setLimit(bool ToF, int lim);
	void setSelected(bool sel);


	std::string getTexto();
};



