#ifndef _Font_hpp_
#define _Font_hpp_

#include <SFML\Graphics.hpp>
#include <string>
#include <list>
#include <iostream>

class Font
{
	//MEMBER
private:
	std::list<sf::Font> font;
public:
	std::string id;
	std::string path;

	//CONSTRUCTORS
	Font(std::string, std::string);

	//DESCTRUCTORS

	//METHODS
	void load();
	void unload();
	sf::Font* getFont();
};

#endif
