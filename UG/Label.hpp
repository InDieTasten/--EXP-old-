#ifndef _Label_hpp_
#define _Label_hpp_

#include <string.h>
#include "DataBank.hpp"

class Label
{
	//MEMBERS
private:
	sf::Text displayText;
public:
	int X;
	int Y;
	int Height;
	int Width;
	std::string DisplayText;

	//CONSTRUCTORS

	//DESTRUCTORS

	//METHODS
	void Setup();
	void Update(DataBank* _dataLink, int _x, int _y);
	void Render(DataBank* _dataLink);
	void handleEvent(sf::Event* _event);
};

#endif
