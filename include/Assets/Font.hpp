#ifndef _Font_hpp_
#define _Font_hpp_

#include <Assets\Asset.hpp>
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;
extern void ug::log(std::string);

class Font : public Asset
{
private:
	sf::Font* data;

public:
	sf::Font* getFont();
	void load();
	void unload();
};

#endif // !_Font_hpp_