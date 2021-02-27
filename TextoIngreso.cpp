#include "TextoIngreso.h"
#include <string>

TextBox::TextBox()
{
	limit = 4;
	textbox.setCharacterSize(18);
	textbox.setFillColor(sf::Color(127, 127, 127, 255));
	textbox.setString("_");
}

TextBox::TextBox(int size, sf::Color Color, bool sel)
{
	limit = 4;
	textbox.setCharacterSize(size);
	textbox.setFillColor(Color);
	isSelected = sel;
	if (sel)
	{
		textbox.setString("_");
	}
	else
	{
		textbox.setString("");
	}
}

void TextBox::setTexto(std::string texto)
{
	sf::String aux = texto;
	textbox.setString(aux);
}

void TextBox::setLimit(bool ToF, int lim)
{
	hasLimit = ToF;
	limit = lim - 1;
}

void TextBox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		std::string t = texto.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
	else
	{
		textbox.setString(texto.str() + "_");
	}
}


void TextBox::typedOn(sf::Event* input)
{
	if (isSelected)
	{
		int charTyped = input->text.unicode;
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				if (texto.str().length() <= limit)
				{
					inputLogic(charTyped);
				}
				else if (texto.str().length() > limit && charTyped == DELETE_KEY) borrarultimoChar();
			}
			else
			{
				inputLogic(charTyped);
			}
		}
	}
}

void TextBox::setEnterFalse()
{
	_Enter = false;
}

std::string TextBox::getTexto()
{
	return textbox.getString();
}


