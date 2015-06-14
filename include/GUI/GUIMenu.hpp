#ifndef _GUIMenu_hpp_
#define _GUIMenu_hpp_

#include <SFML\Graphics.hpp>
#include <Data\Taggable.hpp>
#include <string>
#include <vector>
#include <GUI\GUIElement.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class GUIMenu : sf::Drawable, Taggable, Responsive
{
private:
	int x;
	int y;
	int width;
	int height;
	std::string title;

	std::vector<GUIElement&> elements;
public:
	GUIMenu();
	~GUIMenu();

	void draw(sf::RenderTarget& target, sf::RenderStates states);

	int addElement(GUIElement& _element);
	GUIElement& getElement(int);
	void removeElement(int);

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