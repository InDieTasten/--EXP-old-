#ifndef _CodeBox_hpp_
#define _CodeBox_hpp_

#include <string.h>
#include "DataBank.hpp"
#include <iostream>
#include <list>

class CodeBox
{
	//MEMBERS
private:
	sf::String text1;
	char tmp;
	sf::Shape rect;
	sf::Shape c;
	int ViewY;
	int ViewX;
	int cursor_line;
	int cursor_char;
public:
	//std::string text;
	std::list<std::string> text;
	int X;
	int Y;
	int Height;
	int Width;
	float Textsize;
	bool isActive;
	int enter;

	//CONSTRUCTORS

	//DESTRUCTORS

	//METHODS
	void Setup();

	void Update(DataBank* _dataLink, int _x, int _y);

	void Render(DataBank* _dataLink);
	void handleEvent(sf::Event* _event, const sf::Input* _input, int _x, int _y);

	char getInput(int Type,sf::Event* _event);

};

#endif