#ifndef _HorSlider_hpp_
#define _HorSlider_hpp_

#include <string.h>
#include <math.h>
#include "DataBank.hpp"

class HorSlider
{
	//MEMBERS
private:
	bool mouseHover;
	sf::Shape bar;
	sf::Shape decBox;
	sf::Shape incBox;
	sf::Shape slider;
	bool hoverSlide;
	bool moveSlide;
	int oldMouseX;
public:
	int X;
	int Y;
	int Height;
	int Width;

	float ratio;
	float min;
	float max;
	float value;

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