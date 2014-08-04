#ifndef _TextBox_hpp_
#define _TextBox_hpp_

#include <string.h>
#include "DataBank.hpp"


class TextBox
{
	//MEMBERS
private:
	sf::RectangleShape rect;
	char tmp;
	sf::Text text1;

public:
	std::string text;
	//std::list<sf::Text> text1;
	int X;
	int Y;
	int Height;
	int Width;
	std::string ID;
	bool isActive;

	//CONSTRUCTORS

	//DESTRUCTORS

	//METHODS
	void Show();
	void Hide();

	void Setup();
	void Update(DataBank* _dataLink, int _x, int _y);
	void Render(DataBank* _dataLink);
	void handleEvent(sf::Event* _event, int _x, int _y);
	char getInput(int Type,sf::Event* _event);
};

#endif
