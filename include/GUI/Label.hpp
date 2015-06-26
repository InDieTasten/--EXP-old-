#ifndef _Label_hpp_
#define _Label_hpp_

#include <GUI\GUIElement.hpp>
#include <SFML\Text.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Label : GUIElement
{
private:
	std::string text;
	std::string font;
	sf::Color textColor;
	int textSize;
	
	struct Components {
		Text text;
	} components;
public:
	Label(AssetManager* _assets);
	~Label();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvent(sf::RenderWindow& target, sf::Event* _event);

	void setText(std::string);
	void setFont(std::string);
	void setTextColor(sf::Color);
	std::string getText();
	std::string getFont();
	sf::Color getTextColor();
};

#endif // !_Label_hpp_
