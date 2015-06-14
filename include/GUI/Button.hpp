#ifndef _Button_hpp_
#define _Button_hpp_

#include <SFML\Graphics.hpp>
#include <GUI\GUIElement.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Button : GUIElement
{
private:
	int width;
	int height;
	std::string text;
public:
	Button();
	~Button();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvent(sf::Event* _event);

	void setWidth(int);
	void setHeight(int);
	void setText(std::string);
	int getWidth();
	int getHeight();
	std::string getText();
};

#endif // !_Button_hpp_
