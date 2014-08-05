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
	sf::RectangleShape bar;
	sf::RectangleShape decBox;
	sf::RectangleShape incBox;
	sf::RectangleShape slider;
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
	void Update(DataBank* _dataLink, int _x, int _y, std::string _id);
	void Render(DataBank* _dataLink, int _x, int _y, std::string _id);
	void handleEvent(DataBank* datalink, sf::Event* _event, int _x, int _y, std::string _id);
};

#endif
