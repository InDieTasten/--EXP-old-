#ifndef _GUIMenu_hpp_
#define _GUIMenu_hpp_

#include <SFML\Graphics.hpp>
#include <Data\Taggable.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class GUIMenu : sf::Drawable, Taggable
{
private:
	int x;
	int y;
	int width;
	int height;
	std::string title;
public:
	GUIMenu();
	~GUIMenu();

	void draw(sf::RenderTarget& target, sf::RenderStates states);

	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);
	void setTitle(std::string);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	std::string getTitle();
};

#endif // !_GUIMenu_hpp_