#ifndef _Button_hpp_
#define _Button_hpp_

#include <string.h>
#include <math.h>
#include "DataBank.hpp"

class Button
{
	//MEMBERS
private:
	sf::Shape rect;
	sf::String displayText;
	bool mouseHover;
public:
	int X;
	int Y;
	int Height;
	int Width;

	std::string Text;
	bool isActive;

	//CONSTRUCTORS

	//DESTRUCTORS

	//METHODS
	void Setup();
	void Update(DataBank* _dataLink, int _x, int _y);
	void Render(DataBank* _dataLink);
	void handleEvent(DataBank* datalink, sf::Event* _event, const sf::Input* _input, int _x, int _y, std::string _id);
};

#endif
